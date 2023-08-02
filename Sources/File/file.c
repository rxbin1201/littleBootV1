/*

    littleBootV1 - 02.08.23 
    file.c

*/

// Import libraries
#include <File/file.h>

UINT64 FileSize(EFI_FILE_HANDLE FileHandle) {
    
    // Declare variables
    UINT64 ReturnValue;
    EFI_FILE_INFO *FileInfo;

    // Get the filesize
    FileInfo = LibFileInfo(FileHandle);
    ReturnValue = FileInfo->FileSize;

    FreePool(FileInfo);

    return ReturnValue;
}
/*
UINT8 *ReadFile(CHAR16 *Filename) {

    // Declare variables
    EFI_STATUS Status;
    EFI_FILE_HANDLE FileHandle;
    EFI_FILE_HANDLE Volume = GetVolume(gImageHandle);
    UINT64 ReadSize;
    UINT8 *Buffer;

    // Open the file
    Status = uefi_call_wrapper(
        Volume->Open,
        5,
        Volume,
        &FileHandle,
        Filename,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not open file! Reason: %r\n", Status);
    }

    // Read the contents of the file
    ReadSize = FileSize(FileHandle);
    Buffer = AllocatePool(ReadSize);

    Status = uefi_call_wrapper(
        FileHandle->Read,
        3,
        FileHandle,
        &ReadSize,
        Buffer
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not read file! Reason: %r\n", Status);
    }

    // Close the file
    Status = uefi_call_wrapper(
        FileHandle->Close,
        1,
        FileHandle
    );
    if(EFI_ERROR(Status)) {
        Print(L"Could not close file! Reason: %r\n", Status);
    }

    return Buffer;
}*/

UINT8* ReadFile(CHAR16* Filename) {
    // Declare variables
    EFI_STATUS Status;
    EFI_FILE_HANDLE FileHandle;
    EFI_FILE_HANDLE Volume = GetVolume(gImageHandle);
    UINT64 ReadSize;
    UINT8* Buffer = NULL; // Initialize the buffer to NULL

    // Open the file
    Status = uefi_call_wrapper(
        Volume->Open,
        5,
        Volume,
        &FileHandle,
        Filename,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM
    );
    if (EFI_ERROR(Status)) {
        Print(L"Could not open file! Reason: %r\n", Status);
        return NULL; // Return NULL in case of an error
    }

    // Read the contents of the file
    ReadSize = FileSize(FileHandle);
    Buffer = AllocatePool(ReadSize + 1); // Allocate one extra byte for null-terminator

    if (Buffer != NULL) {
        Status = uefi_call_wrapper(
            FileHandle->Read,
            3,
            FileHandle,
            &ReadSize,
            Buffer
        );
        if (EFI_ERROR(Status)) {
            Print(L"Could not read file! Reason: %r\n", Status);
            FreePool(Buffer); // Free the buffer in case of an error
            Buffer = NULL;
        } else {
            // Null-terminate the buffer
            Buffer[ReadSize] = '\0';

            // Handle Windows-style CRLF (CR followed by LF) and convert to LF (\n)
            UINTN i;
            for (i = 0; i < ReadSize; i++) {
                if (Buffer[i] == '\r' && Buffer[i + 1] == '\n') {
                    Buffer[i] = '\n';
                    // Shift the remaining characters to the left by 1
                    CopyMem(&Buffer[i + 1], &Buffer[i + 2], ReadSize - i - 1);
                    ReadSize--; // Decrement the size to account for the removal of '\r'
                }
            }
        }
    } else {
        Print(L"Memory allocation failed!\n");
    }

    // Close the file
    Status = uefi_call_wrapper(
        FileHandle->Close,
        1,
        FileHandle
    );
    if (EFI_ERROR(Status)) {
        Print(L"Could not close file! Reason: %r\n", Status);
    }

    return Buffer;
}

EFI_FILE* LoadFile(EFI_FILE *Directory, CHAR16 *Path) {

    // Define variables 
    EFI_STATUS Status;
    EFI_FILE *LoadedFile;
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    EFI_GUID LoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFileSystem;

    // Handle loaded image protocol
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        gImageHandle,
        &LoadedImageProtocolGuid,
        (VOID **)&LoadedImage
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    // Handle simple file system protocol
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        LoadedImage->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID **)&SimpleFileSystem
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    // Open volume
    if(Directory == NULL) {
        Status = uefi_call_wrapper(
            SimpleFileSystem->OpenVolume,
            2,
            SimpleFileSystem,
            &Directory
        );
        if(EFI_ERROR(Status)) {
            return NULL;
        }
    }

    // Open file
    Status = uefi_call_wrapper(
        Directory->Open,
        5,
        Directory,
        &LoadedFile,
        Path,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    return LoadedFile;
} // End of file