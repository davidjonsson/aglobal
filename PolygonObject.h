#ifndef POLYGONOBJECT_H
#define POLYGONOBJECT_H

#include "Shape.h"
class PolygonObject : public Shape
{
      public:
             Vec3f p1, p2, p3,normal;
             Material material;

             PolygonObject() : p1(Vec3f(0,0,0)), p2(Vec3f(0,0,0)), p3(Vec3f(0,0,0)), normal(Vec3f(0,0,0))
                       ,material(Material::Material(0,0,0,0,0)){};
             PolygonObject(Vec3f, Vec3f, Vec3f);
             PolygonObject(Vec3f, Vec3f, Vec3f, Material);
             Vec3f intersect(Ray* r, Vec3f* normalR);


      };
#endif
