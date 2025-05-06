#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <algorithm>

int main() {
    int width, height, channels;

    // Load input image (force 3 channels: RGB)
    unsigned char* img = stbi_load("Leopard2a7.jpg", &width, &height, &channels, 0);
    if (!img) {
        std::cerr << "Failed to load input image.\n";
        return 1;
    }
    int blockSize = 20;
    unsigned char avgR, avgG, avgB;

    //output buffer
    unsigned char* mosaic = new unsigned char[width * height * 3];

    for (int m = 0; m<height;m+=blockSize)
    {
        for (int n = 0; n<width; n+=blockSize)
        {
            long sumR = 0, sumG = 0, sumB = 0;
            int count = 0;
            for (int i = 0; i < blockSize; i++)
            {
                for (int j = 0; j < blockSize; j++)
                {
                    int y = m + i;
                    int x = n + j;
                    if (y >= height || x >= width)
                        continue;
                    int pixelIndex = (y * width + x) * channels;
                    sumR += img[pixelIndex];
                    sumG += img[pixelIndex + 1];
                    sumB += img[pixelIndex + 2];
                    count++;
                }
            }
            avgR = sumR / count;
            avgG = sumG / count;
            avgB = sumB / count;

            // Paint block with the average color
            for (int i = 0; i < blockSize; i++)
            {
                for (int j = 0; j < blockSize; j++)
                {
                    int y = m + i;
                    int x = n + j;
                    if (y >= height || x >= width)
                        continue;
                    int pixelIndex = (y * width + x) * channels;
                    mosaic[pixelIndex] = avgR;
                    mosaic[pixelIndex + 1] = avgG;
                    mosaic[pixelIndex + 2] = avgB;
                }
            }
        }
    }
    // Save the mosaic image
    if (!stbi_write_jpg("mosaic_output.jpg", width, height, channels, mosaic, 100)) {
        std::cerr << "Failed to save mosaic_output.jpg\n";
    }
    else {
        std::cout << "Mosaic image saved as mosaic_output.jpg\n";
    }

    stbi_image_free(img);
    delete[]mosaic;
    return 0;
}
