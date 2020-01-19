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
    Map(int width, int height, int tilesize, int windowx, int windowy)
    {
        no = new Noise();
        meshdata = new MeshData(width, height);
        w = width;
        h = height;
        tsize = tilesize;
        float red, green, blue;
        
        // meshdata->vectex is of dimensions [2 * (w-1) * (h-1)] to store all triangles
        // need to add RGB values to each tile based on the avg of its 3 vertices' y values and then multiply each rgb value by factor f from dot product of
        // triangle's normal vector and the light vector <xlight, ylight, zlight>
        float avg;
        for (int i = 0; i < 2 * (width - 1) * (height - 1); i++)
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
               
                meshdata->vectex[i].color.r = red;
                meshdata->vectex[i].color.b = blue;
                meshdata->vectex[i].color.g = green;
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
