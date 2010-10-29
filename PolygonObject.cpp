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

                       }
PolygonObject::PolygonObject(Vec3f pOne, Vec3f pTwo, Vec3f pThree, Material mat) : Shape::Shape(mat){

                       p1 = pOne;
                       p2 = pTwo;
                       p3 = pThree;
                       Vec3f v1, v2;
                       v1 = (p2-p1);
                       v2 = (p1-p3);
                       normal = v1.cross(v2);
                       normal.normalize();

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



                       }
