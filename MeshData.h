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
    Coord center;
};

class MeshData
{
    NoiseMap* nmap;
    int vectexindex;
public:
    Triangle * vectex;
    MeshData(int width, int height)
    {
        nmap = new NoiseMap(width, height);
        vectex = new Triangle[2 * (width - 1) * (width - 1)];
        vectexindex = 0;
        //nmap->noisemap is 1d array of dimensions [width * height] so need to access it as such
        for ( int y = 0; y < height - 1; y++ )
            for ( int x = 0; x < width - 1; x ++ )
            {
                AddTriangle(x, y, x + 1, y + 1, x, y + 1, nmap->noisemap[y * (width)+x], nmap->noisemap[(y+1) * (width) + x + 1], nmap->noisemap[(y+1) * (width)+x]);
                AddTriangle(x + 1, y + 1, x , y , x + 1, y , nmap->noisemap[(y + 1) * (width) + x + 1], nmap->noisemap[y * (width) + x], nmap->noisemap[y * width + x + 1]);
            }
    }
    
    ~MeshData()
    {
        delete[] vectex; delete nmap;
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
        vectex[vectexindex].vertices[1].x = x1;
        vectex[vectexindex].vertices[1].z = y1;
        vectex[vectexindex].vertices[1].y = b;
        vectex[vectexindex].vertices[2].x = x2;
        vectex[vectexindex].vertices[2].z = y2;
        vectex[vectexindex].vertices[2].y = c;
        
        /* THIS IS WRONG AND NOT GENERIC FOR ALL TRIANGLES, IT ONLY WORKS FOR HALF OF THEM */
        // calculate normal vector for triangle
        float tempx = (a - b) * (y2 - y1) - (y - y1) * (c - b);
        float tempy = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
        // tempy turned out to be 1 always
        float tempz = (x - x1) * (c - b) - (a - b) * (x2 - x1);
        
        // normalize vector and add to object
        float magnitude = pow(tempx * tempx + 1 + tempz * tempz, 0.5f);
        vectex[vectexindex].normal.x = tempx / magnitude;
        vectex[vectexindex].normal.y = tempy / magnitude;
        vectex[vectexindex].normal.z = tempz / magnitude;
        
        // calculate center point
        vectex[vectexindex].center.x = (x + x1 + x2) / 3.0f;
        vectex[vectexindex].center.y = (y + y1 + y2) / 3.0f;
        vectex[vectexindex].center.z = (a + b + c) / 3.0f;
        //std::cout << "normal vector: < " << tempx / magnitude << " , " << 1 / magnitude << " , " << tempz / magnitude << " >\n";
        vectexindex += 1;
    }
};




#endif /* MeshData_h */
