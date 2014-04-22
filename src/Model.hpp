#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <boost/optional.hpp>

#include "Car.hpp"
#include "Track.hpp"

namespace car {

class Model {
public:
	Model();

	void setCar(const Car& newCar);
	void setTrack(const Track& newTrack);

	const Car& getCar() const;
	Car& getCar();
	const Track& getTrack() const;
	Track& getTrack();

	void setRightPressed(bool isPressed);
	void setLeftPressed(bool isPressed);
	void setForwardPressed(bool isPressed);
	void setBackwardPressed(bool isPressed);

	float getCurrentTime() const;

	bool hasCarCollided() const;

	std::vector<boost::optional<sf::Vector2f>> getRayPoints(unsigned count) const;

	unsigned getNumberOfCrossedCheckpoints() const;

	void advanceTime(float deltaSeconds);
	void draw(sf::RenderWindow& window) const;

private:
	void collideCar();
	void handleCheckpoints();
	void handleInput(float deltaSeconds);

	Car car;
	Track track;

	bool isCarCollided = false;
	float currentTime = 0.f;
	int currentCheckpoint = -1;
	unsigned numberOfCrossedCheckpoints = 0;

	bool rightPressed = false;
	bool leftPressed = false;
	bool forwardPressed = false;
	bool backwardPressed = false;
};

}

#endif
