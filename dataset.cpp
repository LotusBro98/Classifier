#include "dataset.hpp"

namespace lcf
{
	Dataset::Dataset(int nSets, int nFeatures)
	{
		this->nSets = nSets;
		this->nFeatures = nFeatures;

		this->sets = new char[nSets * nFeatures];
	}

	inline int Dataset::getNSets()
	{
		return nSets;
	}

	inline int Dataset::getNFeatures()
	{
		return nFeatures;
	}

	inline char * Dataset::getSet(int i)
	{
		return sets + nFeatures * i;
	}

	Dataset::~Dataset()
	{
		delete sets;
	}

	Dataset::Dataset(std::istream& is)
	{
		is >> nSets >> nFeatures;
		
		this->sets = new char[nSets * nFeatures];
		
		for(int i = 0; i < nSets * nFeatures; i++)
		{
			is >> sets[i];
			sets[i] -= '0';
		}
	}

	std::ostream& operator << (std::ostream& os, Dataset * ds)
	{
		os << ds->nSets << " " << ds->nFeatures << std::endl;
		for (int set = 0; set < ds->nSets; set++)
		{
			for (int feature = 0; feature < ds->nFeatures; feature++)
				os << (int)ds->getSet(set)[feature];
			os << std::endl;
		}

		return os;
	}
}
