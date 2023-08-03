/*

    littleBootV1 - 02.08.23
    main.c

*/

// Import libraries
#include <efi.h>
#include <efilib.h>

#include <Config/config.h>
#include <File/file.h>
#include <Font/psf1.h>
#include <Icons/bmp.h>
#include <Utils/loader.h>
#include <Utils/log.h>
#include <Utils/util.h>
#include <Utils/time.h>

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    // Initialize the UEFI
    InitializeLib(ImageHandle, SystemTable);

    // Declare variables
    EFI_STATUS Status;

    Status = SetImageHandle(ImageHandle);
    if(EFI_ERROR(Status)) {
        Print(L"Could not set gImageHandle! Reason: %r\n", Status);
    }

    Status = SetSystemTable(SystemTable);
    if(EFI_ERROR(Status)) {
        Print(L"Could not set gSystemTable! Reason: %r\n", Status);
    }

    Status = SetGop();
    if(EFI_ERROR(Status)) {
        Print(L"Could not set gGop! Reason: %r\n", Status);
    }

    SetFrameBuffer();

    Status = SetPsf1Font();

    Status = uefi_call_wrapper(
        SystemTable->ConOut->ClearScreen,
        1,
        SystemTable->ConOut
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not clear screen! Reason: %r\n", Status);
    }

    // Print with new Font using the Log(unsigned int Colour, char *String) function
    DrawBmp((Vec2){0, 0},(Vec2){800, 600},L"background.bmp");

    Log(0xFF7DD3FC, "littleBootV1 - DEV STATE\n");
    Log(0xFF22C55E, "Hello World from new font, but with an other color!\n");

    Status = InitConfig();
    if(EFI_ERROR(Status)) {
        Log(0xFFEF4444, "Config not found!\n");
    }

    DisplayTime();

    Log(0xFF94A3B8, "\nLoading kernel...\n");

    Status = LoadKernel(L"kernel64.elf");
    if(EFI_ERROR(Status)) {
        Print(L"Error Kernel! Reason: %r\n", Status);
    }
    
    //Log(0xFF94A3B8, "Verifying Kernel header...\n");    

    while(1){};

    return EFI_SUCCESS;
}  // End of file