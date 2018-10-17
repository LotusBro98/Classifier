#include "layer.hpp"



namespace lcf
{
	
	void mulAddBytes(char * a, char * b, char * out, int count)
	{
		for (int i = 0; i < count; i++)
			*out += a[i] * b[i] / 16;
	}

	void mulAddBytes(char * a, char * b, float * out, int count)
	{
		for (int i = 0; i < count; i++)
			*out += a[i] * b[i];
	}

	void xorBytes(char * a, char * b, int count)
	{
		for (int i = 0; i < count; i++)
			a[i] ^= b[i];
	}

	float sumBytes(char * a, int count)
	{
		int sum = 0;
		for (int i = 0; i < count; i++)
			sum += a[i];

		return sum;
	}


	Layer::Layer(int nIn, int nOut, char * in, char * out)
	{
		this->nIn = nIn;
		this->nOut = nOut;
		this->weights = new char[(nIn + 1) * nOut];
		for (int i = 0; i < (nIn + 1) * nOut; i++)
			weights[i] = std::rand();
	
		internalIn = !in;
		internalOut = !out;
		
		this->in = in ? in : new char[nIn];
		this->out = out ? out : new char[nOut];
	}

	Layer::Layer(Layer * previous, int nOut, char * out) : Layer(previous->nOut, nOut, previous->out, out) 
	{}

	Layer::~Layer()
	{
		if (internalIn)
			delete in;

		if (internalOut)
			delete out;

		delete weights;
	}

	inline char * Layer::getWeightsForNeuron(int iOut)
	{
		return weights + iOut * (nIn + 1);
	}

	std::ostream& operator << (std::ostream& os, Layer * layer)
	{
		os << layer->nIn << " " << layer->nOut << std::endl;

		for (int iOut = 0; iOut < layer->nOut; iOut++)
		{
			for (int iIn = 0; iIn <= layer->nIn; iIn++)
				os << (int)layer->getWeightsForNeuron(iOut)[iIn] << " ";
			os << std::endl;
		}

		return os;
	}

	void Layer::stackLayers(Layer * previous)
	{
		if (this->internalIn)
		{
			delete this->in;
			this->internalIn = false;
		}

		in = previous->out;
	}


	int Layer::getNOut()
	{
		return nOut;
	}

	int Layer::getNIn()
	{
		return nIn;
	}


	//---------------------------------------------------------------



	void Layer::process(char * in, char * out)
	{
		in = in ? in : this->in;
		out = out ? out : this->out;

		for (int i = 0; i < nOut; i++)
		{
			out[i] = 0;
			mulAddBytes(getWeightsForNeuron(i), in, out + i, nIn);
			out[i] += getWeightsForNeuron(i)[nIn];
		}
	}
}
