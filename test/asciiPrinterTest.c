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



int main(void)
{
    char out[500];
    unsigned int outPos = 0;
    memset(out, 0, sizeof(out));

    //Test unsigned print
    outPos = ascii_sprintf(out, "%u", 2);
    assert(strcmp("2",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%u", 0);
    assert(strcmp("0",out) == 0);
    memset(out, 0, sizeof(out));
    
    outPos = ascii_sprintf(out, "%u", 55432);
    assert(strcmp("55432",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%u", 88843);
    assert(strcmp("88843",out) == 0);
    memset(out, 0, sizeof(out));
     
    outPos = ascii_sprintf(out, "%u", 7777777);
    assert(strcmp("7777777",out) == 0);
    memset(out, 0, sizeof(out));


    //Test Signed print
    outPos = ascii_sprintf(out, "%i", -2);
    assert(strcmp("-2",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%i", -0);
    assert(strcmp("0",out) == 0);
    memset(out, 0, sizeof(out));
    
    outPos = ascii_sprintf(out, "%i", -55432);
    assert(strcmp("-55432",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%i", -88843);
    assert(strcmp("-88843",out) == 0);
    memset(out, 0, sizeof(out));
     
    outPos = ascii_sprintf(out, "%i", -7777777);
    assert(strcmp("-7777777",out) == 0);
    memset(out, 0, sizeof(out));

    //Test Hex print
    union 
    {
        unsigned int asInt;
        unsigned char asStream[sizeof(unsigned int)];
    }testHexValues=
    {
        .asStream = {0x00,0xBB,0x22,0xAA}
    };

    outPos = ascii_sprintf(out, "%x", testHexValues.asInt);
    assert(strcmp("AA22BB00",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%x01", &testHexValues.asStream);
    assert(strcmp("00",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%x02", &testHexValues.asStream);
    assert(strcmp("00BB",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%x03", &testHexValues.asStream);
    assert(strcmp("00BB22",out) == 0);
    memset(out, 0, sizeof(out));

    outPos = ascii_sprintf(out, "%x04", &testHexValues.asStream);
    assert(strcmp("00BB22AA",out) == 0);
    memset(out, 0, sizeof(out));

}