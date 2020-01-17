
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
#include <iostream>

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
        noisemap = new float[(width + 2) * (height + 2)];
        address = noisemap;
        n = new Noise();
        for ( int y = 0; y < height + 2; y++ ) // + 2 allows for gaussian blur and clipping the egdes off later.
            for ( int x = 0; x < width + 2; x++, noisemap++ )
            {
                *noisemap = n->OctavePerlin( x * 50.34f, y * 50.34f, 0, 8, .50, .00024f); // ~.00024 appears to be optimal
                //std::cout << "here: " << *noisemap << "\n";
            }
        noisemap = address;
        for (int i = 0; i < 4; i ++) blur();
        // create temp to clip edges
        float * temp = new float[width * height];
        for(int y = 0; y < height; y ++)
            for ( int x = 0; x < width; x++)
            {
                temp[y * height + x] = noisemap[(y+1) * (height + 2) + x + 1];
            }
        delete[] noisemap;
        // refill clipped noisemap from temp
        noisemap = new float[width * height];
        for ( int y = 0; y < height; y ++)
            for ( int x = 0; x < width; x++) noisemap[y * height + x] = temp[y * height + x];
        delete[] temp;
        
    }

    ~NoiseMap()
    {
        delete n;
        noisemap = address;
        delete[] noisemap;
    }
    
    void correct()
    {
        for ( int y = 0; y < h; y ++)
            for ( int x = 0; x < w; x++) noisemap[y * h + x] *= 0.65f;
    }
    void blur()
    {
        float sum = 0;
        for (int y = 1; y < h + 1 ; y ++)
            for (int x = 1; x < w + 1; x++)
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
                if (0.65f * sum < .44f) noisemap[y * h + x] = 0.46f;
                else noisemap[y * h + x] = 0.645f * sum;
            }
    }
};

#endif /* NoiseMap_h */

