#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>

#include "Vec3f.h"
class Material{
      public:
             Material(){};
             Material(float r, float g, float b,float wr,float wt){
                            color = Vec3f(r,g,b);
                            wR = wr;
                            wT = wt;
                            }
             Material(const Material& mat){
                            *this = mat;
                            };

              void print(){
                      std::cout<<"Material color: ";
                      color.print();
                      std::cout<<"WR:" << wR<<" WT: "<<wT<<std::endl;
                      };
              const Material& operator=(const Material& mat){
                    this->color = mat.color;
                    this->wR = mat.wR;
                    this->wT = mat.wT;
                    return *this;
                    };
              Vec3f color;
              float wR,wT;



      };

#endif
