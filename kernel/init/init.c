#include "console.h"

void kernel_init(void)
{
    cons_init();
        
    /* 错误退出 */
    while (1);
}