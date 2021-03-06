#ifndef SRC_TRACK_RANDOMWALKPOLYGONGENERATOR_HPP
#define SRC_TRACK_RANDOMWALKPOLYGONGENERATOR_HPP

#include "RandomGenerator.hpp"
#include "RandomTrackException.hpp"
#include "Line2.hpp"

namespace car { namespace track {

class RandomWalkPolygonGenerator {
public:
	struct Params {
		std::size_t horizontalResolution = 10;
		std::size_t verticalResolution = 10;
		float gridSize = 20.f;
		float jitter = 2.f;
	};

	RandomWalkPolygonGenerator(const Params& params): params(params)
	{
	}

	std::vector<sf::Vector2f> operator()(RandomGenerator& rng) const;
private:
	Params params;
};

}} /* namespace car::track */



#endif /* SRC_TRACK_RANDOMWALKPOLYGONGENERATOR_HPP */
