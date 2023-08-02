/*

    littleBootV1 - 02.08.23 
    util.c

*/

// Import libraries
#include <Utils/util.h>

// Define global varibale
EFI_HANDLE gImageHandle = NULL;
EFI_SYSTEM_TABLE *gSystemTable = NULL;
EFI_GRAPHICS_OUTPUT_PROTOCOL *gGop = NULL;
FRAME_BUFFER gFrameBuffer;
PSF1_FONT *gFont = NULL; 

EFI_STATUS SetImageHandle(EFI_HANDLE ImageHandle) {
    gImageHandle = ImageHandle;
}
EFI_STATUS SetSystemTable(EFI_SYSTEM_TABLE *SystemTable) {
    gSystemTable = SystemTable;
}

EFI_STATUS SetGop() {

    // Declare variables
    EFI_STATUS Status;

    // Locate the graphics output protocol
    Status = uefi_call_wrapper(
        BS->LocateProtocol,
        3,
        &GraphicsOutputProtocol,
        NULL,
        (VOID **)&gGop
    );
    
    return Status;
}

FRAME_BUFFER* SetFrameBuffer() {
    gFrameBuffer.BaseAddress = (VOID **)gGop->Mode->FrameBufferBase;
    gFrameBuffer.BufferSize = gGop->Mode->FrameBufferSize;
    gFrameBuffer.Width = gGop->Mode->Info->HorizontalResolution;
    gFrameBuffer.Height = gGop->Mode->Info->VerticalResolution;
    gFrameBuffer.PixelsPerScanLine = gGop->Mode->Info->PixelsPerScanLine;
}

EFI_STATUS SetPsf1Font() {
    gFont = LoadPsf1Font(L"font18.psf");
    if(gFont == NULL) {
        Print(L"Psf1-Font is not valid or not found!\n");
        return EFI_LOAD_ERROR;
    }
} // End of file