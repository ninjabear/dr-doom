#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <malloc.h>
#include <vector>
#include <cstring>
#include <thread>
 
const static int ALLOC_SIZE = 4096;

void mt_consume_memory();
void consume_memory();

#endif