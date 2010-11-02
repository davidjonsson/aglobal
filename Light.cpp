#include "Light.h"

Light::Light()
{
    position = Vec3f(0,0,0);
    color = Vec3f(1,1,1);
    width = 0;
    length = 0;
    normal = Vec3f(0,1,0);
}

Light::Light(float x, float y, float z)
{
    position = Vec3f(x, y, z);
    color = Vec3f(1,1,1);
    width = 0;
    length = 0;
    normal = Vec3f(0,1,0);
}

Light::Light(float x, float y, float z, float w, float l)
{
    position = Vec3f(x, y, z);
    color = Vec3f(1,1,1);
    width = w;
    length = l;
    normal = Vec3f(0,1,0);
}

Light::Light(Vec3f p)
{
    position = p;
    color = Vec3f(1,1,1);
    width = 0;
    length = 0;
    normal = Vec3f(0,1,0);
}


Light::Light(Vec3f p, float w, float l)
{
    position = p;
    color = Vec3f(1,1,1);
    width = w;
    length = l;
    normal = Vec3f(0,1,0);
}
void Light::setColor(Vec3f c)
{
    color = c;
}

Vec3f Light::intersect(Ray* r, Vec3f* normalR){

//implmentera denna sedan!!!
}
