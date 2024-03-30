#ifndef _PLANE_H
#define _PLANE_H

#include "Color.h"
#include "Object.h"
#include "Vector.h"

class Plane : public Object {
    Vector normal;
    double distance;
    Color color;

    public:
        Plane ();
        Plane (Vector, double, Color);

        // Method functions
        Vector getPlaneNormal() { return normal; } 
        double getPlaneDistance() { return distance; }
        Color getPlaneColor() { return color; }

        Vector getNormalAt (Vector point) {
            return normal;
        }

        double findIntersection (Ray ray) { // Ray already has a direction, so findIntersection returns distance
            Vector rayDirection = ray.getRayDirection();

            double a = rayDirection.dotProduct(normal);

            if (a == 0) {
                // Ray is parallel to the plane
                return -1;
            }
            else {
                double b = normal.dotProduct(ray.getRayOrigin().vectorAdd(normal.vectorScalarMult(distance).negative()));
                return -1 * b / a; // Distance from ray origin to point of intersection
            }
        }
};

Plane::Plane () {
    normal = Vector (1, 0, 0);
    distance = 0.0;
    color = Color (0.5, 0.5, 0.5, 0.0);
}

Plane::Plane (Vector normalValue, double distanceValue, Color colorValue) {
    normal = normalValue;
    distance = distanceValue;
    color = colorValue;
}

#endif
