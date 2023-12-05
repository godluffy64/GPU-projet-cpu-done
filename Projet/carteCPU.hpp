#ifndef __CARTE_CPU__
#define __CARTE_CPU__

#include "los/ppm.hpp"

using namespace los;

void drawMap(int *dda_data,uint8_t *h_in, uint8_t *h_out,  const int MapSize, const int MapWidth, const int MapHeight, const int Cx, const int Cy);

#endif //__CARTE_CPU__