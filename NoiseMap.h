
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
    Noise* n;
    int h, w;
public:
    float * noisemap;
    float ** tempmap;
    NoiseMap(int width, int height)
    {
        srand( (unsigned)time(NULL) );
        tempmap = new float* [height + 2];
        for ( int i = 0; i < height + 2; i++) tempmap[i] = new float[width + 2];
        noisemap = new float[height * width];
        h = height;
        w = width;
        n = new Noise;
        for ( int y = 0; y < height + 2; y++ ) // + 2 allows for gaussian blur and clipping the egdes off later.
            for ( int x = 0; x < width + 2; x++)
            {
                tempmap[x][y] = n->OctavePerlin( x * 50.34f, y * 50.34f, 0, 8, .50, .00024f); // ~.00024 appears to be optimal
                //std::cout << "here: " << *noisemap << "\n";
            }
        // apply gaussian blur to plus sized tempmap
        blur(); blur(); blur();
        
        // copy only blurred region of plus sized tempmap to appropriately sized noisemap
        for ( int y = 1; y < height + 1; y++ )
            for ( int x = 1; x < width + 1; x++ )
                noisemap[(y-1) * width + (x-1)] = tempmap[x][y];
        for ( int i = 0; i < h; i++) delete[] tempmap[i];
        delete[] tempmap;
        
    }

    ~NoiseMap()
    {
        delete n;
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
                sum += tempmap[x][y] * .25; // current cell
                sum += tempmap[x-1][y] * .125; // left cell
                sum += tempmap[x+1][y] * .125; // right cell
                sum += tempmap[x][y-1] * .125; // bottom cell
                sum += tempmap[x][y+1] * .125; // upper cell
                sum += tempmap[x-1][y+1] * .0625; // upper left cell
                sum += tempmap[x+1][y+1] * .0625; // upper right cell
                sum += tempmap[x-1][y-1] * .0625; // lower left cell
                sum += tempmap[x+1][y-1] * 0.625; // lower right cell
                if (0.65f * sum < .455) tempmap[x][y] = 0.455f;
                else tempmap[x][y] = 0.645f * sum;
            }
    }
};

#endif /* NoiseMap_h */

