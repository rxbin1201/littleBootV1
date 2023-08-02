/*

    littleBootV1 - 02.08.23 
    psf1.h

*/

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <File/file.h>
#include <Utils/util.h>

#ifndef __PSF1_H
#define __PSF1_H

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

typedef struct {
    UINT8 Magic[2];
    UINT8 Mode;
    UINT8 CharSize;
} PSF1_HEADER;

typedef struct {
    PSF1_HEADER *Psf1Header;
    VOID *GlyphBuffer;
} PSF1_FONT;

// Declare functions
PSF1_FONT* LoadPsf1Font(CHAR16 *File);

#endif // End of file