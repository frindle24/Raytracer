#ifndef _LIGHT_H
#define _LIGHT_H

#include "Color.h"
#include "Vector.h"

class Light {
    Vector position;
    Color color;

    public:
        Light ();
        Light (Vector, Color);

        // Method functions
        Vector getLightPosition() { return position; } // Have to be virtual values
        Color getLightColor() { return color; }

};

Light::Light () {
    position = Vector (0, 0, 0);
    color = Color (1, 1, 1, 0);
}

Light::Light (Vector p, Color c) {
    position = p;
    color = c;
}

#endif
