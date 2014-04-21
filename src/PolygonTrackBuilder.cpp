#include "PolygonTrackBuilder.hpp"
#include "mathUtil.hpp"
#include "Line2.hpp"
#include "LineIntersection.hpp"
#include <iostream>

namespace car {

namespace {

void closeEdges(std::vector<Line2f>& edge) {
	for (std::size_t i = 0; i < edge.size(); ++i) {
		auto& line1 = edge[i];
		auto& line2 = edge[(i + 1) % edge.size()];

		if (!isParallel(line1, line2)) {
			sf::Vector2f intersectionPoint;
			intersectsInfinite(line1, line2, &intersectionPoint);

			line1.end = intersectionPoint;
			line2.start = intersectionPoint;
		}
	}
}

}

Track PolygonTrackBuilder::operator()(const std::vector<sf::Vector2f>& points) {
	const float distance = trackWidth / 2.f;

	std::vector<Line2f> rightEdge;
	std::vector<Line2f> leftEdge;
	rightEdge.reserve(points.size());
	leftEdge.reserve(points.size());

	Track track;

	for (std::size_t i = 0; i < points.size(); ++i) {
		const auto& point1 = points[i];
		const auto& point2 = points[(i + 1) % points.size()];

		// rotate direction 90 degrees and normalize it
		auto direction = normalize(rotateClockwise(point2 - point1));
		auto shift = direction * distance;

		rightEdge.push_back({point1 + shift, point2 + shift});
		leftEdge.push_back({point1 - shift, point2 - shift});

	}

	closeEdges(rightEdge);
	closeEdges(leftEdge);

	for (std::size_t i = 0; i < rightEdge.size(); ++i) {
		const auto& line1 = rightEdge[i];
		const auto& line2 = leftEdge[i];

		track.addLine(line1);
		track.addLine(line2);

		auto roadVector = line1.end - line1.start;
		auto roadDirection = normalize(roadVector);
		auto checkpointDirection = rotateCounterclockwise(roadDirection);
		auto length = getLength(roadVector);

		for (float position = 0.f; position < length; position += checkpointDistance) {
			auto base = line1.start + roadDirection * position;
			LineIntersection<float> intersection{line2, {base, base + checkpointDirection}};

			auto intersectionPoint = intersection.getIntersectionPoint();
			if (!intersectionPoint) {
				continue;
			}

			auto ratio = intersection.getIntersectionPointRatioLine1();
			if (ratio > 0.f && ratio < 1.f) {
				track.addCheckpoint({base, *intersectionPoint});
			}
		}

		track.addCheckpoint({line1.end, line2.end});
	}

	return track;
}

} /* namespace car */