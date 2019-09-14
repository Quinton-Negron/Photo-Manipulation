
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	// read the header P2
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}

int main()
{
	int img [MAX_H] [MAX_W];
	int h, w;
	readImage (img, h, w);
	//read the image from the file "inImage.pgm"
	//h and w are passed by reference and contain te dimensions of the picture
	//the 2 dimensional array image contain the image data

	//we can now modify the image however we want
	int out [MAX_H] [MAX_W];
	int a = w*(0.75);
	int b = w*(0.25);
	int c = h*(0.75);
	int d = h*(0.25);

	for(int row = 0; row < h; row++)
	{
		for(int col =  0; col < w; col++)
		{
			if((col <= a && col >= b) && (row == c || row == d))
			{
				out[row][col] = 255;
			}
			else if((col == a || col == b) && (row <= c && row >= d))
			{
				out[row][col] = 255;
			}
			else
			{
				out[row][col] = img[row][col];
			}
		}
	}
	//save the new image to file 'outImage.pgm'
	writeImage(out, h, w);
}
