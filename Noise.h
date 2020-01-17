//
//  Noise.h
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef Noise_h
#define Noise_h

#include <math.h>
#include <vector>


class Noise
{
    short permutation[256];
    int p[512];
    
           
public:
    
    friend class Tile;
    Noise()
    {
        srand ( (unsigned) time(NULL) );
        unsigned long j = rand() % 500;
        for (int i = 0; i < 256; i ++)
        {
            j = 5 * j + 1;
            permutation[i] = j % 256;
        }
        for (int i = 0; i < 512; i++) p[i] = permutation[i % 256];
        
    }
    double perlin(double x, double y, double z)
    {
        
        int xi = (int)x & 255;              // Calculate the "unit cube" that the point asked will be located in
        int yi = (int)y & 255;              // The left bound is ( |_x_|,|_y_|,|_z_| ) and the right bound is that
        int zi = (int)z & 255;              // plus 1.  Next we calculate the location (from 0.0 to 1.0) in that cube.
        double xf = x-(int)x;
        double yf = y-(int)y;
        double zf = z-(int)z;
        
        double u = fade(xf);
        double v = fade(yf);
        double w = fade(zf);
        
        int aaa, aba, aab, abb, baa, bba, bab, bbb;
        aaa = p[p[p[    xi ]+    yi ]+    zi ];
        aba = p[p[p[    xi ]+inc(yi)]+    zi ];
        aab = p[p[p[    xi ]+    yi ]+inc(zi)];
        abb = p[p[p[    xi ]+inc(yi)]+inc(zi)];
        baa = p[p[p[inc(xi)]+    yi ]+    zi ];
        bba = p[p[p[inc(xi)]+inc(yi)]+    zi ];
        bab = p[p[p[inc(xi)]+    yi ]+inc(zi)];
        bbb = p[p[p[inc(xi)]+inc(yi)]+inc(zi)];
        
        double x1, x2, y1, y2;
        x1 = lerp(    grad (aaa, xf  , yf  , zf),           // The gradient function calculates the dot product between a pseudorandom
                    grad (baa, xf-1, yf  , zf),             // gradient vector and the vector from the input coordinate to the 8
                    u);                                     // surrounding points in its unit cube.
        x2 = lerp(    grad (aba, xf  , yf-1, zf),           // This is all then lerped together as a sort of weighted average based on the faded (u,v,w)
                    grad (bba, xf-1, yf-1, zf),             // values we made earlier.
                      u);
        y1 = lerp(x1, x2, v);

        x1 = lerp(    grad (aab, xf  , yf  , zf-1),
                    grad (bab, xf-1, yf  , zf-1),
                    u);
        x2 = lerp(    grad (abb, xf  , yf-1, zf-1),
                      grad (bbb, xf-1, yf-1, zf-1),
                      u);
        y2 = lerp (x1, x2, v);
        
        return (lerp (y1, y2, w)+1)/2;
        
    }
    static double grad(int hash, double x, double y, double z)
    {
        int h = hash % 15;
        double u = h < 8 ? x : y;
        double v;
        if (h < 4) v = y;
        else if (h == 12 || h == 14) v = x;
        else v = z;
        return ((h & 1) == 0? u: -u) + ((h % 2) == 0? v: -v);
    }
    static double lerp(double a, double b, double x)
    {
        return a + x * (b - a);
    }
    int inc(int num)
    {
        num++;
//        if (repeat > 0) num %= repeat;
        return num;
    }
    double fade(double t)
    {
        return t * t * t * (t * (6 * t - 15) + 10);
    }
    
    double OctavePerlin(double x, double y, double z, int octaves, double persistence, float zoom) {
        double total = 0;
        double frequency = 1;
        double amplitude = 1;
        double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
        for(int i=0; i<octaves; i++) {
            total += perlin(x * frequency * zoom, y * frequency * zoom, z * frequency * zoom) * amplitude;
            
            maxValue += amplitude;
            
            amplitude *= persistence;
            frequency *= 2;
        }
        
        return total/maxValue;
    }
};


#endif /* Noise_h */
