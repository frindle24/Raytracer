#include <cmath>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector.h"

const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

using namespace std;

struct RGBType {
    double r;
    double g;
    double b;
};

// Refer to README.md for an explanation of the below function
// We pass color data to this function which returns a file
void saveBMP(const char* fileName, int width, int height, int DPI, RGBType* data) {
    FILE* file;
    int totalPixels = width * height;
    int pixelDataSize = 4 * totalPixels;
    int fileSize = pixelDataSize + FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    double factor = 39.375; // Conversion factor that converts inches to meters (DPI to PPM)
    int m = static_cast<int>(factor);

    int PPM = DPI * m;

    unsigned char BMPFileHeader[FILE_HEADER_SIZE] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char BMPInfoHeader[INFO_HEADER_SIZE] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

    BMPFileHeader[ 2] = (unsigned char)(fileSize);
    BMPFileHeader[ 3] = (unsigned char)(fileSize >> 8);
    BMPFileHeader[ 4] = (unsigned char)(fileSize >> 16);
    BMPFileHeader[ 5] = (unsigned char)(fileSize >> 24);

    BMPInfoHeader[ 4] = (unsigned char)(width);
    BMPInfoHeader[ 5] = (unsigned char)(width >> 8);
    BMPInfoHeader[ 6] = (unsigned char)(width >> 16);
    BMPInfoHeader[ 7] = (unsigned char)(width >> 24);

    BMPInfoHeader[ 8] = (unsigned char)(height);
    BMPInfoHeader[ 9] = (unsigned char)(height >> 8);
    BMPInfoHeader[10] = (unsigned char)(height >> 16);
    BMPInfoHeader[11] = (unsigned char)(height >> 24);

    BMPInfoHeader[21] = (unsigned char)(pixelDataSize);
    BMPInfoHeader[22] = (unsigned char)(pixelDataSize >> 8);
    BMPInfoHeader[23] = (unsigned char)(pixelDataSize >> 16);
    BMPInfoHeader[24] = (unsigned char)(pixelDataSize >> 24);

    BMPInfoHeader[25] = (unsigned char)(PPM);
    BMPInfoHeader[26] = (unsigned char)(PPM >> 8);
    BMPInfoHeader[27] = (unsigned char)(PPM >> 16);
    BMPInfoHeader[28] = (unsigned char)(PPM >> 24);

    BMPInfoHeader[29] = (unsigned char)(PPM);
    BMPInfoHeader[30] = (unsigned char)(PPM >> 8);
    BMPInfoHeader[31] = (unsigned char)(PPM >> 16);
    BMPInfoHeader[32] = (unsigned char)(PPM >> 24);

    file = fopen(fileName, "wb"); // File opened in write and binary mode

    fwrite(BMPFileHeader, 1, 14, file);
    fwrite(BMPInfoHeader, 1, 40, file);

    for (int i = 0; i < totalPixels; i++) {
        RGBType rgb = data[i];

        double red = (data[i].r) * 255;
        double green = (data[i].g) * 255;
        double blue = (data[i].b) * 255;

        unsigned char color[3] = {(unsigned char)(int)floor(blue), (unsigned char)(int)floor(green), (unsigned char)(int)floor(red)};

        fwrite(color, 1, 3, file);
    }

    fclose(file);
}

int significantObjectIndex(vector<double> objectIntersections) {
    // Index of significant intersection
    int minimumValueIndex;

    // Prevent unnecessary calculations

    if (objectIntersections.size() == 0) {
        return -1;
    }
    else if (objectIntersections.size() == 1) {
        if (objectIntersections[0] > 0) {
            // If intersection is greater than 0, it is the index of the minimum value
            return 0;
        }
        else {
            // The only intersection is negative
            return -1;
        }
    }
    else {
        // Find maximum value

        double maxValue = 0;
        int n = objectIntersections.size();
        for (int i = 0; i < n; i++) {
            maxValue = max(maxValue, objectIntersections[i]);
        }

        // Starting from the maximum value find the minimum positive
        if (maxValue > 0) {
            // We want positive intersections only
            for (int i = 0; i < n; i++) {
                if (objectIntersections[i] > 0 && objectIntersections[i] <= maxValue) {
                    maxValue = objectIntersections[i];
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "Rendering...\n";
    
    int DPI = 72;
    int width = 640;
    int height = 480;
    double aspectRatio = (double)width/height;
    int n = width * height;
    RGBType* pixels = new RGBType[n];
    
    Vector O (0, 0, 0);
    Vector X (1, 0, 0);
    Vector Y (0, 1, 0);
    Vector Z (0, 0, 1);

    // Camera
    Vector camPosition (3, 1.4, -4);

    Vector lookAt (0, 0, 0); // Point we want the camera to look at
    Vector diffBtw (camPosition.getVectorX() - lookAt.getVectorX(), camPosition.getVectorY() - lookAt.getVectorY(), camPosition.getVectorZ() - lookAt.getVectorZ());
    
    Vector camDirection = diffBtw.negative().normalize(); // Vector pointing from camera towards the point we're looking at
    Vector camRight = Y.crossProduct(camDirection).normalize();
    Vector camDown = camRight.crossProduct(camDirection);

    Camera sceneCam (camPosition, camDirection, camRight, camDown);

    // Light
    Color whiteLight (1.0, 1.0, 1.0, 0.0);
    Color prettyGreen (0.5, 1.0, 0.5, 0.3);
    Color maroon (0.5, 0.25, 0.25, 0.0);
    Color gray (0.5, 0.5, 0.5, 0.0);
    Color black (0.0, 0.0, 0.0, 0.0);

    Vector lightPositon(-7, 10, -10);
    Light sceneLight (lightPositon, whiteLight);

    // Scene objects

    // Spheres
    Sphere sceneSphere (O, 1, prettyGreen);
    Plane scenePlane (Y, -1.0, maroon);

    vector<Object*> sceneObjects;
    sceneObjects.push_back(dynamic_cast<Object*>(&sceneSphere)); // Checks if cast from Object* to Sphere* is valid
    sceneObjects.push_back(dynamic_cast<Object*>(&scenePlane));

    // Assign a color to every pixel in the image
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int currentIndex = y * width + x; // Changed from global, maybe implement with 2-D array

            double xAmount, yAmount; // Values slighty to the left and right of direction camera points to
            // Start with no anti-aliasing
            if (width > height) {
                // Wider than taller
                xAmount = ((x + 0.5) / width) * aspectRatio - (((width - height) / (double(height)) / 2));
                yAmount = ((height - y) + 0.5) / height;
            }
            else if (height > width) {
                // Taller than wider
                xAmount = (x + 0.5) / width;
                yAmount = (((height - y) + 0.5) / height) / aspectRatio - (((height - width) / (double)width) / 2);
            }
            else {
                // Square image
                xAmount = (x + 0.5) / width;
                yAmount = ((height - y) + 0.5) / height;
            }
            // Offset a position from direction our camera is pointing to create rays that go left, right, up and down of that direction
            // Image plane in front of a camera, we need rays to go left, right, up and down of cam direction in order to cover the image plane

            Vector camRayOrigin = sceneCam.getCameraPosition(); // Ray originates from camera
            Vector camRayDirection = camDirection.vectorAdd(camRight.vectorScalarMult(xAmount - 0.5).vectorAdd(camDown.vectorScalarMult(yAmount - 0.5))).normalize();

            Ray camRay (camRayOrigin, camRayDirection); // Ray which goes through the x,y pixel into screen to look for intersection with objects

            // Look for intersections

            vector<double> intersections;

            // Loop through each object in a scene, and determine if the ray intersects any of those objects
            int n = sceneObjects.size();
            for (int i = 0; i < n; i++) {
                intersections.push_back(sceneObjects.at(i)->findIntersection(camRay)); // Intersection of each object with camRay
            }

            int indexOfSignificantObject = significantObjectIndex(intersections); // Object closest to camera which the ray intersected first

            if ((x > 200 && x < width - 200) && (y > 200 && y < height - 200)) {
                pixels[currentIndex].r = 23;
                pixels[currentIndex].g = 222;
                pixels[currentIndex].b = 10;
            }

            else {
                pixels[currentIndex].r = 0;
                pixels[currentIndex].g = 0;
                pixels[currentIndex].b = 0;
            }
        }
    }

    saveBMP("solid.bmp", width, height, DPI, pixels);

    return 0;
}
