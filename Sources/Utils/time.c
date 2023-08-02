/*

    littleBootV1 - 02.08.23 
    time.c

*/

// Import libraries
#include <Utils/time.h>

VOID DisplayTime() {
    
    // Declare variables
    EFI_TIME currentTime;
    EFI_STATUS Status;

    Status = uefi_call_wrapper(
        RT->GetTime,
        2,
        &currentTime,
        NULL
    );
    if(EFI_ERROR(Status)) {
        Log(0xFFEF4444, "Unable to get current time!\n");
    }

    CHAR16 TimeStr[9]; // Buffer to store formatted time string "hh:mm:ss"

    // Format hour, minute, and second as a string
    SPrint(TimeStr, sizeof(TimeStr), L"%02d:%02d:%02d", 
           currentTime.Hour, currentTime.Minute, currentTime.Second);

    // Convert CHAR16 (wide string) to ASCII (char) if needed
    CHAR8 AsciiTimeStr[9];
    for (UINTN i = 0; i < sizeof(TimeStr); i++) {
        AsciiTimeStr[i] = (CHAR8)TimeStr[i];
    }

    Log(0xFF94A3B8, AsciiTimeStr);

} // End of file