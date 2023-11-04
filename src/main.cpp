#include <stdio.h>
#include "./bitmap/bitmap.hpp"

struct RGB {
	int r;
	int g;
	int b;
};


int main(int argc, char** argv) {

	std::string writePath = "./assets/test3.bmp";

	if (argv[1] == NULL) {
		std::cout << "No file path provided, using default" << std::endl;
	} else {
		writePath = argv[1];
	}

	const char* currentPath = "./assets/test.bmp";

	

	BMPFile *bmpFile = readGrayscaleBMPFile(currentPath);
	std::cout << "====================" << std::endl;

	bitmapScrambler(bmpFile);

	shuffleBack(bmpFile);

	writeGrayscaleBMP(writePath, *bmpFile);

	return (0);
}
