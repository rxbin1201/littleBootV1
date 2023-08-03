/*

    littleBootV1 - 02.08.23 
    elf.h

*/

#ifndef __ELF_H
#define __ELF_H

typedef unsigned long long size_t;

/* Type of addresses.  */
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

/* Conglomeration of the identification bytes, for easy testing as a word.  */
#define	ELFMAG		"\177ELF"
#define	SELFMAG		4

#define EV_CURRENT	1		/* Current version */

// Basic ELF file types (e_type)
static const uint16_t ET_NONE = 0;
static const uint16_t ET_REL = 1;
static const uint16_t ET_EXEC = 2;
static const uint16_t ET_DYN = 3;
static const uint16_t ET_CORE = 4;

// Indexes of various parts inside e_ident
static const size_t EI_MAG0 = 0;
static const size_t EI_MAG1 = 1;
static const size_t EI_MAG2 = 2;
static const size_t EI_MAG3 = 3;
static const size_t EI_CLASS = 4;
static const size_t EI_DATA = 5;
static const size_t EI_VERSION = 6;
static const size_t EI_OSABI = 7;
static const size_t EI_ABIVERSION = 8;
static const size_t EI_PAD = 9;

// A few of the defined machine types (e_machine)
static const uint16_t EM_X86_64 = 62;
static const uint16_t EM_AARCH64 = 183;

// Possible values of e_ident[EI_CLASS]
static const unsigned char ELFCLASSNONE = 0;
static const unsigned char ELFCLASS32 = 1;
static const unsigned char ELFCLASS64 = 2;

// Possible values of e_ident[EI_DATA]
static const unsigned char ELFDATANONE = 0;
static const unsigned char ELFDATA2LSB = 1;
static const unsigned char ELFDATA2MSB = 2;

// A few of the defined program header types (e_type)
static const uint32_t PT_NULL = 0;
static const uint32_t PT_LOAD = 1;
static const uint32_t PT_DYNAMIC = 2;
static const uint32_t PT_INTERP = 3;
static const uint32_t PT_NOTE = 4;
static const uint32_t PT_SHLIB = 5;
static const uint32_t PT_PHDR = 6;
static const uint32_t PT_TLS = 7;

// Segment premissions (e_flags)
static const uint32_t PF_X = 1;
static const uint32_t PF_W = 2;
static const uint32_t PF_R = 4;

typedef struct {
    uint8_t  e_ident[16];   /* Magic number and other info */
    uint16_t e_type;        /* Object file type */
    uint16_t e_machine;     /* Architecture */
    uint32_t e_version;     /* Object file version */
    uint64_t e_entry;       /* Entry point virtual address */
    uint64_t e_phoff;       /* Program header table file offset */
    uint64_t e_shoff;       /* Section header table file offset */
    uint32_t e_flags;       /* Processor-specific flags */
    uint16_t e_ehsize;      /* ELF header size in bytes */
    uint16_t e_phentsize;   /* Program header table entry size */
    uint16_t e_phnum;       /* Program header table entry count */
    uint16_t e_shentsize;   /* Section header table entry size */
    uint16_t e_shnum;       /* Section header table entry count */
    uint16_t e_shstrndx;    /* Section header string table index */
} Elf64_Ehdr;

typedef struct {
    uint32_t p_type;        /* Segment type */
    uint32_t p_flags;       /* Segment flags */
    uint64_t p_offset;      /* Segment file offset */
    uint64_t p_vaddr;       /* Segment virtual address */
    uint64_t p_paddr;       /* Segment physical address */
    uint64_t p_filesz;      /* Segment size in file */
    uint64_t p_memsz;       /* Segment size in memory */
    uint64_t p_align;       /* Segment alignment */
} Elf64_Phdr;

#endif // End of file