/**
 * Portable ascii printer template implementation
 * 
 * Author:    Haerteleric
 * 
 * MIT License
 * 
 * Copyright (c) 2023 Eric Härtel
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/
#include <stddef.h>
#include <stdbool.h>

typedef unsigned int (* write_func)(char* asciiChars, unsigned int numAsciiChars);


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
char ascii_unsignedValue2HexChar(unsigned char input)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
#ifdef ASCII_PRINTER_LOWERCASE_HEX
    return input + ( input >= 0xA ? ('a' - 0xA) : '0');
#else
    return input + ( input >= 0xA ? ('A' - 0xA) : '0');
#endif
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
void ascii_putNibbleHex(write_func output, unsigned char nibble)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    char nibbleAscii = ascii_unsignedValue2HexChar(nibble);
    output(&nibbleAscii,1);
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
void ascii_putByteHex(write_func output, unsigned char byte)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    ascii_putNibbleHex(output, (byte & 0b11110000) >> 4);
    ascii_putNibbleHex(output, byte & 0b00001111);
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
void ascii_putUnsignedDecimal(write_func output, unsigned int unsignedNum)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int decMask = 1000000000; // 4,294,967,295 is unsigned int Max (2^32)
    char currentDigit = 0;

#ifndef ASCII_PRINTER_UNSIGNED_LEADING_ZEROS
    bool wordStarted = false;
#endif

    while (decMask)
    {
        currentDigit = unsignedNum / decMask;
        unsignedNum -=  decMask * currentDigit;
        
#ifndef ASCII_PRINTER_UNSIGNED_LEADING_ZEROS
        if(wordStarted || (currentDigit > 0))
#endif
        {
            wordStarted = true;
            currentDigit += '0';
            output(&currentDigit, 1);
        }

        decMask /= 10;
    }

#ifndef ASCII_PRINTER_UNSIGNED_LEADING_ZEROS
    if(!wordStarted)
    {
        output("0", 1);
    }
#endif
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
void ascii_putHexLittleEndian(write_func output, unsigned char * data, unsigned int size)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    for (size_t i = 0; i < size; i++)
    {
        ascii_putByteHex(output, data[size-1-i]);
    }
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
void ascii_putHexBigEndian(write_func output, unsigned char * data, unsigned int size)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    for (size_t i = 0; i < size; i++)
    {
        ascii_putByteHex(output, data[i]);
    }
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)