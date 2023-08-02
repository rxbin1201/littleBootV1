/*

    littleBootV1 - 02.08.23 
    config.h

*/

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_FILE L"littleboot.cfg"

// Import libraries
#include <efi.h>
#include <efilib.h>
#include <File/file.h>
#include <Utils/log.h>

// Declare variables
extern UINT8 *ConfigBuffer;

// Declare functions
EFI_STATUS InitConfig();
UINT8 *GetConfigValue(UINT8* Key);

#endif // End of file
