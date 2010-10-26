#ifndef SHAPE_H
#define SHAPE_H

#include "Vec3f.h"
#include "Ray.h"
#include "Material.h"

class Shape{
      public:
             Shape(){};
             Shape(Material mat) : material(mat){}; 
             
             Material getMaterial(){return material;};
            // virtual Vec3f intersect(ray r);
             virtual Vec3f intersect(Ray r) = 0;
             Material material;
             
      };

#endif


