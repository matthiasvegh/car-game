#include "PopulationRunner.hpp"

#include <mutex>
#include <condition_variable>
#include <iostream>
#include "Genome.hpp"
#include "AsyncHelper.hpp"

namespace car {

PopulationRunner::PopulationRunner(const Parameters& parameters,
		std::vector<std::function<track::Track()>> trackCreators,
		boost::asio::io_service& ioService):
			ioService(&ioService),
			population{parameters.populationSize,
				NeuralNetwork::getWeightCountForNetwork(
					parameters.hiddenLayerCount, parameters.neuronPerHiddenLayer,
					parameters.getInputNeuronCount(), parameters.outputNeuronCount, parameters.useRecurrence)}
{
	controllerDatas.reserve(parameters.populationSize);
	for (std::size_t i = 0; i < parameters.populationSize; ++i) {
		controllerDatas.push_back(NeuralControllerData{
			{
				parameters.hiddenLayerCount,
				parameters.neuronPerHiddenLayer,
				parameters.getInputNeuronCount(),
				parameters.outputNeuronCount,
				parameters.useRecurrence
			},
			{}
		});

		auto& controllerData = controllerDatas.back();
		controllerData.managers.reserve(trackCreators.size());
		for (const auto& trackCreator: trackCreators) {
			controllerData.managers.emplace_back(parameters, trackCreator);
		}
	}
}

void PopulationRunner::runIteration() {
	Genomes& genomes = population.getPopulation();
	assert(genomes.size() == controllerDatas.size());

	std::condition_variable conditionVariable;
	std::mutex mutex;
	std::size_t tasksLeft{controllerDatas.size()};

	for (std::size_t i = 0; i < controllerDatas.size(); ++i) {
		auto& genome = genomes[i];
		auto& data = controllerDatas[i];

		ioService->post([this, &genome, &data, &tasksLeft, &conditionVariable, &mutex]() {
				runSimulation(genome, data);

				{
					std::unique_lock<std::mutex> lock{mutex};
					if (--tasksLeft == 0) {
						conditionVariable.notify_all();
					}
				}
			});
	}

	{
		std::unique_lock<std::mutex> lock{mutex};
		while (tasksLeft != 0) {
			conditionVariable.wait(lock);
		}
	}

	updateBestFitness();
	population.evolve();
}

void PopulationRunner::runSimulation(Genome& genome, NeuralControllerData& data) {
	data.network.setWeights(genome.weights);
	genome.fitness = 0;

	for (auto& manager: data.managers) {
		manager.setNeuralNetwork(data.network);
		manager.init();
		manager.run();
		genome.fitness += manager.getFitness();
	}
}

void PopulationRunner::updateBestFitness() {
	fitnessSum = 0.f;
	for (Genome& genome : population.getPopulation()) {
		fitnessSum += genome.fitness;
		if (genome.fitness > bestFitness) {
			bestFitness = genome.fitness;
			bestGenome = &genome;
		}
	}
}

} /* namespace car */
