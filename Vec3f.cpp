#include "Vec3f.h"
#include <iostream>

Vec3f::Vec3f(float x,float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vec3f::Vec3f()
{
    x = y = z = 0;
}

Vec3f::Vec3f(const Vec3f& v){
                   *this = v;
                   }


Vec3f Vec3f::operator+(const Vec3f v)
{
  Vec3f tmp;

  tmp.x = x+v.x;
  tmp.y = y+v.y;
  tmp.z = z+v.z;
  return tmp;
}

Vec3f Vec3f::operator-(const Vec3f v)
{
  Vec3f tmp;

  tmp.x = x-v.x;
  tmp.y = y-v.y;
  tmp.z = z-v.z;
  return tmp;
}

Vec3f Vec3f::operator*(const float mult)
{
  Vec3f tmp;

  tmp.x = x*mult;
  tmp.y = y*mult;
  tmp.z = z*mult;
  return tmp;
}

Vec3f Vec3f::operator*(const Vec3f v){
    Vec3f tmp;
    tmp.x = this->x * v.x;
    tmp.y = this->y * v.y;
    tmp.z = this->z * v.z;
    return tmp;
}

Vec3f Vec3f::operator/(const float mult)
{
  Vec3f tmp;

  tmp.x = x/mult;
  tmp.y = y/mult;
  tmp.z = z/mult;
  return tmp;
}

const Vec3f& Vec3f::operator=(const Vec3f& v)
{

  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return *this;

}

float Vec3f::dot(Vec3f v)
{
    float tmp = x*v.x + y*v.y + z*v.z;
    return tmp;
}

float Vec3f::angle(Vec3f v)
{
    float angle;
    angle = acos((this->dot(v))/(this->length() * v.length()));
    return angle;
}

float Vec3f::length()
{
    return sqrt(this->lengthSquare());
}

float Vec3f::lengthSquare()
{
    float lengthSqr;
    lengthSqr = x*x + y*y + z*z;
    return lengthSqr;
}

Vec3f Vec3f::cross(Vec3f v)
{
    Vec3f tmp;
    tmp.x = this->y*v.z - this->z*v.y;
    tmp.y = this->x*v.z - this->z*v.x;
    tmp.z = this->x*v.y - this->y*v.x;
    return tmp;
}

void Vec3f::normalize(){
     float l = this->length();
     if(l > 0)
     *this = *this/l;
     }
void Vec3f::print(){
               std::cout<<"("<<this->x<<", "<<this->y<<", "<<this->z<<")"<<std::endl;
               }
