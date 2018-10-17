#include "layer.hpp"
#include "dataset.hpp"
#include "network.hpp"

#include <fstream>
#include <iostream>

int main()
{
	auto layer = new lcf::Layer(50, 7);
	auto layer2 = new lcf::Layer(7, 1);
	
	std::ifstream datafile;
	datafile.open("firstset.txt");
	auto dataset = new lcf::Dataset(datafile);
	datafile.close();

	auto network = new lcf::Network();
	network->addLayer(layer);
	network->addLayer(layer2);

	std::cout << network;

	char in[50];
	char out[1];

	network->process(in, out);

	return 0;
}
