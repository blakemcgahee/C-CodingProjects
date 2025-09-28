#include <iostream>
#include <fstream>
#include "image.h"
using namespace std;

image::image(string filePath) {

    ifstream file(filePath, ios_base::binary);

    Header headerObject{};

    // get header object to provide image details 
    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file.read((char*)&headerObject.width, sizeof(headerObject.width));
    file.read((char*)&headerObject.height, sizeof(headerObject.height));
    file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    header = headerObject;

    // get pixel colors from header object
    int size = headerObject.width * headerObject.height;
    int currentPixel = 0;
    while (currentPixel < size) {

        Pixel pixel;
        file.read((char*)&pixel.blue, sizeof(pixel.blue));
        file.read((char*)&pixel.green, sizeof(pixel.green));
        file.read((char*)&pixel.red, sizeof(pixel.red));
        pixels.push_back(pixel);
        currentPixel++;

    }
    file.close();
}

Header image::getHeader() {
    return header;
}

vector<Pixel> image::getPixels() {
    return pixels;
}

void image::WriteTga(string filePath) {

    ofstream file(filePath, ios_base::binary);
    if (file.is_open()) {

        file.write(&header.idLength, sizeof(header.idLength));
        file.write(&header.colorMapType, sizeof(header.colorMapType));
        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char*)&header.width, sizeof(header.width));
        file.write((char*)&header.height, sizeof(header.height));
        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < pixels.size(); i++) {

            file.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            file.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            file.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));

        }
        file.close();
    }
}


void image::Multiply(image pic, string fileName) {

    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.getPixels();
    vector<Pixel> newPixels;


    int size = pic.getHeader().width * pic.getHeader().height;
    int i = 0;
    while (i < size) {

        Pixel pixel;

        // convert color 255 to 1
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;

        // multply and round
        int redProduct = (int) ((red * red2 * 255) + 0.5f);
        int greenProduct = (int) ((green * green2 * 255) + 0.5f);
        int blueProduct = (int) ((blue * blue2 * 255) + 0.5f);

        // convert int to char for pixel assignment
        pixel.red = (unsigned char) redProduct;
        pixel.green = (unsigned char) greenProduct;
        pixel.blue = (unsigned char) blueProduct;
        newPixels.push_back(pixel);
        i++;

    }

    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Subtract(image pic, string fileName) {

    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.getPixels();
    vector<Pixel> newPixels;

    int size = pic.getHeader().width * pic.getHeader().height;
    int i = 0;
    while (i < size) {

        Pixel pixel;
        // return colors
        int red = (int) topPixels.at(i).red;
        int green = (int) topPixels.at(i).green;
        int blue = (int) topPixels.at(i).blue;
        int red2 = (int) botPixels.at(i).red;
        int green2 = (int) botPixels.at(i).green;
        int blue2 = (int) botPixels.at(i).blue;

        // difference of top values from bot values with clamp boundry
        int redDif = Clamp(red2 - red);
        int greenDif = Clamp(green2 - green);
        int blueDif = Clamp(blue2 - blue);

        // convert int to char for pixel assignment
        pixel.red = (unsigned char) redDif;
        pixel.green = (unsigned char) greenDif;
        pixel.blue = (unsigned char) blueDif;
        newPixels.push_back(pixel);
        i++;

    }

    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

// clamp boundry limit of 255
int image::Clamp(int num) {

    return max(0, min(num, 255));

}

void image::Screen(image pic, string fileName) {

    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.getPixels();
    vector<Pixel> newPixels;

    int size = pic.getHeader().width * pic.getHeader().height;
    int i = 0;
    while (i < size) {

        Pixel pixel;

        // return colors
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;

        // calculate final results of color
        int redFinal = (int) ((1 - (1-red) * (1-red2)) * 255 + 0.5f);
        int greenFinal = (int) ((1 - (1-green) * (1-green2)) * 255 + 0.5f);
        int blueFinal = (int) ((1 - (1-blue) * (1-blue2)) * 255 + 0.5f);

        // convert int to char for pixel assignment
        pixel.red = (unsigned char) redFinal;
        pixel.green = (unsigned char) greenFinal;
        pixel.blue = (unsigned char) blueFinal;
        newPixels.push_back(pixel);
        i++;

    }

    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Overlay(image pic, string fileName) {

    image bot = pic;
    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = bot.pixels;
    vector<Pixel> newPixels;

    int size = bot.header.width * bot.header.height;
    int i = 0;
    while (i < size) {

        Pixel pixel;

        // get colors
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;

        // compare colors for final results
        int redFinal = 0;
        int greenFinal = 0;
        int blueFinal = 0;
        if (red2 <= 0.5) {
            redFinal = (int) ((2 * red * red2 * 255) + 0.5f);
        } else {
            redFinal = (int) ((1 - 2*(1-red) * (1-red2)) * 255 + 0.5f);
        }
        if (green2 <= 0.5) {
            greenFinal = (int) ((2 * green * green2 * 255) + 0.5f);
        } else {
            greenFinal = (int) ((1 - 2*(1-green) * (1-green2)) * 255 + 0.5f);
        }
        if (blue2 <= 0.5) {
            blueFinal = (int) ((2 * blue * blue2 * 255) + 0.5f);
        } else {
            blueFinal = (int) ((1 - 2*(1-blue) * (1-blue2)) * 255 + 0.5f);
        }

        // convert int to char for pixel assignment
        pixel.red = (unsigned char) redFinal;
        pixel.green = (unsigned char) greenFinal;
        pixel.blue = (unsigned char) blueFinal;
        newPixels.push_back(pixel);
        i++;

    }

    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Add(char color, int amount, string fileName) {

    vector<Pixel> newPixels;
    int size = header.width * header.height;

    if (color == 'R') {

        for (int i = 0; i < size; i++) {

            Pixel pixel;
            int red = (int) pixels.at(i).red;
            int redFinal = Clamp(red + amount);
            pixel.red = redFinal;
            pixel.green = pixels.at(i).green;
            pixel.blue = pixels.at(i).blue;
            newPixels.push_back(pixel);

        }

    } else if (color == 'G') {

        for (int i = 0; i < size; i++) {

            Pixel pixel;

            int green = (int) pixels.at(i).green;
            int greenFinal = Clamp(green + amount);
            pixel.red = pixels.at(i).red;
            pixel.green = greenFinal;
            pixel.blue = pixels.at(i).blue;
            newPixels.push_back(pixel);

        }

    } else if (color == 'B') {

        for (int i = 0; i < size; i++) {

            Pixel pixel;
            int blue = (int) pixels.at(i).blue;
            int blueFinal = Clamp(blue + amount);
            pixel.red = pixels.at(i).red;
            pixel.green = pixels.at(i).green;
            pixel.blue = blueFinal;
            newPixels.push_back(pixel);

        }

    }

    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Scale(int redScale, int blueScale, string fileName) {

    vector<Pixel> newPixels;
    int size = header.width * header.height;

    for (int i = 0; i < size; i++) {

        Pixel pixel;

        int red = (int) pixels.at(i).red;
        int redFinal = Clamp(red * redScale);
        int blue = (int) pixels.at(i).blue;
        int blueFinal = Clamp(blue * blueScale);
        pixel.red = redFinal;
        pixel.green = pixels.at(i).green;
        pixel.blue = blueFinal;
        newPixels.push_back(pixel);

    }

    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::WriteChannels(string filePath) {

    ofstream blueFile("output/" + filePath + "_b.tga", ios_base::binary);

    if (blueFile.is_open()) {

        blueFile.write(&header.idLength, sizeof(header.idLength));
        blueFile.write(&header.colorMapType, sizeof(header.colorMapType));
        blueFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        blueFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        blueFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        blueFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        blueFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        blueFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        blueFile.write((char*)&header.width, sizeof(header.width));
        blueFile.write((char*)&header.height, sizeof(header.height));
        blueFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        blueFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < pixels.size(); i++) {

            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));

        }

        blueFile.close();

    }

    ofstream greenFile("output/" + filePath + "_g.tga", ios_base::binary);

    if (greenFile.is_open()) {

        greenFile.write(&header.idLength, sizeof(header.idLength));
        greenFile.write(&header.colorMapType, sizeof(header.colorMapType));
        greenFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        greenFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        greenFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        greenFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        greenFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        greenFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        greenFile.write((char*)&header.width, sizeof(header.width));
        greenFile.write((char*)&header.height, sizeof(header.height));
        greenFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        greenFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < pixels.size(); i++) {

            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));

        }

        greenFile.close();

    }

    ofstream redFile("output/" + filePath + "_r.tga", ios_base::binary);

    if (redFile.is_open()) {

        redFile.write(&header.idLength, sizeof(header.idLength));
        redFile.write(&header.colorMapType, sizeof(header.colorMapType));
        redFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        redFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        redFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        redFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        redFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        redFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        redFile.write((char*)&header.width, sizeof(header.width));
        redFile.write((char*)&header.height, sizeof(header.height));
        redFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        redFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < pixels.size(); i++) {

            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));

        }

        redFile.close();

    }

}

void image::CombineFiles(image file1, image file2, string fileName) {

    vector<Pixel> redChannel = pixels;
    vector<Pixel> greenChannel = file1.getPixels();
    vector<Pixel> blueChannel = file2.getPixels();
    vector<Pixel> newPixels;

    int size = header.width * header.height;
    int i = 0;
    while (i < size) {

        Pixel pixel;
        pixel.red = redChannel.at(i).red;
        pixel.green = greenChannel.at(i).green;
        pixel.blue = blueChannel.at(i).blue;
        newPixels.push_back(pixel);
        i++;

    }

    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Flip(string fileName) {

    vector<Pixel> newPixels;

    for (int i = pixels.size()-1; i >=0; i--) {

        Pixel pixel;

        pixel.blue = pixels.at(i).blue;
        pixel.green = pixels.at(i).green;
        pixel.red = pixels.at(i).red;
        newPixels.push_back(pixel);

    }

    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

void image::Quadrant(image topRight, image bottomRight, image bottomLeft, string fileName) {

    vector<Pixel> topRightPixels = topRight.getPixels();
    vector<Pixel> bottomRightPixels = bottomRight.getPixels();
    vector<Pixel> topLeftPixels = pixels;
    vector<Pixel> bottomLeftPixels = bottomLeft.getPixels();
    vector<Pixel> newPixels;

    int total_pixels = 0;
    int size = header.width * header.height * 4;
    int i = 0;
    int j = 0;
    int k = 0;
    int z = 0;
    int index = 512;

    while (total_pixels < size/2) {

        while (k < index) {

            newPixels.push_back(bottomLeftPixels.at(k));
            total_pixels++;
            k++;

        }
        while (z < index) {

            newPixels.push_back(bottomRightPixels.at(z));
            total_pixels++;
            z++;

        }
        index += 512;

    }

    index = 512;
    while (total_pixels < size) {

        while (i < index) {

            newPixels.push_back(topLeftPixels.at(i));
            total_pixels++;
            i++;

        }
        while (j < index) {

            newPixels.push_back(topRightPixels.at(j));
            total_pixels++;
            j++;

        }

        index += 512;

    }

    header.width = 1024;
    header.height = 1024;
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");

}

