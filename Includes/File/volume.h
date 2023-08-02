/*

    littleBootV1 - 02.08.23 
    volume.h

*/

#ifndef __VOLUME_H
#define __VOLUME_H

// Import libraries
#include <efi.h>
#include <efilib.h>

// Declare functions
EFI_FILE_HANDLE GetVolume(EFI_HANDLE ImageHandle);

#endif // End of file