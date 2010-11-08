#ifndef PHOTON_H
#define PHOTON_H

#include "Vec3f.h"

class Photon {
    public:
        Photon() : direction(Vec3f(0,0,0)), position(Vec3f(0,0,0)), color(Vec3f(0,0,0)), shadowPhoton(false) { direction.normalize(); }
        Photon(Vec3f d, Vec3f p, Vec3f c, bool s) : direction(d), position(p), color(c), shadowPhoton(s) { direction.normalize(); }
        Photon(const Photon& p) { *this = p; }

        Vec3f direction, position, color;
        bool shadowPhoton;
};

#endif // PHOTON_H
