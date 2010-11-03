#include "Sphere.h"

Sphere::Sphere(): radius(0), origin(Vec3f(0,0,0))
                        , Shape::Shape(Material(0,0,0,0,0)){}
Sphere::Sphere(float r, Vec3f ori, Material mat) : radius(r), origin(ori)
                        , Shape::Shape(mat) {}

Vec3f Sphere::intersect(Ray* ray, Vec3f* normalR){

      std::cout<<"Sphere Intersect"<<std::endl;
      Vec3f raySphere = origin - ray->start;
      float d = raySphere.dot(ray->direction); //direction normaliserad annars division
      float length2 = raySphere.lengthSquare();
      float radius2 = radius*radius;


      if((d < 0) && (length2 > radius2)) //ray pekar bort från sfär och ray börjar ej inom sfär
      return Vec3f(0,0,0);

      float m2 = length2 - d*d;
      if(m2 > radius2)
      return Vec3f(0,0,0);

      float q = sqrt(radius2-m2);
      float t = 0;
      if(length2 > radius2)
      t = d - q;
      else
      t = d + q;


      ray->color = material.color;
      *normalR = (ray->start + ray->direction * t) - origin;

      return (ray->start + ray->direction * t);
      }

/*
Sphere::Sphere(float rad, Vec3f ori, Material mat){}

Vec3f Sphere::intersect(Ray r){
                      return Vec3f(0,0,0);
                      }
*/
