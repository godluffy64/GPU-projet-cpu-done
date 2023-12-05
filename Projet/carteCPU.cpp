#include <cmath>

#include "carteCPU.hpp"
#include "los/ppm.hpp"

using namespace std;


void drawMap(int *dda_data, uint8_t *h_in, uint8_t *h_out, const int MapSize, const int MapWidth, const int MapHeight, const int Cx,const int Cy)
{
    for(int Py = 0; Py < MapHeight; Py++)
    {
        for(int Px = 0; Px < MapWidth; Px++)
        {

        // DDA entre le point c (Cx, Cy) et le point P (Px, Py);

            float Dx, Dy, D;
            float Cx_dda = (float) Cx, Cy_dda = (float) Cy;
            Dx = Px - Cx;
            Dy = Py - Cy;

            D = max(abs(Dx), abs(Dy));

            float incX = Dx / D;
            float incY = Dy / D;
            for (int i = 0; i < D - 1; i++)
            {
                Cx_dda += incX;
                Cy_dda += incY;
                dda_data[i * 2] = (int)round(Cx_dda);
                dda_data[i * 2 + 1] = (int)round(Cy_dda);
            }

        // Fin calcule DDA

        // Calcule Angle  
            float Dz;
            Dz = h_in[Py * MapWidth + Px] - h_in[Cy * MapWidth + Cx];
            double angle_ref = atan(Dz / sqrt((Dx * Dx) + (Dy * Dy)));
            double angle;

            h_out[Py * MapWidth + Px] = 244;
            //h_out.setPixel(Px, Py, 244);
            for (int i = 0; i < (D - 1); i++)
            {
                Dx = Px - dda_data[i * 2];
                Dy = Py - dda_data[i * 2 + 1];
                Dz = h_in[Py * MapWidth + Px] - h_in[dda_data[i * 2 + 1] * MapWidth + dda_data[i * 2]];  
                angle = atan(Dz / sqrt((Dx * Dx) + (Dy * Dy)));

                if (angle_ref >= angle)
                {
                    //h_out.setPixel(Px, Py, 0);
                    h_out[Py * MapWidth + Px] = 0;
                    break;
                }  
            }        
        }
    }
    //h_out.saveTo("img/Result/CPU/LimousinCPU.ppm");
}