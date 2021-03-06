
#include "RealTimeGameManager.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>

#include <boost/math/constants/constants.hpp>

#include "mathUtil.hpp"
#include "drawUtil.hpp"
#include "randomUtil.hpp"

namespace car {

RealTimeGameManager::RealTimeGameManager(const Parameters& parameters, std::function<track::Track()> trackCreator,
			bool startWithAi) :
	GameManager(parameters, trackCreator),
	window(sf::VideoMode(parameters.screenWidth, parameters.screenHeight), "car-game")
{
	using namespace boost::math::float_constants;

	isAIControl = startWithAi;
	font.loadFromFile(parameters.projectRootPath + "/resources/DejaVuSansMono.ttf");
	gasTelemetry.setAutomaticBoundsDetection(false);
	gasTelemetry.setBounds(0.f, 1.f);
	brakeTelemetry.setAutomaticBoundsDetection(false);
	brakeTelemetry.setBounds(0.f, 1.f);
	angleTelemetry.setAutomaticBoundsDetection(false);
	angleTelemetry.setBounds(-pi, pi);
	turnTelemetry.setAutomaticBoundsDetection(false);
	turnTelemetry.setBounds(-1.f, 1.f);

	const float minPixelPerMeter = 10;
	sf::FloatRect staticViewRect = resizeToEnclose(track.getDimensions(), static_cast<float>(parameters.screenWidth)/parameters.screenHeight);

	if (parameters.panMode == PanMode::enabled ||
		(parameters.panMode == PanMode::automatic && parameters.screenWidth / staticViewRect.width > minPixelPerMeter))
	{
		gameView.setSize(parameters.screenWidth / minPixelPerMeter, parameters.screenHeight / minPixelPerMeter);
		gameView.setCenter(model.getCar().getPosition());
		panningEnabled = true;
	} else {
		gameView.reset(staticViewRect);
		panningEnabled = false;
	}

	hudView = window.getDefaultView();
}

void RealTimeGameManager::run() {

	sf::Clock clock;

	float physicsTimeStepAccumulator = 0.f;

	while (window.isOpen()) {
		const sf::Time time = clock.restart();
		float deltaSeconds = time.asSeconds();
		fps = 1/deltaSeconds;

		//if we're really really slow
		if (deltaSeconds > 0.1f) {
			deltaSeconds = 0.1f;
		}
		physicsTimeStepAccumulator += deltaSeconds;
		while (physicsTimeStepAccumulator >= physicsTimeStep) {
			advance();
			if (panningEnabled) {
				gameView.setCenter(model.getCar().getPosition());
			}
			physicsTimeStepAccumulator -= physicsTimeStep;
		}

		updateTelemetry();

		window.clear(sf::Color::Black);

		window.setView(gameView);
		drawGame();

		window.setView(hudView);
		drawTelemetry();

		window.display();
		if (fpsLimit > 0) {
			const sf::Time renderTime = clock.getElapsedTime();
			if (renderTime.asSeconds() < 1.f/fpsLimit) {
				sf::sleep( sf::seconds(1.f/fpsLimit - renderTime.asSeconds()) );
			}
		}
	}
}

void RealTimeGameManager::setFPSLimit(float newFPSLimit) {
	fpsLimit = newFPSLimit;
}

void RealTimeGameManager::handleUserInput() {

	sf::Event event;
	while (window.pollEvent(event)) {
		switch(event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			pressedKeys[event.key.code] = true;
			switch(event.key.code) {
			case sf::Keyboard::C:
				showCar = !showCar;
				break;
			case sf::Keyboard::Y:
				showRays = !showRays;
				break;
			case sf::Keyboard::P:
				showCheckPoints = !showCheckPoints;
				break;
			case sf::Keyboard::R:
				showTrackBoundary = !showTrackBoundary;
				break;
			case sf::Keyboard::T:
				showTelemetryGraphs = !showTelemetryGraphs;
				break;
			case sf::Keyboard::X:
				showTelemetryText = !showTelemetryText;
				break;
			case sf::Keyboard::A:
				isAIControl = !isAIControl;
				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			pressedKeys[event.key.code] = false;
			break;
		default:
			break;
		}
	}

	if (pressedKeys[sf::Keyboard::Q] || pressedKeys[sf::Keyboard::Escape]) {
		window.close();
	}

	if (!isAIControl) {
		model.setLeftPressed(pressedKeys[sf::Keyboard::Left]);
		model.setRightPressed(pressedKeys[sf::Keyboard::Right]);
		model.setForwardPressed(pressedKeys[sf::Keyboard::Up]);
		model.setBackwardPressed(pressedKeys[sf::Keyboard::Down]);
	}
}

void RealTimeGameManager::updateTelemetry() {
	float currentTime = model.getCurrentTime();
	const Car& car = model.getCar();

	speedTelemetry.addDataPoint(sf::Vector2f(currentTime, car.getSpeed()));
	accelerationTelemetry.addDataPoint(sf::Vector2f(currentTime, getLength(car.getAcceleration())));
	angleTelemetry.addDataPoint(sf::Vector2f(currentTime, std::atan2(car.getOrientation().x, car.getOrientation().y)));
	gasTelemetry.addDataPoint(sf::Vector2f(currentTime, car.getThrottle()));
	brakeTelemetry.addDataPoint(sf::Vector2f(currentTime, car.getBrake()));
	turnTelemetry.addDataPoint(sf::Vector2f(currentTime, car.getTurnLevel()));
}

void RealTimeGameManager::drawGame() {
	if (showTrackBoundary) {
		model.drawTrack(window, showCheckPoints);
	}
	if (showRays) {
		drawRays();
	}
	if (showCar) {
		model.drawCar(window);
	}
}

void RealTimeGameManager::drawRays() {
	const Car& car = model.getCar();

	for (const auto& ray : rayPoints) {
		if (!ray) {
			continue;
		}
		drawLine(window, car.getPosition(), *ray, sf::Color{64, 64, 0});
	}
}

void RealTimeGameManager::drawTelemetry() {
	using namespace boost::math::float_constants;

	if (showTelemetryText) {
		const Car& car = model.getCar();

		auto checkpointDirection = model.getCheckpointDirection();

		std::stringstream ss;
		ss << std::fixed <<
			"FPS = " << std::setw(4) << std::setfill('0') << static_cast<int>(fps) <<
			", Speed = " << car.getSpeed() <<
			", Acceleration = " << getLength(car.getAcceleration()) <<
			", Throttle = " << car.getThrottle() <<
			",\nBrake = " << car.getBrake() <<
			", Checkpoint = (" << checkpointDirection.x << ", " << checkpointDirection.y << ")" <<
			", TravelDistance = " << car.getTravelDistance();
		sf::Text text;
		text.setFont(font);
		text.setColor(sf::Color::White);
		text.setCharacterSize(32);
		text.setString(sf::String(ss.str()));
		text.setScale(.5, .5);
		text.setPosition(3., 3.);

		window.draw(text);
	}

	if (showTelemetryGraphs) {
		speedTelemetry.drawAsGraph(window, sf::FloatRect(10, 20, 600, 200), sf::Color::Green);
		accelerationTelemetry.drawAsGraph(window, sf::FloatRect(10, 20, 600, 200), sf::Color::Yellow);
		angleTelemetry.drawAsGraph(window, sf::FloatRect(10, 20, 600, 200), sf::Color::White);
		gasTelemetry.drawAsGraph(window, sf::FloatRect(10, 230, 600, 200), sf::Color::Red);
		brakeTelemetry.drawAsGraph(window, sf::FloatRect(10, 230, 600, 200), sf::Color::Magenta);
		turnTelemetry.drawAsGraph(window, sf::FloatRect(10, 230, 600, 200), sf::Color::Cyan);
	}
}

}

