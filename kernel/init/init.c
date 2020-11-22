#include "console.h"

void main(void)
{
    cons_init();
    /* 打印帮助信息 */
    const char *message = "ucore os is loading ...";
    cprintf("%s\n\n", message);
    
    /* 错误退出 */
    while (1);
}