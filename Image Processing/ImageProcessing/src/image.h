#include <string>
#include <vector>
using namespace std;

struct Header {

    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

};
struct Pixel {

    unsigned char blue;
    unsigned char green;
    unsigned char red;

};

class image {

    Header header;
    vector<Pixel> pixels;

public:

    image(string filePath);
    Header getHeader();
    vector<Pixel> getPixels();
    void WriteTga(string filePath);
    void Multiply(image pic, string fileName);
    void Subtract(image pic, string fileName);
    int Clamp(int num);
    void Screen(image pic, string fileName);
    void Overlay(image pic, string fileName);
    void Add(char color, int amount, string fileName);
    void Scale(int redScale, int blueScale, string fileName);
    void WriteChannels(string filePath);
    void CombineFiles(image file1, image file2, string fileName);
    void Flip(string fileName);
    void Quadrant(image topRight, image bottomRight, image bottomLeft, string fileName);

};