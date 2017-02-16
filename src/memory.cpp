#include "memory.h"

void mt_consume_memory() {   
    int max_cores = std::thread::hardware_concurrency();

    std::thread threads[max_cores];

    for (int i=0; i<max_cores; i++) {
        threads[i] = std::thread(consume_memory);
    }

    for (int i=0; i<max_cores; i++) { 
        threads[i].join();
    }
}

void consume_memory() {
   std::thread::id thread_id = std::this_thread::get_id();
   std::vector<void*> mem_ptrs;

   for (;;) {
       void* ptr = malloc(ALLOC_SIZE);
       if (ptr == NULL) {
           // reached peak?
           break;
       }
       
       std::memset(ptr, 0, ALLOC_SIZE);
       mem_ptrs.push_back(ptr);
   } 
   
   std::cout << "thread(" << thread_id << "): allocated " << (((mem_ptrs.size() * ALLOC_SIZE) / 1024.0) / 1024.0) << " MiB total" << std::endl;
   std::cout << "thread(" << thread_id << "): unwinding..." << std::endl;
   
   for (auto & ptr : mem_ptrs) { // we'll probably never get here
       free(ptr);
   }

   std::cout << "thread(" << thread_id << "): done." << std::endl;
}