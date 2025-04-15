#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>

void dualFilter(unsigned char* img, int width, int height, int channels) {
    // Sepia-tone filter matrix
    float sepiaMatrix[3][3] = {
        {0.393f, 0.769f, 0.189f},
        {0.349f, 0.686f, 0.168f},
        {0.272f, 0.534f, 0.131f}
    };
    //Icy Blue filter matrix
    float icyMatrix[3][3] = {
        {0.6f, 0.0f, 0.2f},
        {0.0f, 0.7f, 0.2f},
        {0.2f, 0.2f, 1.3f}
    };

    // Loop through every pixel in the half of the image
    for (int i = 0; i < width * height/2; i++) {
        int pixelIndex = i * channels;

        // Extract RGB values
        unsigned char R = img[pixelIndex];
        unsigned char G = img[pixelIndex + 1];
        unsigned char B = img[pixelIndex + 2];

        // Apply the sepia transformation
        int newR = (int)(sepiaMatrix[0][0] * R + sepiaMatrix[0][1] * G + sepiaMatrix[0][2] * B);
        int newG = (int)(sepiaMatrix[1][0] * R + sepiaMatrix[1][1] * G + sepiaMatrix[1][2] * B);
        int newB = (int)(sepiaMatrix[2][0] * R + sepiaMatrix[2][1] * G + sepiaMatrix[2][2] * B);

        // Clamp the values to the 0-255 range
        img[pixelIndex] = std::min(255, std::max(0, newR));
        img[pixelIndex + 1] = std::min(255, std::max(0, newG));
        img[pixelIndex + 2] = std::min(255, std::max(0, newB));
    }
    //Loop through every pixel in the other half of the image
    for (int i = width*height/2; i < width * height; i++) {
        int pixelIndex = i * channels;

        // Extract RGB values
        unsigned char R = img[pixelIndex];
        unsigned char G = img[pixelIndex + 1];
        unsigned char B = img[pixelIndex + 2];

        // Apply the icyBlue transformation
        int newR = (int)(icyMatrix[0][0] * R + icyMatrix[0][1] * G + icyMatrix[0][2] * B);
        int newG = (int)(icyMatrix[1][0] * R + icyMatrix[1][1] * G + icyMatrix[1][2] * B);
        int newB = (int)(icyMatrix[2][0] * R + icyMatrix[2][1] * G + icyMatrix[2][2] * B);

        // Clamp the values to the 0-255 range
        img[pixelIndex] = std::min(255, std::max(0, newR));
        img[pixelIndex + 1] = std::min(255, std::max(0, newG));
        img[pixelIndex + 2] = std::min(255, std::max(0, newB));
    }
}

int main() {
    // Load the image (JPEG)
    int width, height, channels;
    const char* inputFilename = "YF-23_1.jpg"; // Replace with your image file path
    unsigned char* img = stbi_load(inputFilename, &width, &height, &channels, 0);

    if (img == nullptr) {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;

    // Apply sepia filter to the image
    dualFilter(img, width, height, channels);

    // Save the modified image (JPEG)
    const char* outputFilename = "dual_filter.jpg"; // Output file name
    if (stbi_write_jpg(outputFilename, width, height, channels, img, 100)) {
        std::cout << "Image saved as " << outputFilename << std::endl;
    }
    else {
        std::cerr << "Error saving image!" << std::endl;
    }

    // Free the image memory
    stbi_image_free(img);

    return 0;
}