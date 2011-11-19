

#ifndef __okapi_h__
#define __okapi_h__

#include "../../utilities/Library.h"

using std::list;

class Okapi
{
public:
    Okapi( void );
    ~Okapi( void );

    /*
     *  Parameters:     docId           --> The ID of the document for which the
     *                                      calculation involves
     *                  queryTermIdf    --> The weight of the query term to use
     *                  termFrequency   --> The frequency of the query term in
     *                                      the specified document
     *                  kVal            --> The "k" value
     *                  bVal            --> The "b" value
     *                  avgDocLen       --> The average document length of the
     *                                      indexed documents
     *
     *  Returns:        The score of the query term for the document.
     */
    double  computeSimilarity( size_t docId, size_t queryTermIdf,
                                    size_t termFrequency,
                                    double kVal, double bVal, double avgDocLen );
};

#endif /* __okapi_h__ */
