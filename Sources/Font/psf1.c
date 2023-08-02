/*

    littleBootV1 - 02.08.23 
    psf1.c

*/

// Import libraries
#include <Font/psf1.h>

PSF1_FONT* LoadPsf1Font(CHAR16 *File) {

    // Declare variables
    EFI_STATUS Status;
    EFI_FILE *FontFile = LoadFile(NULL, File);
    PSF1_HEADER *FontHeader;
    PSF1_FONT *FinalFont;
    UINTN FontSize;
    UINTN GlyphBufferSize;

    if(FontFile == NULL) return NULL;

    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        sizeof(PSF1_HEADER),
        (VOID **)&FontHeader
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    FontSize = sizeof(PSF1_HEADER);
    Status = uefi_call_wrapper(
        FontFile->Read,
        3,
        FontFile,
        &FontSize,
        FontHeader
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    if(FontHeader->Magic[0] != PSF1_MAGIC0 || FontHeader->Magic[1] != PSF1_MAGIC1) {
        return NULL;
    }

    GlyphBufferSize = FontHeader->CharSize * 512;

    VOID *GlyphBuffer; {
        Status = uefi_call_wrapper(
            FontFile->SetPosition,
            2,
            FontFile,
            sizeof(PSF1_HEADER)
        );
        if(EFI_ERROR(Status)) {
            return NULL;
        }
        Status = uefi_call_wrapper(
            BS->AllocatePool,
            3,
            EfiLoaderData,
            GlyphBufferSize,
            (VOID **)&GlyphBuffer
        );
        if(EFI_ERROR(Status)) {
            return NULL;
        }
        Status = uefi_call_wrapper(
            FontFile->Read,
            3,
            FontFile,
            &GlyphBufferSize,
            GlyphBuffer
        );
        if(EFI_ERROR(Status)) {
            return NULL;
        }
    }

    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        sizeof(PSF1_FONT),
        (VOID **)&FinalFont
    );
    if(EFI_ERROR(Status)) {
        return NULL;
    }

    FinalFont->Psf1Header = FontHeader;
    FinalFont->GlyphBuffer = GlyphBuffer;

    return FinalFont;
} // End of file