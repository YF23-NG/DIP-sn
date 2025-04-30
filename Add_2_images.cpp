#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include<iostream>

int main() {
	//Load the 1st JPEG image
	int width1, height1, channels1;
	const char* inputFilename1 = "VIGGEN.jpg";
	unsigned char* img1 = stbi_load(inputFilename1, &width1, &height1, &channels1, 0);
	if (img1 == nullptr)
	{
		std::cerr << "Error loading image1!" << std::endl;
		return -1;
	}

	//Load the 2nd JPEG image
	int width2, height2, channels2;
	const char* inputFilename2 = "GTA5_JPG.jpg";
	unsigned char* img2 = stbi_load(inputFilename2, &width2, &height2, &channels2, 0);
	if (img2 == nullptr)
	{
		std::cerr << "Error loading image2!" << std::endl;
		return -1;
	}

	//Add the 2 JPEG images
	int totalPixels = width1 * height1 * channels2;
	unsigned char* output = new unsigned char[totalPixels];
	for (int i = 0; i < totalPixels; i++)
	{
		int sum = img1[i] + img2[i];
		output[i] = std::min(255, std::max(0, sum));
	}


	//save the modified image
	const char* outputFilename = "add.png";
	if (stbi_write_jpg(outputFilename, width1, height1, channels1, output, 100))
	{
		std::cout << "Image saved as " << outputFilename << std::endl;
	}
	else
	{
		std::cerr << "Error saving image!" << std::endl;
	}

	//Free the image memory
	stbi_image_free(img1);
	stbi_image_free(img2);
	delete[] output;
	return 0;
}