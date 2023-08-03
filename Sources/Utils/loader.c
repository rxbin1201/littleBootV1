/*

    littleBootV1 - 02.08.23 
    loader.c

*/

// Import libraries
#include <Utils/loader.h>

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
    Elf64_Phdr* ELF64_PHEADER;
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

    KernelSize = sizeof(ELF64_HEADER);

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

    if(
        memcmp(&ELF64_HEADER.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
		ELF64_HEADER.e_ident[EI_CLASS] != ELFCLASS64 ||
		ELF64_HEADER.e_ident[EI_DATA] != ELFDATA2LSB ||
		ELF64_HEADER.e_type != ET_EXEC ||
		ELF64_HEADER.e_machine != EM_X86_64 ||
		ELF64_HEADER.e_version != EV_CURRENT
    ) {
        Log(0xFFEF4444, "Kernel format is bad!\n");
    } else {
        Log(0xFF22C55E, "Kernel header successfully verified\n");
    }

    Status = uefi_call_wrapper(
        Kernel->SetPosition,
        2,
        Kernel,
        ELF64_HEADER.e_phoff
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    UINTN HSize = ELF64_HEADER.e_phnum * ELF64_HEADER.e_phentsize;
    
    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        HSize,
        (VOID **)&ELF64_PHEADER
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    Status = uefi_call_wrapper(
        Kernel->Read,
        3,
        Kernel,
        &HSize,
        ELF64_PHEADER
    );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    for(Elf64_Phdr* phdr = ELF64_PHEADER; (char*)phdr + ELF64_HEADER.e_phnum * ELF64_HEADER.e_phentsize; phdr = (Elf64_Phdr*)((char*)phdr + ELF64_HEADER.e_phentsize)) {
        switch (phdr->p_type) {
            case 1:
            {
                int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
                Elf64_Addr segment = phdr->p_paddr;
                Status = uefi_call_wrapper(
                    BS->AllocatePages,
                    4,
                    AllocateAddress,
                    EfiLoaderData,
                    pages,
                    &segment
                );
                if(EFI_ERROR(Status)) {
                    return Status;
                }
                Status = uefi_call_wrapper(
                    Kernel->SetPosition,
                    2,
                    Kernel,
                    phdr->p_offset
                );
                if(EFI_ERROR(Status)) {
                    return Status;
                }

                UINTN PSize = phdr->p_filesz;
                Status = uefi_call_wrapper(
                    Kernel->Read,
                    3,
                    Kernel,
                    &PSize,
                    (VOID*)segment
                );
                if(EFI_ERROR(Status)) {
                    return Status;
                }

                break;
            }
        }
    }

    int (*KernelStart)() = ((__attribute__((sysv_abi)) int (*)() ) ELF64_HEADER.e_entry);

    Print(L"%d\n", KernelStart());

    return EFI_SUCCESS;
}