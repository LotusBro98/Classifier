#ifndef LCF_DATASET_HPP
#define LCF_DATASET_HPP

#include <iostream>

namespace lcf
{
	class Dataset
	{
		public:
			Dataset(int nSets, int nFeatures);
			Dataset(std::istream& is);
			~Dataset();

			int getNSets();
			int getNFeatures();

			char * getSet(int i);

			friend std::ostream& operator << (std::ostream& os, Dataset * dataset);

		private:
			int nSets;
			int nFeatures;
			char * sets;
	};
}

#endif
