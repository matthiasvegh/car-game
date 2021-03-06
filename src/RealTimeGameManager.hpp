#ifndef REALTIMEGAMEMANAGER_HPP
#define REALTIMEGAMEMANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "GameManager.hpp"
#include "Telemetry.hpp"

namespace car {

namespace track {
	class Track;
}

class RealTimeGameManager : public GameManager {
public:
	RealTimeGameManager(const Parameters& parameter, std::function<track::Track()> trackCreator,
			bool startWithAi);

	void run();

	void setFPSLimit(float newFPSLimit);

protected:
	virtual void handleUserInput();

	void drawGame();
	void drawTelemetry();
	void drawRays();
	void updateTelemetry();

	sf::RenderWindow window;
	sf::View gameView;
	sf::View hudView;
	sf::Font font;

	bool panningEnabled = false;

	float fpsLimit = 64;
	float fps = -1.f;

	bool showCar = true;
	bool showRays = true;
	bool showCheckPoints = true;
	bool showTrackBoundary = true;
	bool showTelemetryText = true;
	bool showTelemetryGraphs = false;

	Telemetry speedTelemetry;
	Telemetry accelerationTelemetry;
	Telemetry angleTelemetry;
	Telemetry gasTelemetry;
	Telemetry brakeTelemetry;
	Telemetry turnTelemetry;

	bool pressedKeys[sf::Keyboard::KeyCount] = {false};

};

}

#endif /* !REALTIMEGAMEMANAGER_HPP */
