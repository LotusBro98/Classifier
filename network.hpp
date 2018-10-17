#ifndef LCF_NETWORK_HPP
#define LCF_NETWORK_HPP

#include "layer.hpp"
#include "dataset.hpp"

#include <vector>

namespace lcf
{
	class Network
	{
		public:
			Network();
			~Network();

			void addLayer(Layer * layer);

			void process(char * in, char * out);

			void processAll(Dataset * dataset, char * outbuf);

			float calcLoss(Dataset * dataset, char * outBuf);

			void trainEpoch(Dataset * dataset, char * outBuf);

			int getNOut();
			int getNIn();

			friend std::ostream& operator << (std::ostream& os, Network * network);

		private:
			std::vector<Layer> layers;
	};
}

#endif
