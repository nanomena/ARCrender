#ifndef ARC
#define ARC

#pragma GCC target("sse3", "sse2", "sse")
#pragma GCC target("avx", "sse4", "sse4.1", "sse4.2", "ssse3")
#pragma GCC target("f16c")

#ifdef ebug
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define $ if (DEBUG) cerr
// #define double long double

#include <omp.h>
#include <random>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <cstdarg>
#include <algorithm>
#include <map>
#include <array>
#include <cassert>
#include <utility>
#include "stb_image.h"
#include "tiny_obj_loader.h"
#include "stb_image_write.h"
using namespace std;

#endif
