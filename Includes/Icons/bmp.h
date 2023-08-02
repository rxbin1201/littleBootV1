/*

    littleBootV1 - 02.08.23 
    bmp.h

*/

#ifndef __BMP_H
#define __BMP_H

// Import libraries
#include <efi.h>
#include <efilib.h>

#include <File/file.h>
#include <Utils/log.h>
#include <Utils/util.h>

typedef struct {
    UINT16 HeaderField;
    UINT32 Size;
    UINT16 Reserved[2];
    UINT32 OffsetPixelArray;
    UINT32 HeaderSize;
    UINT32 BitmapWidth;
    UINT32 BitmapHeight;
    UINT16 ColorPlane;
    UINT16 Bpp;
    UINT32 CompressionMethod;
    UINT32 ImageSize;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    UINT32 ColorNumber;
    UINT32 ImportantColorNumber;
    UINT32 UnitsVerticalHorizontalResolution;
    UINT16 Padding;
    UINT16 DirectionBitsFill;
    UINT16 HalftoningAlgorithms;
    UINT32 HalftoningParameter1;
    UINT32 HalftoningParameter2;
    UINT32 ColorEncoding;
    UINT32 ApplicationDefinedIdentifier;
} BMP_HEADER;

typedef struct Vec2 {
    UINT32 x;
    UINT32 y;
} Vec2;

typedef struct Vec3 {
    UINT8 Red;
    UINT8 Green;
    UINT8 Blue;
    UINT8 Alpha;
} Vec3;

// Declare functions
BMP_HEADER *ParseBmpHeader(UINT8 *BmpArray);
VOID DrawBmp(Vec2 Position, Vec2 BmpSize, CHAR16 *Filename);

#endif // End of file