/*

    littleBootV1 - 02.08.23 
    log.c

*/

// Import libraries
#include <Utils/log.h>

VOID LogChar(unsigned int Colour, char Char, unsigned int xOff, unsigned int yOff) {
    unsigned int* pixPtr = (unsigned int*)gFrameBuffer.BaseAddress;
    char* fontPtr = gFont->GlyphBuffer + (Char * gFont->Psf1Header->CharSize);
    for(unsigned long y = yOff; y < yOff + 18; y++) {
        for(unsigned long x = xOff; x < xOff + 8; x++) {
            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0) {
                pixPtr[x + (y * gFrameBuffer.PixelsPerScanLine)] = Colour;
            }
        }
        fontPtr++;
    }
}

VOID Log(unsigned int Colour, char* String) {
    char* chr = String;
    while (*chr != 0) {
        if (*chr == '\n') {
            // Handle newline character: move to the next line and reset X position
            CursorPosition.X = 0;
            CursorPosition.Y += 18;
        } else {
            LogChar(Colour, *chr, CursorPosition.X, CursorPosition.Y);
            CursorPosition.X += 8;
            if (CursorPosition.X + 8 > gFrameBuffer.Width) {
                CursorPosition.X = 0;
                CursorPosition.Y += 18;
            }
        }
        chr++;
    }
} // End of file