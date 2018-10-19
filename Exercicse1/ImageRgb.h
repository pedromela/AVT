#pragma once
#include <stdio.h> 
#include <assert.h>

class ImageRgb {
public:
	ImageRgb(const char* filename);
	~ImageRgb();

	bool LoadBmpFile(const char *filename);      // Loads the bitmap from the specified file


	long GetNumRows() const { return NumRows; }
	long GetNumCols() const { return NumCols; }
	// Rows are word aligned
	long GetNumBytesPerRow() const { return ((3 * NumCols + 3) >> 2) << 2; }
	const void* ImageData() const { return (void*)ImagePtr; }
	void Reset();
	int GetErrorCode() const { return ErrorCode; }
	enum {
		NoError = 0,
		OpenError = 1,         // Unable to open file for reading
		FileFormatError = 2,   // Not recognized as a 24 bit BMP file
		MemoryError = 3,      // Unable to allocate memory for image data
		ReadError = 4,         // End of file reached prematurely
		WriteError = 5         // Unable to write out data (or no date to write out)
	};
private:
	unsigned char* ImagePtr;   // array of pixel values (integers range 0 to 255)
	long NumRows;            // number of rows in image
	long NumCols;            // number of columns in image
	int ErrorCode;            // error code

	static short readShort(FILE* infile);
	static long readLong(FILE* infile);
	static void skipChars(FILE* infile, int numChars);
	static void writeLong(long data, FILE* outfile);
	static void writeShort(short data, FILE* outfile);

	static unsigned char doubleToUnsignedChar(double x);
};