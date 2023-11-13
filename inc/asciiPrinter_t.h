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
#include <stdarg.h>
#include <stdbool.h>

#ifndef _ASCII_PRINTER_INCLUDED
#define _ASCII_PRINTER_INCLUDED
#endif


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
unsigned int ascii_putNibbleHex(char * dest, unsigned char nibble)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    char nibbleAscii = ascii_unsignedValue2HexChar(nibble);
    *dest = nibbleAscii;

    //Always One Char
    return 1;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putByteHex(char * dest, unsigned char byte)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    ascii_putNibbleHex(&dest[0], (byte & 0b11110000) >> 4);
    ascii_putNibbleHex(&dest[1], byte & 0b00001111);

    //Always Two Char
    return 2;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)

#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putHexByteStream(char * dest, unsigned char * stream, unsigned int len)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    for (unsigned int i = 0; i < len; i++)
    {
        ascii_putByteHex(&dest[i*2],stream[i]);
    }

    return len*2;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putUnsignedDecimal(char * dest, unsigned int unsignedNum)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int decMask = 1000000000; // 4,294,967,295 is unsigned int Max (2^32)
    char currentDigit = 0;

#ifndef ASCII_PRINTER_UNSIGNED_LEADING_ZEROS
    bool wordStarted = false;
    unsigned int numCharsWritten = 0;
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
            dest[numCharsWritten++] = currentDigit;
        }

        decMask /= 10;
    }

#ifndef ASCII_PRINTER_UNSIGNED_LEADING_ZEROS

    if(!wordStarted)
    {
        dest[numCharsWritten++] = '0';
    }
    return numCharsWritten;

#else

    //Always 10 Digits
    return 10;

#endif // NOT(ASCII_PRINTER_UNSIGNED_LEADING_ZEROS)
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)

#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putSignedDecimal(char * dest, signed int signedNum)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int numCharsWritten = 0;

    if(signedNum < 0)
    {
        dest[numCharsWritten++] = '-';
        signedNum = -signedNum;
    }

    numCharsWritten += ascii_putUnsignedDecimal(&dest[numCharsWritten], signedNum);

    return numCharsWritten;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putHexLittleEndian(char * dest, unsigned char * data, unsigned int size)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int offset = 0;
    for (size_t i = 0; i < size; i++)
    {
        offset += ascii_putByteHex(&dest[offset], data[size-1-i]);
    }

    return size * 2; //2 Chars per Byte
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)



#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif 
unsigned int ascii_putHexBigEndian(char * dest, unsigned char * data, unsigned int size)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int offset = 0;
    for (size_t i = 0; i < size; i++)
    {
        offset += ascii_putByteHex(&dest[offset], data[i]);
    }

    return size * 2; //2 Chars per Byte
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif
unsigned int ascii_putString(char * dest, unsigned char * str)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
    unsigned int numCharsWritten = 0;
    while(*str != '\0')
    {
        dest[numCharsWritten++] = *str;
        str++;
    }

    return numCharsWritten;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif
unsigned int ascii_vsprintf(char * dest, const char * msgFormat, va_list vaList)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
  unsigned int parsePos = 0;
  unsigned int numCharsWritten = 0;

  parsePos = 0;
  //Generate Final Message
  while(msgFormat[parsePos] != '\0')
  {
      if(msgFormat[parsePos] == '%')
      {
          parsePos++; //skip over wildcard escape char

          switch(msgFormat[parsePos])
          {
          case 'u':
            {
              unsigned int decValue = va_arg(vaList, unsigned int);
              numCharsWritten += ascii_putUnsignedDecimal(&dest[numCharsWritten], decValue);
            }break;

          case 'i':
            {
              signed int decValue = va_arg(vaList, unsigned int);
              numCharsWritten += ascii_putSignedDecimal(&dest[numCharsWritten], decValue);
            }break;

          case 's':
            {
              numCharsWritten += ascii_putString(&dest[numCharsWritten],va_arg(vaList, char *));
            }break;

          case 'x':
            {
              if(msgFormat[parsePos + 1] == '0')
              {
                parsePos++;
                unsigned char * startAddress = va_arg(vaList, unsigned char *);
                unsigned int bytesToPrint = msgFormat[++parsePos] - '0';
                numCharsWritten += ascii_putHexByteStream(&dest[numCharsWritten], startAddress, bytesToPrint);
              }
              else
              {
                unsigned int hexValue = va_arg(vaList, unsigned int);
                numCharsWritten += ascii_putHexLittleEndian(&dest[numCharsWritten], (unsigned char * )&hexValue ,sizeof(unsigned int));
              }
            }break;

          default:
            {
            }break;
          }

          parsePos++; //skip over wildcard identifier char
      }
      else
      {
          dest[numCharsWritten++] = msgFormat[parsePos++];
      }
  }

  return numCharsWritten;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif
unsigned int ascii_getNumWildcards(const char * msgFormat)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
  unsigned int parsePos = 0;
  unsigned int numWildcards = 0;

  while(msgFormat[parsePos] != '\0')
  {
      if(msgFormat[parsePos++] == '%')
      {
          numWildcards++;
      }
  }

  return numWildcards;
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)


#ifdef ASCII_PRINTER_INLINE_IMPLEMENTATION
inline
#endif
#ifdef ASCII_PRINTER_STATIC_IMPLEMENTATION
static
#endif
unsigned int ascii_sprintf(char * dest, const char * msgFormat, ...)
#ifdef ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION
;
#else
{
  va_list vaList;
  va_start(vaList, msgFormat);

  return ascii_vsprintf(dest, msgFormat, vaList);
}
#endif // NOT(ASCII_PRINTER_ONLY_PROTOTYPE_DECLARATION)




