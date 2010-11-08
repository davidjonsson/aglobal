#include "PolygonObject.h"

PolygonObject::PolygonObject(Vec3f pOne, Vec3f pTwo, Vec3f pThree){
                       p1 = pOne;
                       p2 = pTwo;
                       p3 = pThree;
                       Vec3f v1, v2;
                       v1 = (p2-p1);
                       v2 = (p1-p3);
                       normal = v1.cross(v2);
                       normal.normalize();
                       material = Material::Material(0,0,0,0,0);
                       }
PolygonObject::PolygonObject(Vec3f pOne, Vec3f pTwo, Vec3f pThree, Material mat){

                       p1 = pOne;
                       p2 = pTwo;
                       p3 = pThree;
                       Vec3f v1, v2;
                       v1 = (p2-p1);
                       v2 = (p1-p3);
                       normal = v1.cross(v2);
                       normal.normalize();
                       material = mat;
                       }
Vec3f PolygonObject::intersect(Ray ray){
                       float den = ray.direction.dot(normal);

                       //om nämnare = 0 är ray/plan parallella och inte intressanta
                       if(den == 0)
                       return Vec3f(0,0,0);

                       else{

                       float num = (p1 - ray.start).dot(normal);

                       float d = num/den;
                       Vec3f intersect = ray.start + ray.direction * d;

                       Vec3f u = (p2-p1);
                       Vec3f v = (p1-p3);
                       float uu = u.dot(u);
                       float uv = u.dot(v);
                       float vv = v.dot(v);
                       Vec3f w = (intersect- p1);
                       float wu = w.dot(u);
                       float wv = w.dot(v);

                       den = uv * uv - uu * vv;
                       float s,t;

                       s = (uv*wv - vv*wu)/den;
                       if(s < 0.0 || s > 1.0)
                            return Vec3f(0,0,0);

                       t = (uv * wu - uu * wv)/den;
                       if(t < 0.0 || (s+t) > 1.0)
                            return Vec3f(0,0,0);

                       return intersect;
                       //kolla  http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm
                       //för hur man på ett effektivt sätt kan testa om
                       //skärningspunkten definerad som
                       //ray.start + d * ray.direction
                       //ligger i triangeln definerad av p1,p2 och p3

                            }
                       }
