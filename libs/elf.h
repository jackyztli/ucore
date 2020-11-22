#ifndef LIBS_ELF_H
#define LIBS_EFL_H
#include "stdint.h"

#define ELF_MAGIC 0x464C457FU /* 小端机器魔术字 */

/* 文件头信息 */
struct elfhdr {
    uint32_t e_magic;     /* 魔术字 */
    uint8_t e_elf[12];
    uint16_t e_type;      /* 1=relocatable, 2=executable, 3=shared object, 4=core image */
    uint16_t e_machine;   /* 3=x86, 4=68K, etc. */
    uint32_t e_version;   /* 文件版本，目前总是1 */
    uint32_t e_entry;     /* 可运行文件入口 */
    uint32_t e_phoff;     /* 程序段 */
    uint32_t e_shoff;     /* 节头部 */
    uint32_t e_flags;     /* 架构特殊标识，通常为0 */
    uint16_t e_ehsize;    /* 文件头信息长度 */
    uint16_t e_phentsize; /* 程序段一个实体的大小 */
    uint16_t e_phnum;     /* 程序段实体数量 */
    uint16_t e_shentsize; /* 节段的一个实体长度 */
    uint16_t e_shnum;     /* 节点的实体数量 */
    uint16_t e_shstrndx;  /* 节段中包含的字符串个数 */
};

/* 程序段的信息 */
struct proghdr {
    uint32_t p_type;   /* 程序类型，包括程序，数据，链接等等 */
    uint32_t p_offset; /* 相对于节段的偏移 */
    uint32_t p_va;     /* 节段对应的虚拟地址 */
    uint32_t p_pa;     /* 节段对应的物理地址 */
    uint32_t p_filesz; /* 节段的数量 */
    uint32_t p_memsz;  /* 节段的地址空间 */
    uint32_t p_flags;  
    uint32_t p_align;  /* 节段的对齐 */
};

#endif
