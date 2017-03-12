#include "thread.h"

void thread_bomb() { 
    std::condition_variable cv;
    std::mutex m;
    std::vector<std::thread> thread_handles;

    long thread_count = 0; 

    for (;;) {
        thread_count++;
        try { 
            thread_handles.push_back(std::thread(blocked_thread, std::ref(cv), std::ref(m)));
        } catch (const std::exception& e) {
            std::cout << "After creating " << thread_count << " new threads the following error occurred: " << std::endl << std::endl;
            std::cout << e.what() << std::endl << std::endl;
            break;
        } catch (...) {
            std::cout << "After creating " << thread_count << " new threads an unexpected (non std::exception) error occurred." << std::endl << std::endl;
            break;
        }
    }

    std::cout << "The threads are currently running. Would you like to clean up the threads before exiting? [Y/n]: ";

    char cont = 0;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(cont);

    if (cont != 'n' && cont != 'N') {
        std::cout << "Cleaning up threads..." << std::endl;

        cv.notify_all();

        for (long i=0; i<thread_count; i++) {
            try {
                thread_handles[i].join();
            } catch (...) { }
            cv.notify_all();
        }

        std::cout << thread_count << " threads closed. " << std::endl;
    } else {
        std::cout << "Understood, ending the process leaving the operating system to clean up " << thread_count << " detached threads." << std::endl;

        for (long i=0; i<thread_count; i++) {
            try {
                thread_handles[i].detach();
            } catch (...) { }
        }
    }
}

void blocked_thread(std::condition_variable& cv, std::mutex& m) {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock);
    lock.unlock();
}