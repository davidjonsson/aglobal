#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"

class Sphere : public Shape{
      
      public:
              Sphere();
              Sphere(float, Vec3f, Material);
      
             float radius;
             Vec3f origin;
           
             Vec3f intersect(Ray r);
      
            // Vec3f getNormal(Vec3f p){return origin-p;};
             
             
      };
      
     

#endif
