#pragma once


float clip(float n, float lower, float upper);

typedef float Kernel[3][3];

struct Color{
    // RGB is between 0 and 255, and an integer value, so short is optimal
    short R;
    short G;
    short B;
    Color(int red, int green, int blue);
    Color():R{0},G{0},B{0}{}
};

class Image {
private:
    Color * data; // Array of pixels
    unsigned int width; // Width of image
    unsigned int height; // Height of image
public:
    Image(unsigned int width, unsigned int height);
    Image(const Image &other);
    ~Image();
    //Image& operator=(Image rhs);
    Color getPixel(unsigned int x, unsigned int y);
    void setPixel(unsigned int x, unsigned int y, Color c);
    Image grayscale();
    Image threshold(unsigned int t);
    Image operator+(Image other);
    Color applyKernel(unsigned int x, unsigned int y, Kernel k);
    Image convolve(Kernel k);
};

