#ifndef FORK_H
#define FORK_H

#include <iostream>
#include <unistd.h>
#include <malloc.h>
#include <cstring>

const static int MEM_WRITE_SIZE = 10000000; // 10MB

void fork_bomb();

#endif