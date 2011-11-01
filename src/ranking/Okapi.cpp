
#include "Okapi.h"

Okapi::Okapi() {}

Okapi::~Okapi() {}

double  Okapi::computeSimilarity( size_t docId, size_t queryTermIdf,
                                            size_t termFrequency,
                                            double kVal, double bVal,
                                            double avgDocLen )
{


	double result = 0;

	size_t docLength ;

	//get doc length for given doc id
	//TODO: replace this with average document length
	docLength = 5000;

	double numerator,denominator;

	numerator = termFrequency*(kVal+1);

	denominator = termFrequency + kVal*(1- bVal + (bVal*docId)/avgDocLen);


	result = queryTermIdf*(numerator/denominator);

	return result;

}
