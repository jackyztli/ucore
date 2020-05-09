//#include <stdlib.h>
#include <stdint.h>

// 内核起始地址
#define SYSSEG 0x10000
// 扇区大小
#define SECTSIZE 512

/*
 * 功能描述：从I/O端口读取一个字节
 */
static inline uint8_t inb(uint16_t port)
{
    uint8_t data;
    asm volatile("inb %1, %0" : "=a"(data) : "d"(port));
    return data;
}

static inline void outb(uint16_t port, uint8_t data)
{
    asm volatile ("outb %0, %1" :: "a" (data), "d" (port));
}

static inline void insl(uint32_t port, void *addr, int cnt)
{
    asm volatile (
        "cld;"
        "repne; insl;"
        : "=D" (addr), "=c" (cnt)
        : "d" (port), "0" (addr), "1" (cnt)
        : "memory", "cc");
}

/*
 * 功能描述：将单个扇区读入到buff处
 */
static void readSect(void *buff, uint32_t sectno)
{
    /* 等待磁盘可读 */
    while ((inb(0x1F7) & 0xC0) != 0x40) {}
    
    outb(0x1F2, 1); 
    outb(0x1F3, sectno & 0xFF);
    outb(0x1F4, (sectno >> 8) & 0xFF);
    outb(0x1F5, (sectno >> 16) & 0xFF);
    outb(0x1F6, ((sectno >> 24) & 0xF) | 0xE0);
    outb(0x1F7, 0x20);

    /* 等待磁盘可读 */
    while ((inb(0x1F7) & 0xC0) != 0x40) {}

    /* 从磁盘读取一个扇区 */
    insl(0x1F0, buff, SECTSIZE / 4);  
}

/*
 * 功能描述：从磁盘1扇区（内核开始处）的offset处读取
 *           count大小的内容到内存
 */
static void readSeg(uintptr_t va, uint32_t count, uint32_t offset)
{
    uintptr_t end_va = va + count;
    // offset对应的开始扇区
    uint32_t sectno = (offset / SECTSIZE) + 1;

    while (va < end_va) {
        readSect((void *)va, sectno);
        va += SECTSIZE;
        sectno++;
    }
}

int bootmain()
{
    // 从第一个扇区读入内核
    readSeg((uintptr_t)SYSSEG, SECTSIZE * 8, 0);
    
    // 调用内核的启动函数
    
    return 1;
}
