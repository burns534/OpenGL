
//
//  NoiseMap.h
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef NoiseMap_h
#define NoiseMap_h

#include "Noise.h"
#include <random>


class NoiseMap
{
    float * address;
    Noise* n;
    int h, w;
public:
    float * noisemap;
    
    NoiseMap(int width, int height)
    {
        srand( (unsigned)time(NULL) );
        h = height;
        w = width;
        noisemap = new float[width * height];
        address = noisemap;
        n = new Noise();
        for ( int y = 0; y < height; y++ )
            for ( int x = 0; x < width; x++, noisemap++ )
            {
                *noisemap = n->OctavePerlin( x * 50.34f, y * 50.34f, 0, 8, .50, .001f);
            }
        noisemap = address;
        
        blur();
        blur();
    }

    ~NoiseMap()
    {
        delete n;
        noisemap = address;
        delete[] noisemap;
    }
    
    void blur()
    {
        float sum = 0;
        for (int y = 1; y < h - 1; y ++)
            for (int x = 1; x < w - 1; x++)
            {
                sum = 0;
                // 3x3 gaussian kernel
                sum += noisemap[y * h + x] * .25; // current cell
                sum += noisemap[y * h + x - 1] * .125; // left cell
                sum += noisemap[y * h + x + 1] * .125; // right cell
                sum += noisemap[(y+1) * h + x] * .125; // bottom cell
                sum += noisemap[(y-1) * h + x] * .125; // upper cell
                sum += noisemap[(y-1) * h + x - 1] * .0625; // upper left cell
                sum += noisemap[(y-1) * h + x + 1] * .0625; // upper right cell
                sum += noisemap[(y+1) * h + x - 1] * .0625; // lower left cell
                sum += noisemap[(y+1) * h + x + 1] * 0.625; // lower right cell
                noisemap[y * h + x] = sum * 0.65f;
            }
    }
};

#endif /* NoiseMap_h */

