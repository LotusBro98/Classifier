#include "network.hpp"



float dist1set(char * a, char * b, int  count)
{
	float dist = 0;
	lcf::xorBytes(a, b, count);
	dist = lcf::sumBytes(a, count);
	lcf::xorBytes(a, b, count);

	return dist;
}

float loss(char * in, char * out, int nSets, int nIn, int nOut)
{
	float L = 0;

	for (int i = 0; i < nSets; i++)
	{
		char * inI = in + i * nIn;
		char * outI = out + i * nOut;
		for (int j = i + 1; j < nSets; j++)
		{
			char * inJ = in + j * nIn;
			char * outJ = out + j * nOut;
			
			L += dist1set(outI, outJ, nOut) / (1 + dist1set(inI, inJ, nIn));
		}
	}

	L /= ((float)nSets * (float)nSets) / 2;

	return L;
}




namespace lcf
{
	Network::Network()
	{
		layers = std::vector<Layer>();
	}

	Network::~Network()
	{
		layers.clear();
	}

	void Network::addLayer(Layer * layer)
	{
		if (!layers.empty())
			layer->stackLayers(&layers.back());
		layers.push_back(*layer);
	}


	std::ostream& operator << (std::ostream& os, Network * network)
	{
		os << network->layers.size() << "\n";

		for (int i = 0; i < network->layers.size(); i++)
		{
			os << &network->layers.at(i);	
		}

		return os;
	}

	int Network::getNOut()
	{
		return layers.back().getNOut();
	}

	int Network::getNIn()
	{
		return layers.front().getNIn();
	}


	void Network::processAll(Dataset * dataset, char * outBuf)
	{
		int nOut = getNOut();

		for (int i = 0; i < dataset->getNSets(); i++)
			this->process(dataset->getSet(i), outBuf + i * nOut);
	}


	//----------------------------------------
	float Network::calcLoss(Dataset * dataset, char * outBuf)
	{
		return 0;		
	}
	//----------------------------------------

	void Network::process(char * in, char * out)
	{
		if (layers.size() == 1)
		{
			layers.front().process(in, out);
			return;
		}

		layers.front().process(in);
		for (int i = 1; i < layers.size(); i++)
			layers.at(i).process();
		layers.back().process(nullptr, out);
	}

}
