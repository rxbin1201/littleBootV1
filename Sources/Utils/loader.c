/*

    littleBootV1 - 02.08.23 
    loader.c

*/

// Import libraries
#include <Utils/loader.h>

typedef unsigned long long size_t;

int memcmp(const void* aptr, const void* bptr, size_t n){
	const unsigned char* a = aptr, *b = bptr;
	for (size_t i = 0; i < n; i++){
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}

EFI_STATUS LoadKernel(CHAR16* KernelPath) {

    // Declare variables
    EFI_STATUS Status;
    EFI_FILE* Kernel;
    EFI_FILE_INFO* FileInfo;
    Elf64_Ehdr ELF64_HEADER;
    UINTN FileInfoSize;
    UINTN KernelSize;

    Kernel = LoadFile(NULL, L"kernel64.elf");
    if(Kernel == NULL) {
        Log(0xFFEF4444, "Kernel not found!\n");
        return EFI_LOAD_ERROR;
    } else {
        Log(0xFF22C55E, "Kernel found.\n");
    }

    Status = uefi_call_wrapper(
        Kernel->GetInfo,
        4,
        Kernel,
        &gEfiFileInfoGuid,
        &FileInfoSize,
        NULL
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        FileInfoSize,
        (VOID **)&FileInfo
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    Status = uefi_call_wrapper(
        Kernel->GetInfo,
        4,
        Kernel,
        &gEfiFileInfoGuid,
        &FileInfoSize,
        (VOID **)&FileInfo
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    KernelSize = sizeof(ELF64_HEADER);

    // Stucks here

    Status = uefi_call_wrapper(
        Kernel->Read,
        3,
        Kernel,
        &KernelSize,
        &ELF64_HEADER
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    return EFI_SUCCESS;
}