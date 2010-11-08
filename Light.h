#ifndef LIGHT_H
#define LIGHT_H
#include "Shape.h"
#include "Vec3f.h"
#include "PolygonObject.h"

class Light : public Shape
{
    public:
        Light();
        Light(float x, float y, float z);
        Light(Vec3f position);
        Light(Vec3f p, float w, float l);
        Light(float x, float y, float z, float w, float l);
        ~Light();
        Vec3f intersect(Ray* r, Vec3f* normalR);
        void setColor(Vec3f c);
        Vec3f position, color, normal;
        float width, length;
        PolygonObject poly1,poly2;
        PolygonObject* polygons[2];
};

#endif // LIGHT_H_INCLUDED
