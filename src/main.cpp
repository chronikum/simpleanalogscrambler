#include <stdio.h>
#include "./bitmap/converter.hpp"

struct RGB {
	int r;
	int g;
	int b;
};



//std::vector<RGB> rgbPixels;

//int expectedSize = pixels.size() / 3;

//rgbPixels.resize(expectedSize); // resize the pixels vector to 256

//for (int i = 0; i < pixels.size(); i += 3) {
//	rgbPixels[i / 3].r = pixels[i];
//	rgbPixels[i / 3].g = pixels[i + 1];
//	rgbPixels[i / 3].b = pixels[i + 2];
//}

int main() {

	const char* currentPath = "./assets/test.bmp";

	std::vector<uint8_t> pixels = readGrayscaleBMP(currentPath);


	return (0);
}
