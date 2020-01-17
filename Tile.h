//
//  Tile.h
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef Tile_h
#define Tile_h
#include "Noise.h"
#include "NoiseMap.h"
#include <iostream>

struct RGBType
{
    float r,g,b;
};

struct c
{
    int x,y;
};


class Tile
{
    
public:
    RGBType* pixels;
    Tile(int width, int height, int tilesize)
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
    NoiseMap* gen;
    //std::vector< std::vector< Tile* > > field;
    Tile *** field;
    Map(int width, int height, int tilesize, int windowx, int windowy)
    {
        no = new Noise();
        gen = new NoiseMap(width, height);
        field = new Tile**[height];
        for (int i = 0; i < height; i++) field[i] = new Tile*[width];
        w = width;
        h = height;
        tsize = tilesize;
        RGBType* address;
        float red, green, blue;
        float* zedd = gen->noisemap;
        //std::vector< std::vector< Tile* > > field(height, std::vector< Tile* >(width));
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++, zedd++ )
            {
                field[x][y] = new Tile(width, height, tilesize);
                address = &*field[x][y]->pixels;
//                red = (float) no->OctavePerlin(2 * (float) x / width - 0.02f + (float) x, (float) y / height + float(y), 3, 3, .5);
//                green = (float) no->OctavePerlin(2 * (float) x / width - 0.02f + (float) x, (float) y / height + float(y), 3, 3, .5);
//                blue = (float) no->OctavePerlin(2 * (float) x / width - 0.02f + (float) x, (float) y / height + float(y), 3, 3, .5);
                //zedd = (float) no->OctavePerlin(2 * (float) x / width - 0.02f + (float) x, (float) y / height + float(y), 3, 3, .5);
                if ( * zedd < 0.48f ) // water
                {
                    red = 0.0f;
                    green = 46.0f / 255;
                    blue = 203.0f / 255;
                } else if ( * zedd < 0.50f ) // sand
                {
                    red = 1.0f;
                    green = 220.0f / 255;
                    blue = 147.0f / 255;
                } else if ( * zedd < 0.59) // regular green
                {
                    red = 0.0f;
                    green = 185.0f / 300;
                    blue = 33.0f / 300;
                } else if ( * zedd < 0.63 ) // green 2
                {
                    red = 65.0f / 255;
                    green = 162.0f / 255;
                    blue = 30.0f / 255;
                } else if ( * zedd < 0.7 ) // mountain 1
                {
                    red = 100.0f / 255;
                    green = 94.0f / 255;
                    blue = 83.0f / 255;
                } else if ( * zedd < 0.72 ) // mountain 2
                {
                    red = 71.0f / 255;
                    green = 72.0f / 255;
                    blue = 60.0f / 255;
                } else // snow
                {
                    red = blue = green = 0.95f;
                }
                
                for(int i = 0; i < tilesize; i++)
                    for (int k = 0; k < tilesize; k++)
                    {
                        field[x][y]->pixels[i * tilesize + k].r = red;
                        field[x][y]->pixels[i * tilesize + k].g = green;
                        field[x][y]->pixels[i * tilesize + k].b = blue;
                    }
                //field[x][y]->pixels = address;
            }
        Win.x = windowx;
        Win.y = windowy;
    }
    
    ~Map()
    {
        delete no;
        delete gen;
        for (int y = 0; y < h; y ++)
            for (int x = 0; x < w; x++) delete field[x][y];
        
        for (int i = 0; i < h; i++) delete[] field[i];
        delete[] field;
    }
};

#endif /* Tile_h */
