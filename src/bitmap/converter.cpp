#include "converter.hpp"


/**
 * @brief Print out the BMP info header
 * 
 * @param header 
 */
void printOutHeader(const BMPHeader header) {
    std::cout << "BMP Header" << std::endl;
    std::cout << "Signature: " << header.bmpSignature[0] << header.bmpSignature[1] << std::endl;
    std::cout << "File Size: " << header.fileSize << std::endl;
    std::cout << "Reserved 1: " << header.reserved1 << std::endl;
    std::cout << "Reserved 2: " << header.reserved2 << std::endl;
    std::cout << "Data Offset: " << header.dataOffset << std::endl;
}

/**
 * @brief Print out the info header
 * 
 * @param infoHeader 
 */
void printOutInfoHeader(const BMPInfoHeader infoHeader) {
    std::cout << "BMP Info Header" << std::endl;
    std::cout << "Header Size: " << infoHeader.headerSize << std::endl;
    std::cout << "Image Width: " << infoHeader.width << std::endl;
    std::cout << "Image Height: " << infoHeader.height << std::endl;
    std::cout << "Planes: " << infoHeader.planes << std::endl;
    std::cout << "Bits Per Pixel: " << infoHeader.bitsPerPixel << std::endl;
    std::cout << "Compression: " << infoHeader.compression << std::endl;
    std::cout << "Image Size: " << infoHeader.imageSize << std::endl;
    std::cout << "X Pixels Per Meter: " << infoHeader.xResolution << std::endl;
    std::cout << "Y Pixels Per Meter: " << infoHeader.yResolution << std::endl;
    std::cout << "Total Colors: " << infoHeader.colorsUsed << std::endl;
    std::cout << "Important Colors: " << infoHeader.importantColors << std::endl;

}

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

    // Read the color table
    std::vector<uint8_t> colorTable(256 * 4);
    file.read(reinterpret_cast<char*>(colorTable.data()), 256 * 4);

    // Move the file pointer to the beginning of the pixel data
    file.seekg(bmpHeader.dataOffset);

    // Read pixel data with handling for padding
    std::vector<uint8_t> pixels;
    int padding = (4 - (bmpInfoHeader.width % 4)) % 4;
    for (int i = 0; i < bmpInfoHeader.height; ++i) {
        for (int j = 0; j < bmpInfoHeader.width; ++j) {
            uint8_t pixel;
            file.read(reinterpret_cast<char*>(&pixel), 1);
            pixels.push_back(pixel);
        }
        file.seekg(padding, std::ios::cur);  // skip padding
    }

    BMPFile* newBMPFile = new BMPFile;  // Using new instead of malloc for C++

    newBMPFile->bmpHeader = bmpHeader;
    newBMPFile->bmpInfoHeader = bmpInfoHeader;
    newBMPFile->colorTable = colorTable;
    newBMPFile->pixels = pixels;

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
    const std::vector<uint8_t>& colorTable = bmpFile.colorTable;  // Access the color table

    std::ofstream file(filePath, std::ios::binary);
    
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        exit(1);
    }

    // Write BMP header and BMP info header
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    // Write the color table
    file.write(reinterpret_cast<const char*>(colorTable.data()), 256 * 4);

    // Write pixel data with handling for padding
    int padding = (4 - (bmpInfoHeader.width % 4)) % 4;
    for (int i = 0; i < bmpInfoHeader.height; ++i) {
        for (int j = 0; j < bmpInfoHeader.width; ++j) {
            file.write(reinterpret_cast<const char*>(&pixels[i * bmpInfoHeader.width + j]), 1);
        }
        for (int p = 0; p < padding; ++p) {
            file.put(0);  // write padding
        }
    }

    std::cout << "\nSaved file with " << pixels.size() << " pixels." << std::endl;

    file.close();
}