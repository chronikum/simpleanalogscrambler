#include <iostream>
#include <fstream>
#include <vector>



#pragma pack(push, 1) // Ensure structure is packed tightly
struct BMPHeader {
    char bmpSignature[2];  // "BM"
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;   // Start position of pixel data
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xResolution;
    int32_t yResolution;
    uint32_t colorsUsed;
    uint32_t importantColors;
};


/**
 * @brief This represents a bitmap file
 */
struct BMPFile {
	BMPHeader bmpHeader;
	BMPInfoHeader bmpInfoHeader;
	std::vector<uint8_t> pixels;
};

#pragma pack(pop)

BMPFile* readGrayscaleBMPFile(const std::string& filePath);
void writeGrayscaleBMP(const std::string& filePath, const BMPFile &bmpFile);