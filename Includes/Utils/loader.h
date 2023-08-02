/*

    littleBootV1 - 02.08.23 
    loader.h

*/

#ifndef __LOADER_H
#define __LOADER_H

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <File/file.h>
#include <Utils/elf.h>
#include <Utils/log.h>

// Declare functions
EFI_STATUS LoadKernel(CHAR16* KernelPath);

#endif // End of file