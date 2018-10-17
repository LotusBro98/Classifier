#ifndef LCF_LAYER_HPP
#define LCF_LAYER_HPP

#include<iostream>

namespace lcf
{
	template <typename Tout> void mulAddBytes(char * a, char * b, Tout * out, int count);
	void xorBytes(char * a, char * b, int count);
	float sumBytes(char * a, int count);

	class Layer
	{
		public:
			Layer(int nIn, int nOut, char * in = nullptr, char * out = nullptr);
			Layer(Layer * previous, int nOut, char * out = nullptr);
			~Layer();

			void process(char * in = nullptr, char * out = nullptr);
	
			friend std::ostream& operator << (std::ostream& os, Layer * layer);

			char * getWeightsForNeuron(int iOut);

			void stackLayers(Layer * previous);

			int getNOut();
			int getNIn();

		private:
			char * weights;
			int nIn;
			int nOut;
			char * in;
			char * out;

			bool internalIn;
			bool internalOut;
	};
}

#endif
