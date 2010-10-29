#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3f.h"

class Light
{
    public:
        Light();
        Light(float x, float y, float z);
        Light(Vec3f position);

        void setColor(Vec3f c);
        Vec3f position, color;
};

#endif // LIGHT_H_INCLUDED
