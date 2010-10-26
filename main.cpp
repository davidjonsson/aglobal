#include <iostream>
#include "Vec3f.h"
#include "Ray.h"
#include "Material.h"
#include "Shape.h"
#include "Sphere.h"
#include "Polygon.h"

using namespace std;
int main(){
   
    Vec3f start(0.3,0,10.0);
    //start.print();
    Vec3f end(0, -0.10, -50.0);
    Vec3f color(0.5,0.5,0.5);
   
    Ray r(start,end,color);
    r.print();
    // std::cout<<"hej2";
    Material mat(0.4,0.4,0.4, 0.6, 0.4);
   // mat.print();
    
    Polygon p(Vec3f(0,0,-150),Vec3f(1,0,-150),Vec3f(0,1,-150));
    
    //Shape s(mat);
    //s.getMaterial().print();
   Sphere sphere(0.5, Vec3f(0,0,0), mat);
   
  // Sphere s(0.5,start,mat);
  // s.material.print();
 

   Shape* sArray[2];
   sArray[0] = &sphere;
   sArray[1] = &p;

   for(int i = 0; i < 2; i++)
       sArray[i]->intersect(r).print();


   /* 
    //Material mat(1,1,1);
    hej.print();
    hej = Vec3f(0,0,1);
    hej.print();
    Ray r(Vec3f(1,0,0), Vec3f(0,1,0));
    
    r.start.print();
    r.direction.print();
   // mat.color.print();
   */
  // Sphere s(0.5,Vec3f(1,1,1), Material(1,1,1));
  //
   
   
    system("pause");
    return 0;
    };
