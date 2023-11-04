#include "converter.hpp"


/**
 * @brief Printing out the pixel data
 * 
 * @param pixels 
 */
void printOutPixelData(const std::vector<uint8_t>& pixels) {
    for (int i = 0; i < pixels.size(); i++) {
        std::cout << (int) pixels[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Reads a bitmap file from a file path
 * - Does not allocate memory for the pixels. Please copy the return value to a allocated vector or array.
 * 
 * @param filePath 
 * @return std::vector<uint8_t> 
 */
BMPFile* readGrayscaleBMPFile(const std::string& filePath) {

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

    // Move the file pointer to the beginning of the pixel data
    file.seekg(bmpHeader.dataOffset);

    // Read pixel data
    std::vector<uint8_t> pixels(bmpInfoHeader.imageSize);
    file.read(reinterpret_cast<char*>(pixels.data()), bmpInfoHeader.imageSize);

    struct BMPFile* newBMPFile = (struct BMPFile*) malloc(sizeof(struct BMPFile));

    newBMPFile->bmpHeader = bmpHeader;
    newBMPFile->bmpInfoHeader = bmpInfoHeader;
    newBMPFile->pixels = pixels;

    printOutPixelData(newBMPFile->pixels);

    std::cout << "\nOpened file and read \n" << newBMPFile->pixels.size() << std::endl;
    return newBMPFile;
}

/**
 * @brief Write a bitmap file to a file path
 * 
 * @param filePath 
 * @param bmpFile 
 */
void writeGrayscaleBMP(const std::string& filePath, const BMPFile &bmpFile) {

    const std::vector<uint8_t>& pixels = bmpFile.pixels;
    const BMPHeader& bmpHeader = bmpFile.bmpHeader;
    const BMPInfoHeader& bmpInfoHeader = bmpFile.bmpInfoHeader;

    std::ofstream file(filePath, std::ios::binary);

    printOutPixelData(pixels);
    
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        exit(1);
    }

    // Write BMP header and BMP info header
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    // Write pixel data
    file.write(reinterpret_cast<const char*>(pixels.data()), bmpInfoHeader.imageSize);

    std::cout << "\nSaved file with " << pixels.size() << " pixels." << std::endl;

    file.close();
}