#ifndef _SPHERE_H
#define _SPHERE_H

#include "Color.h"
#include "Object.h"
#include "Vector.h"

class Sphere : public Object {
    Vector center;
    double radius;
    Color color;

    public:
        Sphere ();
        Sphere (Vector, double, Color);

        // Method functions
        Vector getSphereCenter() { return center; } 
        double getSphereRadius() { return radius; }
        Color getSphereColor() { return color; }
        
        Vector getNormalAt(Vector point) {
            Vector normal = point.vectorAdd(center.negative()) .normalize();
            return normal;
        }

        double findIntersection(Ray ray) {
            Vector rayOrigin = ray.getRayOrigin();
            double rayOriginX = rayOrigin.getVectorX();
            double rayOriginY = rayOrigin.getVectorY();
            double rayOriginZ = rayOrigin.getVectorZ();

            Vector rayDirection = ray.getRayDirection();
            double rayDirectionX = rayOrigin.getVectorX();
            double rayDirectionY = rayOrigin.getVectorY();
            double rayDirectionZ = rayOrigin.getVectorZ();

            Vector sphereCenter = center;
            double sphereCenterX = sphereCenter.getVectorX();
            double sphereCenterY = sphereCenter.getVectorY();
            double sphereCenterZ = sphereCenter.getVectorZ();

            double a = 1;
            double b = (2 * (rayOriginX - sphereCenterX) * rayDirectionX) + (2 * (rayOriginY - sphereCenterY) * rayDirectionY) + (2 * (rayOriginZ - sphereCenterZ) * rayDirectionZ);
            double c = pow(rayOriginX - sphereCenterX, 2) + pow(rayOriginY - sphereCenterY, 2) + pow(rayOriginZ - sphereCenterZ, 2) - (radius * radius);

            double discriminant = b * b - 4 * c;

            if (discriminant > 0) {
                // Ray intersects the sphere
                // Two roots, one on either side of the sphere

                double root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001; // Deals with accuracy errors while doing linear algebra computations

                if (root1 > 0) {
                    // First root is the smallest positive root
                    return root1;
                }

                else {
                    // Second root is the smallest postive root
                    double root2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
                    return root2;
                }
            }

            else {
                // Ray misses the sphere
                return -1;
            }
        }

};

Sphere::Sphere () {
    center = Vector (0, 0, 0);
    radius = 1.0;
    color = Color (0.5, 0.5, 0.5, 0.0);
}

Sphere::Sphere (Vector centerValue, double radiusValue, Color colorValue) {
    center = centerValue;
    radius = radiusValue;
    color = colorValue;
}

#endif
