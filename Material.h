#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#define DIFFUSE 1
#define SPECULAR 2
#define REFLECTIVE 3
#define TRANSMITIVE 4
#define GLASS 5
#include "Vec3f.h"
class Material{
      public:
             Material(){};
             Material(float r, float g, float b,float wr,float wt){
                            color = Vec3f(r,g,b);
                            wR = wr;
                            wT = wt;
                            specH = 0;
                            specI = 0;
                            refrIndex = 1.55;
                            if(wR > 0 && wT > 0 && specH >0 && specI > 0)
                            type = GLASS;
                            else if(wR >0)
                            type = REFLECTIVE;
                            else if(wT > 0)
                            type = TRANSMITIVE;
                            else if(specH >0 && specI > 0)
                            type = SPECULAR;
                            else
                            type = DIFFUSE;
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
                    this->specH = mat.specH;
                    this->specI = mat.specI;
                    this->type = mat.type;
                    return *this;
                    };
              Material setSpecular(float hardness,float intensity)
              {
                  this->specH  = hardness;
                  this->specI  = intensity;
                  return *this;
              };
              int getType()
              {
                  return this->type;
              }

              Vec3f color;
              float wR,wT,refrIndex, specI,specH,type;

      };



#endif
