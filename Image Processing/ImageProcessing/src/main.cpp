#include <vector>
#include <iostream>
#include "image.h"
using namespace std;

// compare headers of images 
bool compareHeader(image picture1, image picture2) {
    if ((int)picture1.getHeader().idLength != (int)picture2.getHeader().idLength)
        return false;
    if ((int)picture1.getHeader().colorMapType != (int)picture2.getHeader().colorMapType)
        return false;
    if ((int)picture1.getHeader().dataTypeCode != (int)picture2.getHeader().dataTypeCode)
        return false;
    if ((short)picture1.getHeader().colorMapOrigin != (short)picture2.getHeader().colorMapOrigin)
        return false;
    if ((short)picture1.getHeader().colorMapLength != (short)picture2.getHeader().colorMapLength)
        return false;
    if ((int)picture1.getHeader().colorMapDepth != (int)picture2.getHeader().colorMapDepth)
        return false;
    if ((short)picture1.getHeader().xOrigin != (short)picture2.getHeader().xOrigin)
        return false;
    if ((short)picture1.getHeader().yOrigin != (short)picture2.getHeader().yOrigin)
        return false;
    if ((short)picture1.getHeader().width != (short)picture2.getHeader().width)
        return false;
    if ((short)picture1.getHeader().height != (short)picture2.getHeader().height)
        return false;
    if ((int)picture1.getHeader().bitsPerPixel != (int)picture2.getHeader().bitsPerPixel)
        return false;
    if ((int)picture1.getHeader().imageDescriptor != (int)picture2.getHeader().imageDescriptor)
        return false;
    return true;
}

// compare pixels and colors of images
bool comparePixels(image picture1, image picture2) {
    vector<Pixel> pixels1 = picture1.getPixels();
    vector<Pixel> pixels2 = picture2.getPixels();
    for (int i = 0; i < pixels1.size(); i++) {
        if ((int)pixels1.at(i).red != (int)pixels2.at(i).red)
            return false;
        if ((int)pixels1.at(i).green != (int)pixels2.at(i).green)
            return false;
        if ((int)pixels1.at(i).blue != (int)pixels2.at(i).blue)
            return false;
    }
    return true;
}

// test cases
bool compareHeader(image picture1, image picture2);
bool comparePixels(image picture1, image picture2);
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();
void Test10();
void Test11();
void TestAll();


int main() {
    TestAll();
    return 0;
}

// Use the Multiply blending mode to combine “layer1.tga” (top layer) with “pattern1.tga” (bottom layer).
void Test1() {

    image top = image("input/layer1.tga");
    image bottom = image("input/pattern1.tga");

    top.Multiply(bottom, "part1");
    image picture1 = image("output/part1.tga");
    image picture2 = image("examples/EXAMPLE_part1.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 1 Completed Successfully" << endl;
    else cout << "Test 1 Errored and Failed" << endl;
}


// Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer).
// This mode subtracts the top layer from the bottom layer
void Test2() {

    image top = image("input/layer2.tga");
    image bottom = image("input/car.tga");

    top.Subtract(bottom, "part2");
    image picture1 = image("output/part2.tga");
    image picture2 = image("examples/EXAMPLE_part2.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 2 Completed Successfully" << endl;
    else cout << "Test 2 Errored and Failed" << endl;
}

// Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily.
// Load the image “text.tga” and, using that as the top layer, combine it with the previous results of layer1 / pattern2 using the Screen blending mode.
void Test3() {

    image top = image("input/layer1.tga");
    image bottom = image("input/pattern2.tga");

    top.Multiply(bottom, "temp");
    image top2 = image("input/text.tga");
    image temp = image("output/temp.tga");

    top2.Screen(temp, "part3");
    image picture1 = image("output/part3.tga");
    image picture2 = image("examples/EXAMPLE_part3.tga");
    
    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 3 Completed Successfully" << endl;
    else cout << "Test 3 Errored and Failed" << endl;
}

// Multiply “layer2.tga” with “circles.tga”, and store it. 
// Load “pattern2.tga” and, using that as the top layer, combine it with the previous result using the Subtract blending mode.
void Test4() {

    image top = image("input/layer2.tga");
    image bottom = image("input/circles.tga");

    top.Multiply(bottom, "temp");
    image top2 = image("input/pattern2.tga");
    image temp = image("output/temp.tga");

    top2.Subtract(temp, "part4");
    image picture1 = image("output/part4.tga");
    image picture2 = image("examples/EXAMPLE_part4.tga");
    
    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 4 Completed Successfully" << endl;
    else cout << "Test 4 Errored and Failed" << endl;
}

// Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
void Test5() {

    image top = image("input/layer1.tga");
    image bottom = image("input/pattern1.tga");

    top.Overlay(bottom, "part5");    
    image picture1 = image("output/part5.tga");
    image picture2 = image("examples/EXAMPLE_part5.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 5 Completed Successfully" << endl;
    else cout << "Test 5 Errored and Failed" << endl;
}

// Load “car.tga” and add 200 to the green channel.
void Test6() {

    image top = image("input/car.tga");

    top.Add('G', 200, "part6");
    image picture1 = image("output/part6.tga");
    image picture2 = image("examples/EXAMPLE_part6.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 6 Completed Successfully" << endl;
    else cout << "Test 6 Errored and Failed" << endl;
}

// Load “car.tga” and scale(multiply) the red channel by 4, and the blue channel by 0. 
// This will increase the intensity of any red in the image, while negating any blue it may have.

void Test7() {

    image car = image("input/car.tga");

    car.Scale(4, 0, "part7");
    image picture1 = image("output/part7.tga");
    image picture2 = image("examples/EXAMPLE_part7.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 7 Completed Successfully" << endl;
    else cout << "Test 7 Errored and Failed" << endl;
}

// Load “car.tga” and write each channel to a separate file: 
// the red channel should be “part8_r.tga”, 
// the green channel should be “part8_g.tga”, 
// the blue channel should be “part8_b.tga”
// (Hint: If your red channel image appears all red, try writing[Red, Red, Red] instead of[Red, 0, 0] to the file—ditto for green and blue!)
void Test8() {

    image car = image("input/car.tga");

    car.WriteChannels("part8");
    image blue = image("output/part8_b.tga");
    image blue2 = image("examples/EXAMPLE_part8_b.tga");

    image green= image("output/part8_g.tga");
    image green2 = image("examples/EXAMPLE_part8_g.tga");

    image red = image("output/part8_r.tga");
    image red2 = image("examples/EXAMPLE_part8_r.tga");

    if (compareHeader(blue, blue2) && comparePixels(blue, blue2) && 
        compareHeader(green, green2) && comparePixels(green, green2) &&
        compareHeader(red, red2) && comparePixels(red, red2))
        cout << "Test 8 Completed Successfully" << endl;
    else cout << "Test 8 Errored and Failed" << endl;
}

// Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga” combine the three files into one file. 
// The data from “layer_red.tga” is the red channel of the new image, layer_green is green, and layer_blue is blue.
void Test9() {

    image redFile = image("input/layer_red.tga");
    image greenFile = image("input/layer_green.tga");
    image blueFile = image("input/layer_blue.tga");

    redFile.CombineFiles(greenFile, blueFile, "part9");
    image picture1 = image("output/part9.tga");
    image picture2 = image("examples/EXAMPLE_part9.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 9 Completed Successfully" << endl;
    else cout << "Test 9 Errored and Failed" << endl;
}

// Load “text2.tga”, and rotate it 180 degrees, flipping it upside down. T
void Test10() {

    image file = image("input/text2.tga");

    file.Flip("part10");
    image picture1 = image("output/part10.tga");
    image picture2 = image("examples/EXAMPLE_part10.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 10 Completed Successfully" << endl;
    else cout << "Test 10 Errored and Failed" << endl;
}

// Create a new file that is the combination of car.tga, circles.tga, pattern1.tga, and text.tga. 
// Each source image will be in a quadrant of the final image, and the result should look like the image below.
void Test11() {

    image car = image("input/car.tga");
    image circles = image("input/circles.tga");
    image pattern = image("input/pattern1.tga");
    image text = image("input/text.tga");

    car.Quadrant(circles, pattern, text, "extracredit");

    image picture1 = image("output/extracredit.tga");
    image picture2 = image("examples/EXAMPLE_extracredit.tga");

    if (compareHeader(picture1, picture2) && comparePixels(picture1, picture2))
        cout << "Test 11 Completed Successfully" << endl;
    else cout << "Test 11 Errored and Failed" << endl;
}

void TestAll() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
}