/*

    littleBootV1 - 02.08.23 
    util.h

*/

#ifndef __UTIL_H
#define __UTIL_H

// Import libraries
#include <efi.h>
#include <efilib.h>

#include <Font/psf1.h>

typedef struct {
    VOID *BaseAddress;
    UINTN BufferSize;
    UINTN Width;
    UINTN Height;
    UINTN PixelsPerScanLine;
} FRAME_BUFFER;

typedef struct {
    unsigned int X;
    unsigned int Y;
} Point;

// Declare variables
extern EFI_HANDLE gImageHandle;
extern EFI_SYSTEM_TABLE *gSystemTable;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *gGop;
extern FRAME_BUFFER gFrameBuffer;
extern PSF1_FONT *gFont;
extern Point CursorPosition;


// Declare functions
EFI_STATUS SetGop();
EFI_STATUS SetImageHandle(EFI_HANDLE ImageHandle);
EFI_STATUS SetSystemTable(EFI_SYSTEM_TABLE *SystemTable);
FRAME_BUFFER* SetFrameBuffer();
EFI_STATUS SetPsf1Font();

#endif // End of file