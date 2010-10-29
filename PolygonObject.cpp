#include "PolygonObject.h"
#define SMALL_NUM  0.00000001

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
Vec3f PolygonObject::intersect(Ray* ray, Vec3f* normalR){

                        Vec3f u, v, n;
                        Vec3f dir, w0, w;
                        float r, a, b;

                        u = p2 - p1;
                        v = p3 - p1;

                        dir = ray->direction;
                        w0 = ray->start - p1;
                        a = -(normal.dot(w0));
                        b = normal.dot(dir);

                        if(fabs(b) < SMALL_NUM)
                        {
                            if(a == 0)
                                return Vec3f(0,0,0);
                            else
                                return Vec3f(0,0,0);
                        }

                        r = a / b;
                        if(r < 0.0)
                            return Vec3f(0,0,0);

                        Vec3f intersect = ray->start + dir * r;

                        float uu, uv, vv, wu, wv, D;
                        uu = u.dot(u);
                        uv = u.dot(v);
                        vv = v.dot(v);
                        w = intersect - p1;
                        wu = w.dot(u);
                        wv = w.dot(v);
                        D = uv * uv - uu * vv;

                        float s, t;
                        s = (uv * wv - vv * wu) / D;
                        if(s < 0.0 || s > 1.0)
                            return Vec3f(0,0,0);

                        t = (uv * wu - uu * wv) / D;
                        if(t < 0.0 || (s+t) > 1.0)
                            return Vec3f(0,0,0);

                        *normalR = normal;
                        ray->color = material.color;
                        return intersect;



/*
                       std::cout<<"Polygon Intersect"<<std::endl;
                       float den = ray->direction.dot(normal);

                       //om nämnare = 0 är ray/plan parallella och inte intressanta
                       if(den == 0)
                       return Vec3f(0,0,0);

                       else{

                       float num = (p1 - ray->start).dot(normal);

                       float d = num/den;
                       Vec3f intersect = ray->start + ray->direction * d;

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

                       ray->color = material.color;
                       return intersect;

                       //kolla  http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm
                       //för hur man på ett effektivt sätt kan testa om
                       //skärningspunkten definerad som
                       //ray.start + d * ray.direction
                       //ligger i triangeln definerad av p1,p2 och p3

                            }*/
                       }
