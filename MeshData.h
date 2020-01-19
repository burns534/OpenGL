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

struct RGBType
{
    float r,g,b;
};

struct Coord
{
    float x,y,z;
};
// for storing each mesh triangle's data
struct Triangle
{
    Coord vertices[3];
    Coord normal;
    RGBType color;
};

class MeshData
{
    NoiseMap* nmap;
    int triangleindex;
    Triangle * vectex;
    int vectexindex;
public:
    float* triangles;
    MeshData(int width, int height)
    {
        nmap = new NoiseMap(width, height);
        vectex = new Triangle[(width - 1) * (width - 1)];
        triangles = new float[6 * (width-1) * (height-1)]; //triangle array to hold mesh y values
        triangleindex = 0;
        
        for ( int y = 0; y < height - 1; y++ )
            for ( int x = 0; x < width - 1; x ++ )
            {
                AddTriangle(x, y, x + 1, y + 1, x, y + 1, nmap->noisemap[y * height+x], nmap->noisemap[(y+1) * height + x + 1], nmap->noisemap[(y+1) * height+x]);
                AddTriangle(x + 1, y + 1, x , y , x +1, y , nmap->noisemap[(y + 1) * height + x + 1], nmap->noisemap[y * height + x], nmap->noisemap[y * height + x + 1]);
            }
    }
    
    ~MeshData()
    {
        delete[] triangles;
    }
    void AddNormal(int x, int y, float a, float b, float c)
    {
    }
    void AddTriangle(float x, float y, float x1, float y1, float x2, float y2, float a, float b, float c)
    {
        // add complete triangle coordinates to object
        vectex[vectexindex].vertices[0].x = x;
        vectex[vectexindex].vertices[0].z = y;
        vectex[vectexindex].vertices[0].y = a;
        vectex[vectexindex].vertices[1].x = x + 1;
        vectex[vectexindex].vertices[1].z = y + 1;
        vectex[vectexindex].vertices[1].y = b;
        vectex[vectexindex].vertices[2].x = x;
        vectex[vectexindex].vertices[2].z = y + 1;
        vectex[vectexindex].vertices[2].y = c;
        
        // calculate normal vector for triangle
        
        float tempx = c - b; // everything else cancelled
        // tempy turned out to be 1 always
        float tempz = a - c;
        
        // normalize vector and add to object
        float magnitude = pow(tempx * tempx + 1 + tempz * tempz, 0.5f);
        vectex[vectexindex].normal.x = tempx / magnitude;
        vectex[vectexindex].normal.y = 1 / magnitude;
        vectex[vectexindex].normal.z = tempz / magnitude;
        //std::cout << "normal vector: < " << tempx / magnitude << " , " << 1 / magnitude << " , " << tempz / magnitude << " >\n";
        
        triangles[triangleindex] = a; // adds all 3 vertices for our triangle to the triangles array
        triangles[triangleindex+1] = b;
        triangles[triangleindex+2] = c;
        triangleindex += 3;
    }
};




#endif /* MeshData_h */
