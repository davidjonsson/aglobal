#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "Vec3f.h"

//SKRIVA COPY CONSTRUCTORS!!!
class Ray{

      public:
             Ray(){};
             Ray(Vec3f s, Vec3f d, Vec3f c) : start(s), direction(d), color(c){
                       //MÅSTE FIXAS
                       //direction.normalize();
                       direction.normalize();
                       };
             Ray(const Ray& r){
                       this->start = r.start;
                       this->direction = r.direction;
                       this->color = r.color;
                       this->direction.normalize();
                       };

              void print(){
                   std::cout<<std::endl<<"Start: ";
                   start.print();
                   std::cout<<" "<<"Direction: ";
                   direction.print();
                   std::cout<<" "<<"Color: ";
                   color.print();
                   };
              Vec3f start, direction, color;


      };

#endif
