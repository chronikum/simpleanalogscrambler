#include <stdio.h>
#include "./bitmap/bitmap.hpp"

struct RGB {
	int r;
	int g;
	int b;
};


int main() {

	const char* currentPath = "./assets/test.bmp";

	

	BMPFile *bmpFile = readGrayscaleBMPFile(currentPath);
	std::cout << "====================" << std::endl;

	bitmapScramber(bmpFile);

	writeGrayscaleBMP("./assets/test3.bmp", *bmpFile);

	return (0);
}
