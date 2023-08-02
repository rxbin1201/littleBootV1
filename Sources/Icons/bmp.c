/*

    littleBootV1 - 02.08.23 
    bmp.c

*/

// Import libraries
#include <Icons/bmp.h>

BMP_HEADER *ParseBmpHeader(UINT8 *BmpBuffer) {

    BMP_HEADER *BmpHeader = (BMP_HEADER *)AllocatePool(sizeof(BMP_HEADER));

    BmpHeader->HeaderField = (BmpBuffer[0] << 8) | BmpBuffer[1];
    BmpHeader->Size = (BmpBuffer[2] << 24) | (BmpBuffer[3] << 16) | (BmpBuffer[4] << 8) | BmpBuffer[5];
    BmpHeader->Size = (BmpBuffer[2] << 24) | (BmpBuffer[3] << 16) | (BmpBuffer[4] << 8) | BmpBuffer[5];
    BmpHeader->Reserved[0] = (BmpBuffer[6] << 8) | BmpBuffer[7];
    BmpHeader->Reserved[1] = (BmpBuffer[8] << 8) | BmpBuffer[9];
    BmpHeader->OffsetPixelArray = (BmpBuffer[10] << 24) | (BmpBuffer[11] << 16) | (BmpBuffer[12] << 8) | BmpBuffer[13];
    BmpHeader->HeaderSize = (BmpBuffer[14] << 24) | (BmpBuffer[15] << 16) | (BmpBuffer[16] << 8) | BmpBuffer[17];
    BmpHeader->BitmapWidth = (BmpBuffer[18] << 24) | (BmpBuffer[19] << 16) | (BmpBuffer[20] << 8) | BmpBuffer[21];
    BmpHeader->BitmapHeight = (BmpBuffer[22] << 24) | (BmpBuffer[23] << 16) | (BmpBuffer[24] << 8) | BmpBuffer[25];
    BmpHeader->ColorPlane = (BmpBuffer[26] << 8) | BmpBuffer[27];
    BmpHeader->Bpp = (BmpBuffer[28] << 8) | BmpBuffer[29];
    BmpHeader->CompressionMethod = (BmpBuffer[30] << 24) | (BmpBuffer[31] << 16) | (BmpBuffer[32] << 8) | BmpBuffer[33];
    BmpHeader->ImageSize = (BmpBuffer[34] << 24) | (BmpBuffer[35] << 16) | (BmpBuffer[36] << 8) | BmpBuffer[37];
    BmpHeader->HorizontalResolution = (BmpBuffer[38] << 24) | (BmpBuffer[39] << 16) | (BmpBuffer[40] << 8) | BmpBuffer[41];
    BmpHeader->VerticalResolution = (BmpBuffer[42] << 24) | (BmpBuffer[43] << 16) | (BmpBuffer[44] << 8) | BmpBuffer[45];
    BmpHeader->ColorNumber = (BmpBuffer[46] << 24) | (BmpBuffer[47] << 16) | (BmpBuffer[48] << 8) | BmpBuffer[49];
    BmpHeader->ImportantColorNumber = (BmpBuffer[50] << 24) | (BmpBuffer[51] << 16) | (BmpBuffer[52] << 8) | BmpBuffer[53];
    BmpHeader->UnitsVerticalHorizontalResolution = (BmpBuffer[54] << 24) | (BmpBuffer[55] << 16) | (BmpBuffer[56] << 8) | BmpBuffer[57];
    BmpHeader->Padding = (BmpBuffer[58] << 8) | BmpBuffer[59];
    BmpHeader->DirectionBitsFill = (BmpBuffer[60] << 8) | BmpBuffer[61];
    BmpHeader->HalftoningAlgorithms = (BmpBuffer[62] << 8) | BmpBuffer[63];
    BmpHeader->HalftoningParameter1 = (BmpBuffer[64] << 24) | (BmpBuffer[65] << 16) | (BmpBuffer[66] << 8) | BmpBuffer[67];
    BmpHeader->HalftoningParameter2 = (BmpBuffer[68] << 24) | (BmpBuffer[69] << 16) | (BmpBuffer[70] << 8) | BmpBuffer[71];
    BmpHeader->ColorEncoding = (BmpBuffer[72] << 24) | (BmpBuffer[73] << 16) | (BmpBuffer[74] << 8) | BmpBuffer[75];
    BmpHeader->ApplicationDefinedIdentifier = (BmpBuffer[76] << 24) | (BmpBuffer[77] << 16) | (BmpBuffer[78] << 8) | BmpBuffer[79];

    return BmpHeader;
}

VOID DrawBmp(Vec2 Position, Vec2 BmpSize, CHAR16 *Filename) {

    // Declare variables
    Vec3 PixelValue;
    UINT8 *BmpBuffer = ReadFile(Filename);
    BMP_HEADER *BmpHeader = ParseBmpHeader(BmpBuffer);

    if(BmpHeader->HeaderField == 0x424D) {

        for(UINT32 i = (Position.y + (BmpSize.y - 1)); i > Position.y; i--) {
            UINT8 *BmpRow = (BmpBuffer + BmpBuffer[10]) + (i - Position.y) * BmpSize.x * 4; //BmpBuffer[0x1E];
            UINT32 Offset = 0;
            for(UINT32 j = Position.x; j < (Position.x + BmpSize.x); j++) {
                PixelValue.Blue = BmpRow[Offset++] & 0xFF;
                PixelValue.Green = BmpRow[Offset++] & 0xFF;
                PixelValue.Red = BmpRow[Offset++] & 0xFF;
                PixelValue.Alpha = BmpRow[Offset++] & 0xFF;
                *((UINT32*)(gGop->Mode->FrameBufferBase + (4 * gGop->Mode->Info->PixelsPerScanLine * i) + (4 * j))) = ((PixelValue.Red << 16) | (PixelValue.Green << 8) | PixelValue.Blue);
            }
        }

        FreePool(BmpBuffer);
        FreePool(BmpHeader);
    } else {
        Log(0xFFEF4444, "Unsupported Bitmap format!\n");
    }

} // End of file

