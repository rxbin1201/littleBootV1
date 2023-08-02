/*

    littleBootV1 - 02.08.23 
    config.c

*/

// Import libraries
#include <Config/config.h>

// Define global varibale
UINT8 *gConfigBuffer = NULL;

EFI_STATUS InitConfig() {

    // Declare variables
    CHAR16 *ConfigFile = CONFIG_FILE;

    // Read config file into buffer
    gConfigBuffer = ReadFile(ConfigFile);
    if(gConfigBuffer == NULL) {
        return EFI_NOT_FOUND;
    }

    //Log(0xFF94A3B8, "Configuration:\n");
    //Log(0xFF94A3B8, (char*)gConfigBuffer);
}