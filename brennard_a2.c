#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

#define LEFTMOST_BIT_POS 7
#define BITS_IN_BYTE	 8
#define BYTE_MAX_VALUE   255

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

/*  Function: get_bit()
    Description: Extracts a bit from a byte, can check if a bit in a byte is set or cleared

    Input: byte   - respective byte where bit needs to be extracted
    Input: bit    - position of the bit to be extracted

    Returns: 1 if bit is set, 0 if cleared
    
*/
unsigned char get_bit(unsigned char byte, int bit);

/*  Function: set_bit()
    Description: Sets the specified bit to 1 and returns the new byte

    Input: byte   - respective byte where bit needs to be set
    Input: bit    - position of the bit to be set

    Returns: The new modified byte
    
*/
unsigned char set_bit(unsigned char byte, int bit);

/*  Function: clear_bit()
    Description: Extracts a bit from a byte, can check if a bit in a byte is set or cleared

    Input: byte   - respective byte where bit needs to be cleared
    Input: bit    - position of the bit to be cleared

    Returns: The new modified byte
    
*/
unsigned char clear_bit(unsigned char byte, int bit);

/*  Function: print_raw()
    Description: Simulates printing a photo as a black-and-white image represented by                  an array of characters '1' and '0', represented as '*' and '.' respectively.

    Input: raw_string[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Input: rows    		  - number of rows in photo
    Input: cols			  - number of cols in photo
    Output: Visual representation of aforementioned black and white image

    Returns: void
    
*/
void print_raw(unsigned char raw_string[], int rows, int cols);

/*  Function: pack_ bits()
    Description: Takes an array of '1' and '0' characters representing a black-and-white image and packs them into bytes. Each character is considered a bit, 8 consecutive characters are a byte.

    Input: unpacked_string[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Input: num_chars    	   - total number of characters in the unpacked_string[]
    Output: packed_result[]	   - an array where the packed bytes are stored
   
    Returns: total number of bytes in packed_result[]
    
*/
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);

/*  Function: print_packed()
    Description: Takes an array of bytes representing a black-and-white image and prints them onto the screen. A 1 bit is '*' and a 0 bit is '.'

    Input: packed[]       - an array of bytes, each containing 8 bits
    Input: rows    		  - number of rows in photo
    Input: cols			  - number of cols in photo
    Output: Prints unpacked image onto screen.
   
    Returns: void
    
*/
void print_packed(unsigned char packed[], int rows, int cols);

/*  Function: encode_bits()
    Description: Encodes array of packed bytes using run length encoding.

    Input: packed[]       		- an array of bytes, each containing 8 bits
    Input: packed_size    		- number of bytes in the packed array
    Output: encoded_result[]	- array of bytes, each byte representing the consecutive count of bits (1 or 0) from the packed array
   
    Returns: number of bytes in the encoded array
    
*/
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);

/*  Function: print_encoded()
    Description: Takes an array of encoded bytes representing a black-and-white image and prints them onto the screen. A 1 bit is '*' and a 0 bit is '.'

    Input: encoded[]       		- run length encoded array of bytes 
    Input: encoded_size    		- number of bytes in encoded array
    Input: rows    		  		- number of rows in photo
    Input: cols			  		- number of cols in photo
    Output: Prints visual representation of the encoded black and white image, 1 is '*' and 0 is '.'
   
    Returns: void
    
*/
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);

int main() {
   unsigned char raw_photo[MAX_ARR];
   unsigned char packed_photo[MAX_ARR/BITS_IN_BYTE];
   unsigned char encoded_photo[MAX_ARR];
   
   int rows = 0;
   int cols = 0;
   unsigned int char_size = take_photo(raw_photo, &rows, &cols); 
   
   while (char_size > 0) {
   		printf("\nRaw photo (%d bytes):\n", char_size);
		print_raw(raw_photo, rows, cols);
		printf("\n");
		
		unsigned int packed_size = pack_bits(raw_photo, char_size, packed_photo);
		printf("Packed photo (%d bytes):\n", packed_size);
		print_packed(packed_photo, rows, cols);
		printf("\n");
		
		unsigned int encoded_size = encode_bits(packed_photo, packed_size, encoded_photo);
		printf("Encoded photo (%d bytes):\n", encoded_size);
		print_encoded(encoded_photo, encoded_size, rows, cols);
		
		printf("Sizes: raw = %d bytes, packed = %d bytes, encoded = %d bytes\n", char_size, packed_size, encoded_size);
		
		char_size = take_photo(raw_photo, &rows, &cols);
	   }
  
   return 0;
}

void print_raw(unsigned char raw_string[], int rows, int cols) {
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			int index = i * cols + j; 
			
			if (raw_string[index] == '1') {
				printf("*");
			} else if (raw_string[index] == '0') {
				printf(".");
			}
		}
		printf("\n");
	}
}

unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}

int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
	int charIndex = 0;
	int currentBitIndex = 0;
	int currentByteIndex = 0;
	unsigned char currentByte = 0; 
	
	for (charIndex = 0; charIndex < num_chars; charIndex++) {
		if (unpacked_string[charIndex] == '1') {
			currentByte |= (1 << (LEFTMOST_BIT_POS - currentBitIndex));
		}
		
		currentBitIndex++;
		
		if (currentBitIndex == 8) {
			packed_result[currentByteIndex] = currentByte;
			currentByteIndex++;
			currentByte = 0;
			currentBitIndex = 0;
		}
	}
	
	if (currentBitIndex > 0) {
        packed_result[currentByteIndex] = currentByte;
        currentByteIndex++;
    }
	
	return currentByteIndex;
}

void print_packed(unsigned char packed[], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int index = (i * cols + j) / BITS_IN_BYTE;
			
			int bitPos = LEFTMOST_BIT_POS - (i * cols + j) % BITS_IN_BYTE;
			
			if (packed[index] & (1 << bitPos)) {
				printf("*");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
		
}

int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]) {
	int streak = 0;
    int encodedResultIndex = 0;
    unsigned char currentType = 1;
    
    for (int i = 0; i <= packed_size; i++) {
    	for (int j = 0; j < BITS_IN_BYTE; j++) {
    		if (i == packed_size) { 
	            if (streak > 0) {
	                encoded_result[encodedResultIndex++] = streak;
	            }
	            break;
	        }
	        
    		unsigned char currentBit = get_bit(packed[i], LEFTMOST_BIT_POS - j);
    		
    		if (currentBit == currentType) {
    			streak++;
    			if (streak == BYTE_MAX_VALUE) {
    				encoded_result[encodedResultIndex++] = streak;
    				streak = 0;
    				currentType = !currentType;
    			}
    		} else {
    			encoded_result[encodedResultIndex++] = streak;
    			streak = 1;
    			currentType = !currentType;
    		}
    	}
    }
	
	return encodedResultIndex;
}

void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols) {
	unsigned char currentBitType = 1;
	int currentCol = 0;
	
	for (int i = 0; i < encoded_size; i++) {
		for (int j = 0; j < encoded[i]; j++) {
			
			if (currentBitType == 1) {
				printf("*");
			} else {
				printf(".");
			}
			
			currentCol++;
			
			if (currentCol == cols) {
				printf("\n");
				currentCol = 0;
			}
		}
		currentBitType = !currentBitType;
	}
}
















