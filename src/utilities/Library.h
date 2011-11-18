/*
 * Library.h
 * Contains all the library imports required for project
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include <istream>
#include <fstream>

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <cassert>

//boost library
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>




#define UNIX
#ifdef UNIX
#include <ctime>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#endif


#ifdef UNIX
const bool b_verbose_global = false;
#endif

#endif
