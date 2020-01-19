//
//  Shader.h
//  Perlin
//
//  Created by Kyle Burns on 1/19/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

class Shader
{
private:
    int h,w,tsize;
public:
    Shader(int width, int height, int tilesize)
    {
        h = height;
        w = width;
        tsize = tilesize;
    }
    void Shade(float x, float y, float z, MeshData* &obj)
    {
        float f;

        // normalize light source vector
        float mag = pow( x * x + y * y + z * z, 0.5f);
        x /= mag;
        y /= mag;
        z /= mag;
        // iterate through meshdata and shade
        for ( int i = 0; i < 2 * (w-1) * (h-1); i++)
        {
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
            f = x * obj->vectex[i].normal.x + y * obj->vectex[i].normal.y + z * obj->vectex[i].normal.z;

            // map f from (-1,1) to (0.0f, 1.0f) so it will be an appropriate factor
            f = (f + 1) / 2.0f;
            
            //adjust rgb values proportional to f
            obj->vectex[i].color.r *= f;
            obj->vectex[i].color.g *= f;
            obj->vectex[i].color.b *= f;
            
        }
            
    }
};

#endif /* Shader_h */


