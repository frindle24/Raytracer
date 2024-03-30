#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector.h"

class Camera {
    Vector camPosition, camDirection, camRight, camDown;

    public:
        Camera ();
        Camera (Vector, Vector, Vector, Vector);

        // Method functions
        Vector getCameraPosition () { return camPosition; }
        Vector getCameraDirection () { return camPosition; }
        Vector getCameraRight () { return camRight; }
        Vector getCameraDown() { return camDown; }

};

Camera::Camera () {
    camPosition = Vector (0, 0, 0);
    camDirection = Vector (0, 0, 1);
    camRight = Vector(0, 0, 0);
    camDown = Vector(0, 0, 0);
}

Camera::Camera (Vector pos, Vector dir, Vector right, Vector down) {
    camPosition = pos;
    camDirection = dir;
    camRight = right;
    camDown = down;
}

#endif
