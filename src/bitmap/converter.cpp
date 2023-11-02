#include "converter.hpp"

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
#pragma pack(pop)

/**
 * @brief Reads a bitmap file from a file path
 * 
 * @param filePath 
 * @return std::vector<uint8_t> 
 */
std::vector<uint8_t> readGrayscaleBMP(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }

    // Read BMP header and BMP info header
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    if (bmpHeader.bmpSignature[0] != 'B' || bmpHeader.bmpSignature[1] != 'M') {
        std::cerr << "Not a BMP file!" << std::endl;
        exit(1);
    }

    if (bmpInfoHeader.bitsPerPixel != 8) {
        std::cerr << "Not a grayscale BMP!" << std::endl;
        exit(1);
    }

    // Move the file pointer to the beginning of the pixel data
    file.seekg(bmpHeader.dataOffset);

    // Read pixel data
    std::vector<uint8_t> pixels(bmpInfoHeader.imageSize);
    file.read(reinterpret_cast<char*>(pixels.data()), bmpInfoHeader.imageSize);

    std::cout << "\nOpened file and read" << pixels.size() << std::endl;
    return pixels;
}