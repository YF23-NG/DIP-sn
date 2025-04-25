#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include<iostream>

int main() {
	//Load the JPEG image
	int width,height,channels;
	const char* inputFilename = "F-117.jpg";
	unsigned char* img = stbi_load(inputFilename, &width, &height, &channels, 0);
	if (img == nullptr) {
		std::cerr << "Error loading image!" << std::endl;
		return -1;
	}

	//Loop through every pixel in the image
	for (int i = 0; i < width * height; i++)
	{
		int pixelIndex = i * channels;
		//Extract RGB value
		unsigned char R = img[pixelIndex];
		unsigned char G = img[pixelIndex+1];
		unsigned char B = img[pixelIndex+2];

		if (((R + G + B)/3) < 160)
		{
			img[pixelIndex] = 255;
			img[pixelIndex+1] = 255;
			img[pixelIndex+2] = 255;
		}
	}

	//save the modified image
	const char* outputFilename = "swap.jpg";
	if (stbi_write_jpg(outputFilename, width, height, channels, img, 100))
	{
		std::cout << "Image saved as " << outputFilename << std::endl;
	}
	else
	{
		std::cerr << "Error saving image!" << std::endl;
	}

	//Free the image memory
	stbi_image_free(img);
	return 0;
}