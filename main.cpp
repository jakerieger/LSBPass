#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <vector>
#include <picosha2.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: lsb_pass <image.png>" << std::endl;
        return 1;
    }
    const char* fileName = argv[1];

    int width, height, channels;
    unsigned char* data = stbi_load(fileName, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << fileName << std::endl;
        return 1;
    }

    if (channels < 3) {
        stbi_image_free(data);
        std::cerr << "Image has less than 3 channels" << std::endl;
        return 1;
    }

    std::vector<uint8_t> bitmask;
    for (int i = 0; i < width * height * channels; ++i) {
        if (channels == 4) if (i % 4 == 0) continue; // skip alpha bits
        bitmask.push_back(data[i] & 1); // Extract LSB
    }

    stbi_image_free(data);

    // Generate password from bitmask
    const std::string passStr = picosha2::hash256_hex_string(bitmask);

    std::cout << "LSB Password Generator by Jake Rieger" << '\n';
    std::cout << "===========================================================================\n";
    std::cout << "Generated from:\n  - Name: " << fileName << '\n';
    std::cout << "  - Width: " << width << "\n  - Height: " << height << "\n";
    std::cout << "===========================================================================\n";
    std::cout << "Password: " << passStr << '\n';

    return 0;
}