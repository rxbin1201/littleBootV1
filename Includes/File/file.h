/*

    littleBootV1 - 02.08.23 
    file.h

*/

#ifndef __FILE_H
#define __FILE_H

// Import libraries
#include <efi.h>
#include <efilib.h>

#include <File/volume.h>
#include <Utils/util.h>

// Declare functions
UINT64 FileSize(EFI_FILE_HANDLE FileHandle);
UINT8 *ReadFile(CHAR16 *Filename);
EFI_FILE* LoadFile(EFI_FILE *Directory, CHAR16 *Path);

#endif // End of file