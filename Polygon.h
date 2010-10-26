#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
class Polygon : public Shape
{
      public:
             Vec3f p1, p2, p3,normal;
             Material material;
             
             Polygon() : p1(Vec3f(0,0,0)), p2(Vec3f(0,0,0)), p3(Vec3f(0,0,0)), normal(Vec3f(0,0,0))
                       ,material(Material::Material(0,0,0,0,0)){};
             Polygon(Vec3f, Vec3f, Vec3f);
             Polygon(Vec3f, Vec3f, Vec3f, Material);
             Vec3f intersect(Ray);
      
      
      };
#endif
