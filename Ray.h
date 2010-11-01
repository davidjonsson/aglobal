#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"
//#include "Shape.h"


//SKRIVA COPY CONSTRUCTORS!!!
class Ray{

      public:
             Ray(){};
             Ray(Vec3f s, Vec3f d, Vec3f c) : start(s), direction(d), color(c) {
                       //MÅSTE FIXAS
                       //direction.normalize();
                       direction.normalize();
                       };
             Ray(const Ray& r){
                       this->start = r.start;
                       this->direction = r.direction;
                       this->color = r.color;
                       };
       //      Vec3f traceRay(PolygonObject s);
      //      Vec3f traceRay(Shape* theShapes, Ray& r,int numShapes, int currentDepth);

              Vec3f start, direction, color;
      };

#endif
