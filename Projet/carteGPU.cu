#include "utils/commonCUDA.hpp"
#include "utils/chronoGPU.hpp"

#include "carteCPU.hpp"


__global__ void kernelMap(int *data,const Heightmap h_in, Heightmap h_out, const int Cx,const int Cy)
{
    for(int indexY = blockDim.y * blockIdx.y + threadIdx.y ; indexY < h_in.getHeight(); indexY += blockDim.y * gridDim.y)
    {
        for(int indexX = blockDim.x * blockIdx.x + threadIdx.x; indexX < h_in.getWidth(); indexX += blockDim.x * gridDim.x)
        {
        // DDA entre le point c (Cx, Cy) et le point P (indexX, indexY);

            float Dx, Dy, D;
            float Cx_dda = (float) Cx, Cy_dda = (float) Cy;
            Dx = indexX - Cx;
            Dy = indexY - Cy;

            D = max(abs(Dx), abs(Dy));

            float incX = Dx / D;
            float incY = Dy / D;
            for (int i = 0; i < D - 1; i++)
            {
                Cx_dda += incX;
                Cy_dda += incY;
                data[i * 2] = (int)round(Cx_dda);
                data[i * 2 + 1] = (int)round(Cy_dda);
            }

        // Fin calcule DDA

        // Calcule Angle  
            float Dz;
            Dz = h_in.getPixel(indexX, indexY) - h_in.getPixel(Cx, Cy);
            double angle_ref = atan(Dz / sqrt((Dx * Dx) + (Dy * Dy)));
            double angle;

            h_out.setPixel(indexX, indexY, 244);
            for (int i = 0; i < (D - 1); i++)
            {
                Dx = indexX - data[i * 2];
                Dy = indexY - data[i * 2 + 1];
                Dz = h_in.getPixel(indexX, indexY) - h_in.getPixel(data[i * 2], data[i * 2 + 1]);  
                angle = atan(Dz / sqrt((Dx * Dx) + (Dy * Dy)));

                if (angle_ref >= angle)
                {
                    h_out.setPixel(indexX, indexY, 0);
                    break;
                }  
            }        
        }
    }
    h_out.saveTo("img/Result/CPU/LimousinCPU.ppm");
}



void carteGPU(int *data, const Heightmap h_in, Heightmap h_out,const int Cx,const int Cy)
{
    int *dev_data;
    Heightmap *dev_h_in;
    Heightmap *dev_h_out;

    //cudaMalloc(&dev_data, )


}