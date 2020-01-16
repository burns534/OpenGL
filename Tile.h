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
    Tile * field[100][100];
    Map(int width, int height, int tilesize)
    {
        no = new Noise();
        gen = new NoiseMap(width, height);
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
                if ( * zedd < 0.48 ) // water
                {
                    red = 0.0f;
                    green = 46.0f / 255;
                    blue = 203.0f / 255;
                } else if ( * zedd < 0.51 ) // sand
                {
                    red = 1.0f;
                    green = 234.0f / 255;
                    blue = 147.0f / 255;
                } else if ( * zedd < 0.6) // regular green
                {
                    red = 0.0f;
                    green = 185.0f / 255;
                    blue = 33.0f / 255;
                } else if ( * zedd < 0.65 ) //mountain
                {
                    red = 97.0f / 255;
                    green = 64.0f / 255;
                    blue = 45.0f / 255;
                } else if ( * zedd < 0.7 )
                {
                    red = 51.0f / 255;
                    green = 38.0f / 255;
                    blue = 0.0f;
                } else // snow
                {
                    red = blue = green = 1.0f;
                }
                
                for(int i = 0; i < tilesize; i++)
                    for (int k = 0; k < tilesize; k++, field[x][y]->pixels++)
                    {
                        field[x][y]->pixels->r = red;
                        field[x][y]->pixels->g = green;
                        field[x][y]->pixels->b = blue;
                    }
                field[x][y]->pixels = address;
            }
        Win.x = width * 8;
        Win.y = width * 8;
    }
};

#endif /* Tile_h */
