#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>

class Vector {
    double x, y, z;

    public:
        Vector ();
        Vector (double, double, double);

        // Method functions
        double getVectorX() { return x; }
        double getVectorY() { return y; }
        double getVectorZ() { return z; }

        double magnitude () {
            return sqrt((x * x) + (y * y) + (z * z));
        }

        Vector normalize () {
            double magn = magnitude();
            return Vector (x / magn, y / magn, z / magn);
        }

        Vector negative () {
            return Vector (-x, -y, -z);
        }

        double dotProduct (Vector v) {
            return x * v.getVectorX() + y * v.getVectorY() + z * v.getVectorZ();
        }

        Vector crossProduct (Vector v) {
            return Vector (y * v.getVectorZ() - z * v.getVectorY(), z * v.getVectorX() - x * v.getVectorZ(), x * v.getVectorY() - y * v.getVectorX());
        }

        Vector vectorAdd (Vector v) {
            return Vector (x + v.getVectorX(), y + v.getVectorY(), z + v.getVectorZ());
        }

        Vector vectorScalarMult (double scalar) {
            return Vector (x * scalar, y * scalar, z * scalar);
        }

};

Vector::Vector () {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector (double i, double j, double k) {
    x = i;
    y = j;
    z = k;
}

#endif
