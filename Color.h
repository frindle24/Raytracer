#ifndef _Color_H
#define _Color_H

class Color {
    double red, green, blue, special; // Use the special value to add reflectivity and shininess

    public:
        Color ();
        Color (double, double, double, double);

        // Method functions
        double getColorRed() { return red; }
        double getColorGreen() { return green; }
        double getColorBlue() { return blue; }
        double getColorSpecial() { return special; }

        // Setter functions
        void setColorRed(double redValue) { red = redValue; }
        void setColorGreen(double greenValue) { green = greenValue; }
        void setColorBlue(double blueValue) { blue = blueValue; }
        void setColorSpecial(double specialValue) { special = specialValue; }

};

Color::Color () {
    red = 0.5;
    green = 0.5;
    blue = 0.5;
}

Color::Color (double r, double g, double b, double s) {
    red = r;
    green = g;
    blue = b;
    special = s;
}

#endif
