#include <stdio.h>
#include "./bitmap/converter.hpp"

int main() {

	const char* currentPath = "./assets/test.bmp";

	std::vector<uint8_t> pixels = readGrayscaleBMP(currentPath);

	for (int i = 0; i < pixels.size(); i++) {
		printf("%d\n", pixels[i]);
	}
	return (0);
}