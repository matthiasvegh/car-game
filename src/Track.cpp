
#include <boost/math/constants/constants.hpp>

#include "Track.hpp"
#include "drawUtil.hpp"

namespace car {

Track Track::createCircleTrack() {

	using namespace boost::math::float_constants;

	Track track;
	const int circleResolution = 60;
	const int numberOfCheckpoints = 8;
	const float innerCircleRadius = 50.;
	const float outerCircleRadius = 60.;
	for ( int i = 0; i < circleResolution; ++i ) {
		track.addLine(Line2f(
					innerCircleRadius*std::cos((i-1)*2*pi/circleResolution),
					innerCircleRadius*std::sin((i-1)*2*pi/circleResolution),
					innerCircleRadius*std::cos((i)*2*pi/circleResolution),
					innerCircleRadius*std::sin((i)*2*pi/circleResolution)));
		track.addLine(Line2f(
					outerCircleRadius*std::cos((i-1)*2*pi/circleResolution),
					outerCircleRadius*std::sin((i-1)*2*pi/circleResolution),
					outerCircleRadius*std::cos((i)*2*pi/circleResolution),
					outerCircleRadius*std::sin((i)*2*pi/circleResolution)));
	}
	for ( int i = 0; i < numberOfCheckpoints; ++i ) {
		track.addCheckpoint(Line2f(
				innerCircleRadius*std::cos((i)*2*pi/numberOfCheckpoints),
				-innerCircleRadius*std::sin((i)*2*pi/numberOfCheckpoints),
				outerCircleRadius*std::cos((i)*2*pi/numberOfCheckpoints),
				-outerCircleRadius*std::sin((i)*2*pi/numberOfCheckpoints)
			));
	}
	return track;
}

void Track::addLine(const Line2f& line) {
	lines.push_back(line);
}

void Track::addCheckpoint(const Line2f& line) {
	checkpoints.push_back(line);
}


bool Track::collidesWith(const Line2f& line) {
	for ( const Line2f& trackLine : lines ) {
		if ( line.intersectWith(trackLine) ) {
			return true;
		}
	}
	return false;
}

int Track::checkpointCollidesWith(const Line2f& line) {
	for ( std::size_t i = 0; i < checkpoints.size(); ++i ) {
		if ( line.intersectWith(checkpoints[i]) ) {
			return i;
		}
	}
	return -1;
}

std::size_t Track::getNumberOfCheckpoints() const {
	return checkpoints.size();
}

void Track::draw(sf::RenderWindow& window, int highlihgtCheckpoint) const {
	for ( const Line2f& trackLine : lines ) {
		drawLine(window, trackLine);
	}

	sf::Color checkpointColor{255, 255, 64};
	sf::Color highlightedCheckpointColor{128, 128, 255};

	for ( std::size_t i = 0; i < checkpoints.size(); ++i ) {

		drawLine(window, checkpoints[i],
				((static_cast<int>(i) == highlihgtCheckpoint) ?
						checkpointColor : highlightedCheckpointColor));
	}
}

}

