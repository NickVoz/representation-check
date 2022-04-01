#include "stdio.h"

// Returns 1 if the system is using big endian representation, else returns 0
//
// creates a short variable with value 1, in order to get a
// byte-level representation of the long variable, it casts the short
// to a char pointer.
// If the dereferenced char pointer value is 1 - the machine is using little
// endian representation, since the first byte, which holds the long's single digits
// value(which is 1), contains the data.
// otherwise - it uses big endian representation
int is_big_endian() {
    unsigned long a = 1;
    unsigned char *b = (unsigned char*) &a;
    if (*b) {
        return 0;
    }
    return 1;
}
// This function merges the first numerical half of one long, 
// and the second half of another. 
// it does so by converting the long pointers to int pointers, resulting
// in pointers that point to 4 bytes in the memory, meaning that each
// pointer points to the numerical first half of the long. Afterwards 
// merging them into an array(which is of length 8 bytes). it returns the
// conversion of the array back to a long, resulting in the merged word.
unsigned long merge_bytes(unsigned long x, unsigned long int y) {
    unsigned int *leftHalf = (unsigned int*) &x; 
    unsigned int *rightHalf = (unsigned int*) &y;
    // check if system is using big endian representation
    if (is_big_endian()) {
        rightHalf++;
        unsigned int intToLong[] = {*leftHalf, *rightHalf};
        return *((unsigned long*) &intToLong);
    }
    // system is using little endian representation
    leftHalf++;
    unsigned int intToLong[] = {*rightHalf, *leftHalf};
    return *((unsigned long*) &intToLong);

}
// Receives a byte-sized word(represent by a char) and inserts it into
// the desired byte position in a long word.
// 
//
//
unsigned long put_byte(unsigned long x, unsigned char b, int i) {
    // Check if system is using big endian representation
    unsigned char *a = (unsigned char*) &x;
    if (is_big_endian()) {
        *(a + i) = b;
        return *((unsigned long*) a);
    }
    // System is using little endian representation
    *(a + sizeof(unsigned long) - 1 - i ) = b;
    return *((unsigned long*) a);
}
