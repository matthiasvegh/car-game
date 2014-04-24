
#include "RealTimeGameManager.hpp"
#include "NeuralController.hpp"
#include "Parameters.hpp"
#include "TrackType.hpp"
#include "Track.hpp"
#include "RandomTrackGenerator.hpp"
#include "PolygonTrackBuilder.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

#include <boost/archive/text_iarchive.hpp>

using namespace car;

int main(int argc, char **argv) {

	std::srand(std::time(0));

	Parameters parameters = parseParameters(argc, argv);

	std::function<Track()> trackCreator;

	switch (parameters.trackType) {
	case TrackType::circle:
		trackCreator = createCircleTrack;
		break;
	case TrackType::zigzag:
		trackCreator = createZigZagTrack;
		break;
	case TrackType::curvy:
		trackCreator = createCurvyTrack;
		break;
	case TrackType::random:
		RandomTrackGenerator generator{PolygonTrackBuilder{5.f}, 100,
				parameters.randomTrackPoints, parameters.minRandomTrackWidth, parameters.maxRandomTrackWidth,
				{-60.f, -60.f}, {60.f, 60.f}};
		trackCreator = std::bind(generator, parameters.randomTrackSeed);
		break;
	}

	if (parameters.isAI) {
		NeuralController controller{parameters, trackCreator};
		controller.run();
	} else {
		RealTimeGameManager manager{trackCreator};

		manager.setFPSLimit(parameters.fpsLimit);

		if (parameters.neuralNetworkFile) {
			NeuralNetwork network;

			std::ifstream ifs(*parameters.neuralNetworkFile);
			boost::archive::text_iarchive ia(ifs);
			ia >> network;

			manager.setNeuralNetwork(network);
		}
		manager.run();
	}
	return 0;
}

