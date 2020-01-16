//
//  MeshData.h
//  Perlin
//
//  Created by Kyle Burns on 1/15/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef MeshData_h
#define MeshData_h

#include "NoiseMap.h"

class MeshData
{
    NoiseMap* nmap;
    int triangleindex;
public:
    float* triangles;
    MeshData(int width, int height)
    {
        nmap = new NoiseMap(width, height);
        triangles = new float[6 * (width-1) * (height-1)]; //triangle array to hold mesh y values
        triangleindex = 0;
        
        for ( int y = 0; y < height - 1; y++ )
            for ( int x = 0; x < width - 1; x ++ )
            {
                AddTriangle(nmap->noisemap[y * height+x], nmap->noisemap[(y+1) * height + x + 1], nmap->noisemap[(y+1) * height+x]);
                AddTriangle(nmap->noisemap[(y + 1) * height + x + 1], nmap->noisemap[y * height + x], nmap->noisemap[y * height + x + 1]);
            }
    }
    
    void AddTriangle(float a, float b, float c)
    {
        triangles[triangleindex] = a; // adds all 3 vertices for our triangle to the triangles array
        triangles[triangleindex+1] = b;
        triangles[triangleindex+2] = c;
        triangleindex += 3;
    }
};




#endif /* MeshData_h */
