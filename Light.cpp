#include "Light.h"
#include "PolygonObject.h"

Light::~Light() {

   // delete polygons[0];
   // delete polygons[1];


}
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
    color = Vec3f(255,255,255);
    width = w;
    length = l;
    normal = Vec3f(0,1,0);
    Material mat(1,1,1,0,0);
    Vec3f p1(x, y, z), p2(x + w, y, z), p3(x + w, y, z - l), p4(x, y, z - l);

    poly1 = PolygonObject(p1,p3,p2);
    poly2 = PolygonObject(p1,p4,p3);
    polygons[0] = &poly1;
    polygons[1] = &poly2;


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
    this->getMaterial().color = c;
    color = c;
}

Vec3f Light::intersect(Ray* r, Vec3f* normalR){

return Vec3f(0,0,0);

    Vec3f hit = polygons[0]->intersect(r,normalR);
    if(!(hit.x == 0 && hit.y == 0 && hit.z == 0)){
        return hit;
    }
    else
        hit = polygons[1]->intersect(r,normalR);

    if(!(hit.x == 0 && hit.y == 0 && hit.z == 0)){
        return hit;
    }
    else
    return Vec3f(0,0,0);

//implmentera denna sedan!!!
}
