CC =gcc
LD =ld

BOOTLOADER_SOURCE_FILES := $(shell find Sources -name *.c)
BOOTLOADER_OBJECT_FILES := $(patsubst Sources/%.c, Build/%.o, $(BOOTLOADER_SOURCE_FILES))

EFI_CFLAGS=-fno-stack-protector -fpic -fshort-wchar -mno-red-zone -I gnu-efi/inc/ -I Includes/ -DEFI_FUNCTION_WRAPPER
EFI_LDFLAGS=gnu-efi/x86_64/crt0-efi-x86_64.o -nostdlib -znocombreloc -T gnu-efi/x86_64/elf_x86_64_efi.lds -shared -Bsymbolic -L gnu-efi/x86_64/ -l:libgnuefi.a -l:libefi.a -z noexecstack

$(BOOTLOADER_OBJECT_FILES): Build/%.o : Sources/%.c
	mkdir -p $(dir $@) && \
	$(CC) $(EFI_CFLAGS) -c $(patsubst Build/%.o, Sources/%.c, $@) -o $@

.PHONY: efi
efi: $(BOOTLOADER_OBJECT_FILES)
	$(LD) $(BOOTLOADER_OBJECT_FILES) $(EFI_LDFLAGS) -o Build/bootx64.so && \
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc --target=efi-app-x86_64 Build/bootx64.so Image/bootx64.efi && \
	uefi-run -s 256 -f Image/kernel64.elf -f Image/font18.psf -f Image/littleboot.cfg -f Image/test.bmp -f Image/background.bmp -d Image/bootx64.efi -- -m 512 -rtc base=localtime