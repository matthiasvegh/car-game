#ifndef CREATECIRCLETRACK_HPP_
#define CREATECIRCLETRACK_HPP_

#include "Track.hpp"

namespace car {

struct CircleTrackParams {
	float innerRadius = 50.f;
	float outerRadius = 60.f;
	int resolution = 60;
	int numberOfCheckpoints = 72;
};

Track createCircleTrack(const CircleTrackParams& params);

}



#endif /* CREATECIRCLETRACK_HPP_ */
