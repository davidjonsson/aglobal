#include "Light.h"

Light::Light()
{
    position = Vec3f(0,0,0);
    color = Vec3f(1,1,1);
}

Light::Light(float x, float y, float z)
{
    position = Vec3f(x, y, z);
    color = Vec3f(1,1,1);
}

Light::Light(Vec3f p)
{
    position = p;
    color = Vec3f(1,1,1);
}

void Light::setColor(Vec3f c)
{
    color = c;
}
