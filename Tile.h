//
//  Tile.h
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef Tile_h
#define Tile_h
#include <iostream>
#include "MeshData.h"



struct c
{
    int x,y;
};


class Tile
{
    
public:
    RGBType* pixels;
    Tile(int tilesize)
    {
        pixels = new RGBType[tilesize*tilesize];
    }
};


class Map
{
public:
    int w;
    int h;
    int tsize;
    c Win;
    Noise* no;
    MeshData * meshdata;
    //std::vector< std::vector< Tile* > > field;
    Map(int width, int height, int tilesize, int windowx, int windowy, float xlight, float ylight, float zlight)
    {
        no = new Noise();
        meshdata = new MeshData(width, height);
        w = width;
        h = height;
        tsize = tilesize;
        float f;
        float red, green, blue;
        
        // normalize light source vector
        float mag = pow( xlight * xlight + ylight * ylight + zlight * zlight, 0.5f);
        xlight /= mag;
        ylight /= mag;
        zlight /= mag;
        
        // meshdata->vectex is of dimensions [2 * (w-1) * (h-1)] to store all triangles
        // need to add RGB values to each tile based on the avg of its 3 vertices' y values and then multiply each rgb value by factor f from dot product of
        // triangle's normal vector and the light vector <xlight, ylight, zlight>
        float avg;
        int count = 0;
        float tempx, tempy, tempz;
        for (int i = 0; i < 2 * (width - 1) * (height - 1); i++, count++)
            {
                // average the heights of each triangle's 3 vertices.
                avg = (meshdata->vectex[i].vertices[0].y + meshdata->vectex[i].vertices[1].y + meshdata->vectex[i].vertices[2].y) / 3.0f;
                // assign appropriate color values
                if ( avg < 0.57f ) // water
                {
                    red = 0.0f;
                    green = 46.0f / 255;
                    blue = 203.0f / 255;
                } else if ( avg < 0.58f ) // sand
                {
                    red = 1.0f;
                    green = 220.0f / 255;
                    blue = 147.0f / 255;
                } else if ( avg < 0.71f) // regular green
                {
                    red = 0.0f;
                    green = 185.0f / 300;
                    blue = 33.0f / 300;
                } else if ( avg < 0.76f ) // green 2
                {
                    red = 65.0f / 255;
                    green = 162.0f / 255;
                    blue = 30.0f / 255;
                } else if ( avg < 0.84f ) // mountain 1
                {
                    red = 100.0f / 255;
                    green = 94.0f / 255;
                    blue = 83.0f / 255;
                } else if ( avg < 0.86 ) // mountain 2
                {
                    red = 71.0f / 255;
                    green = 72.0f / 255;
                    blue = 60.0f / 255;
                } else // snow
                {
                    red = blue = green = 0.95f;
                }
                 // -- This is for point source light --
//                // calculate vector from tile to light source ( tiles facing sun need to be brightest )
//                tempx = meshdata->vectex[i].center.x - xlight;
//                tempy = meshdata->vectex[i].center.y - ylight;
//                tempz = meshdata->vectex[i].center.z - zlight;
//                // unitize light vector
//                mag = pow(tempx * tempx + tempy * tempy + tempz * tempz, 0.5f);
//                tempx /= -mag;
//                tempy /= -mag;
//                tempz /= -mag;
                
                // dot product of light vector and normal vector
                f = xlight * meshdata->vectex[i].normal.x + ylight * meshdata->vectex[i].normal.y + zlight * meshdata->vectex[i].normal.z;
                
                // map f from (-1,1) to (0.0f, 1.0f) so it will be an appropriate factor
                f = (f + 1) / 2.0f;
                
                // adjust rgb values proportional to f;
                meshdata->vectex[i].color.r = red * f ;
                meshdata->vectex[i].color.b = blue * f;
                meshdata->vectex[i].color.g = green * f;
                //std::cout << "count, color: " << count << ", " << red + green + blue << "\n";
                //std::cout << "avg, f, red: " << avg << " ," << f << ", " << red << "\n";
            }
        Win.x = windowx;
        Win.y = windowy;
    }
    
    ~Map()
    {
        delete no;
        delete meshdata;
    }
};

#endif /* Tile_h */
