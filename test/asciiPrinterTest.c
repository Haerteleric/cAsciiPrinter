#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

/*****************************TEMPLATE INCLUDE**************************************/
#define ASCII_PRINTER_INLINE_IMPLEMENTATION
#define ASCII_PRINTER_STATIC_IMPLEMENTATION

//following just for testing
#define ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
#include "asciiPrinter_t.h" //Prototype
#undef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
#include "asciiPrinter_t.h" //Implementation
/***********************************************************************************/

static char buffer[100];
static int bufferLength = 0;


unsigned print(char * data, unsigned int dataLength)
{
    for (unsigned int i = 0; i < dataLength; i++)
    {
        buffer[bufferLength++] = data [i];
    }
    return dataLength;
}
int main(void)
{
    clock_t startTime = clock();
   
    unsigned int value = 0xcafeaffe;
    ascii_putHexLittleEndian(print, &value, sizeof(value));
    buffer[bufferLength++] = '\0';
    assert(strcmp("CAFEAFFE\0",buffer) == 0);
    bufferLength = 0;
    
    value = 0x123cadd;
    ascii_putHexLittleEndian(print, &value, sizeof(value));
    buffer[bufferLength++] = '\0';
    assert(strcmp("0123CADD\0",buffer) == 0);
    bufferLength = 0;

    value = 12345;
    ascii_putUnsignedDecimal(print, value);
    buffer[bufferLength++] = '\0';
    assert(strcmp("12345\0",buffer) == 0);
    bufferLength = 0;
    
    ascii_putNibbleHex(print, 0xA);
    buffer[bufferLength++] = '\0';
    assert(strcmp("A\0",buffer) == 0);
    bufferLength = 0;

    ascii_putNibbleHex(print, 0x0);
    buffer[bufferLength++] = '\0';
    assert(strcmp("0\0",buffer) == 0);
    bufferLength = 0;

    double elapsedTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsedTime);
}