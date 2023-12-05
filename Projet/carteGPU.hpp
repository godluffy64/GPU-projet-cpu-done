#ifndef __CARTE_GPU__
#define __CARTE_GPU__


#include "utils/commonCUDA.hpp"
#include "utils/chronoGPU.hpp"
#include "los/ppm.hpp"

using namespace los;

__global__ void kernelMap(int *data,const uint8_t h_in, Heightmap h_out, const int Cx,const int Cy)
void carteGPU(int *data, const uint8_t *h_in, Heightmap h_out,const int Cx,const int Cy)



#endif //__CARTE_GPU__