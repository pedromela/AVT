#pragma warning(disable : 4996)

#include "ImageRgb.h"

ImageRgb::~ImageRgb()
{
	delete[] ImagePtr;
}

bool ImageRgb::LoadBmpFile(const char* filename)
{
	Reset();
	FILE* infile = fopen(filename, "rb");      // Open for reading binary data
	if (!infile) {
		fprintf(stderr, "Unable to open file: %s\n", filename);
		ErrorCode = OpenError;
		return false;
	}

	bool fileFormatOK = false;
	int bChar = fgetc(infile);
	int mChar = fgetc(infile);
	if (bChar == 'B' && mChar == 'M') {         // If starts with "BM" for "BitMap"
		skipChars(infile, 4 + 2 + 2 + 4 + 4);         // Skip 4 fields we don't care about
		NumCols = readLong(infile);
		NumRows = readLong(infile);
		skipChars(infile, 2);               // Skip one field
		int bitsPerPixel = readShort(infile);
		skipChars(infile, 4 + 4 + 4 + 4 + 4 + 4);      // Skip 6 more fields

		if (NumCols > 0 && NumCols <= 100000 && NumRows > 0 && NumRows <= 100000
			&& bitsPerPixel == 24 && !feof(infile)) {
			fileFormatOK = true;
		}
	}
	if (!fileFormatOK) {
		Reset();
		ErrorCode = FileFormatError;
		fprintf(stderr, "Not a valid 24-bit bitmap file: %s.\n", filename);
		fclose(infile);
		return false;
	}

	// Allocate memory
	ImagePtr = new unsigned char[NumRows*GetNumBytesPerRow()];
	if (!ImagePtr) {
		fprintf(stderr, "Unable to allocate memory for %ld x %ld bitmap: %s.\n",
			NumRows, NumCols, filename);
		Reset();
		ErrorCode = MemoryError;
		fclose(infile);
		return false;
	}

	unsigned char* cPtr = ImagePtr;
	for (int i = 0; i < NumRows; i++) {
		int j;
		for (j = 0; j < NumCols; j++) {
			*(cPtr + 2) = fgetc(infile);   // Blue color value
			*(cPtr + 1) = fgetc(infile);   // Green color value
			*cPtr = fgetc(infile);      // Red color value
			cPtr += 3;
		}
		int k = 3 * NumCols;               // Num bytes already read
		for (; k < GetNumBytesPerRow(); k++) {
			fgetc(infile);            // Read and ignore padding;
			*(cPtr++) = 0;
		}
	}
	if (feof(infile)) {
		fprintf(stderr, "Premature end of file: %s.\n", filename);
		Reset();
		ErrorCode = ReadError;
		fclose(infile);
		return false;
	}
	fclose(infile);   // Close the file
	return true;
}
ImageRgb::ImageRgb(const char* filename)
{
	NumRows = 0;
	NumCols = 0;
	ImagePtr = 0;
	ErrorCode = 0;
	LoadBmpFile(filename);
}
short ImageRgb::readShort(FILE* infile)
{
	// read a 16 bit integer
	unsigned char lowByte, hiByte;
	lowByte = fgetc(infile);         // Read the low order byte (little endian form)
	hiByte = fgetc(infile);         // Read the high order byte

	// Pack together
	short ret = hiByte;
	ret <<= 8;
	ret |= lowByte;
	return ret;
}

long ImageRgb::readLong(FILE* infile)
{
	// Read in 32 bit integer
	unsigned char byte0, byte1, byte2, byte3;
	byte0 = fgetc(infile);         // Read bytes, low order to high order
	byte1 = fgetc(infile);
	byte2 = fgetc(infile);
	byte3 = fgetc(infile);

	// Pack together
	long ret = byte3;
	ret <<= 8;
	ret |= byte2;
	ret <<= 8;
	ret |= byte1;
	ret <<= 8;
	ret |= byte0;
	return ret;
}

void ImageRgb::Reset()
{
	NumRows = 0;
	NumCols = 0;
	delete[] ImagePtr;
	ImagePtr = 0;
	ErrorCode = 0;
}

void ImageRgb::skipChars(FILE* infile, int numChars)
{
	for (int i = 0; i < numChars; i++) {
		fgetc(infile);
	}
}