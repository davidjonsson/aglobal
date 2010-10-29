#ifndef VEC3F_H
#define VEC3F_H
#include <math.h>

class Vec3f
{
    public:
     float x,y,z;

     Vec3f(float x,float y,float z);
     Vec3f();
     Vec3f(const Vec3f& v);
     float dot(Vec3f v);
     float angle(Vec3f v);
     float length();
     float lengthSquare();
     Vec3f cross(Vec3f v);
     void normalize();

     Vec3f operator+(const Vec3f v);
     Vec3f operator-(const Vec3f v);
     Vec3f operator*(const float mult);
     Vec3f operator*(const Vec3f v);
     Vec3f operator/(const float mult);
     const Vec3f& operator=(const Vec3f& v);
     void print();



};

#endif
