#ifndef _RAY_H
#define _RAY_H

#include "Vector.h"

class Ray {
    Vector origin, direction;

    public:
        Ray ();
        Ray (Vector, Vector);

        // Method functions
        Vector getRayOrigin() { return origin; }
        Vector getRayDirection() { return direction; }

};

Ray::Ray () {
    origin = Vector (0, 0, 0);
    direction = Vector (1, 0, 0);
}

Ray::Ray (Vector o, Vector d) {
    origin = o;
    direction = d;
}

#endif
