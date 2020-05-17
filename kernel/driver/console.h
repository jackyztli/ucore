#ifndef KERNEL_DRIVER_CONSOLE_H
#define KERNEL_DRIVER_CONSOLE_H

void cons_init(void);
void cons_putc(int c);
int cons_getc(void);
void serial_intr(void);
void kbd_intr(void);

#endif

