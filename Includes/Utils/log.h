/*

    littleBootV1 - 02.08.23 
    log.h

*/

#ifndef __LOG_H
#define __LOG_H

// Import libraries
#include <efi.h>
#include <efilib.h>

#include <Utils/util.h>

// Declare functions
VOID LogChar(unsigned int Colour, char Char, unsigned int xOff, unsigned int yOff);
VOID Log(unsigned int Colour, char *String);

#endif // End of file