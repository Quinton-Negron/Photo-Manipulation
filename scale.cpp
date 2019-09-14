/*
 Author: Quinton Negron
 
 Description:
 This program uses the "image program", but with added feature
 of inverting the pixel color. This is done by simply
 going into the int main() and making it so that when
 outputed the file prodcues the differnece of a pixel value
 ergo it's inverse
 
 This time for part b we use an if/elif to denote whihc half of the
 pictures gets inverted. Specifically the later half.
 
 For Part c, we physcially define a space within the if/elif for where
 box is going to be. Everything outside this box will just prodcue
 the normal image.
 
 Part D uses the same if/elif to produce a frame this time
 */

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
	int x = h*2;
	int z = 0;
    int y = w*2;
	int u = 0;

	for(int row = 0; row < x; row++)
	{
		for(int col =  0; col < y; col++)
		{
			if(col % 2 == 0 && col != 0)
			{
				z = z + 1;
			}
			if(col == 0)
			{
				z = 0;
			}
			if(col == 0 && row % 2 == 0 && row !=0)
			{
				u = u + 1;
			}
			
				out[row][col] = img[u][z];
		}
	}
	//save the new image to file 'outImage.pgm'
	writeImage(out, x, y);
}
