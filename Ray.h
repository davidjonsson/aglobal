#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"
//#include "Shape.h"


//SKRIVA COPY CONSTRUCTORS!!!
class Ray{

      public:
             Ray(){};
             Ray(Vec3f s, Vec3f d, Vec3f c,float w) : start(s), direction(d), color(c), weight(w) {
                       direction.normalize();
                       };
             Ray(const Ray& r){
                       this->start = r.start;
                       this->direction = r.direction;
                       this->color = r.color;
                       this->weight = r.weight;
                       };
       //      Vec3f traceRay(PolygonObject s);
      //      Vec3f traceRay(Shape* theShapes, Ray& r,int numShapes, int currentDepth);

              Vec3f start, direction, color;
              float weight;
      };

#endif
