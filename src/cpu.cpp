#include "cpu.h"

void consume_cpu() {
    int max_cores = std::thread::hardware_concurrency();

    std::thread threads[max_cores];

    for (int i=0; i<max_cores; i++) {
        threads[i] = std::thread(consume_thread);
    }

    for (int i=0; i<max_cores; i++) { // this will never complete
        threads[i].join();
    }
}

void consume_thread() {
    bool flip = false;
    for (;;) {
        flip = !flip; // ensure it doesn't get optimized away
    }
}