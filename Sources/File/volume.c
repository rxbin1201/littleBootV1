/*

    littleBootV1 - 02.08.23 
    volume.c

*/

// Import libraries
#include <File/volume.h>

EFI_FILE_HANDLE GetVolume(EFI_HANDLE ImageHandle) {

    // Declare variables
    EFI_STATUS Status;
    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_GUID LoadedImageProtocol = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_FILE_IO_INTERFACE *FileIoInterface;
    EFI_GUID SimpleFileSystemProtocol = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_FILE_HANDLE Volume;

    // Get the loaded image protocol
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        ImageHandle,
        &LoadedImageProtocol,
        (VOID **)&LoadedImage
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not get the loaded image protocol(LIP)! Reason: %r\n", Status);
        return NULL;
    }

    // Get the volume handle
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        LoadedImage->DeviceHandle,
        &SimpleFileSystemProtocol,
        (VOID **)&FileIoInterface
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not get the volume handle! Reason: %r\n", Status);
        return NULL;
    }

    // Open volume
    Status = uefi_call_wrapper(
        FileIoInterface->OpenVolume,
        2,
        FileIoInterface,
        &Volume
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not open the volume! Reason: %r\n", Status);
        return NULL;
    }

    return Volume;
} // End of file