#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<iostream>

int main() {
    int width, height, channels;
    unsigned char* img = stbi_load("Leopard2a7.jpg", &width, &height, &channels, 0);

    if (!img) return -1;

    //Rotating
    int count = 0;
    unsigned char* arr = new unsigned char[width*height*channels];

    for (int i = 0; i < width * height * channels; i++)
    {
        arr[i] = img[i];
    }
    
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int pixelIndex = (j * width + i) * 3;
            img[count++] = arr[pixelIndex];     // R
            img[count++] = arr[pixelIndex + 1]; // G
            img[count++] = arr[pixelIndex + 2]; // B

        }
    }

    //save the modified image
    const char* outputFilename = "rotate90.jpg";
    if (stbi_write_jpg(outputFilename, height, width, channels, img, 100))
    {
        std::cout << "Image saved as " << outputFilename << std::endl;
    }
    else
    {
        std::cerr << "Error saving image!" << std::endl;
    }

    stbi_image_free(img);
    delete[] arr;
    return 0;
}
