#include <iostream>
#include <string>

#include "cpu.h"
#include "fork.h"
#include "memory.h"
#include "file_handles.h"

using namespace std;

const int PROC_SUCCESS = 0;
const int PROC_OTHER_ERROR = 1;

static const std::string VERSION("0.1.0");

enum Mode {
    memory,
    fork_proc,
    thread_bomb,
    file_handles,
    cpu,
    help,
    version,
    unknown
};

void show_version() {
    cout << "dr-doom version " << VERSION << endl;
}

void usage() {
    cout << "dr-doom." << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "  " << "dr-doom memory-cannon" << endl;
    cout << "  " << "dr-doom fork-bomb" << endl;
    cout << "  " << "dr-doom halt-catch-fire" << endl;
    cout << "  " << "dr-doom too-many-file-handles" << endl;
    cout << "  " << "dr-doom thread-bomb" << endl;
    cout << "  " << "dr-doom -h | --help" << endl;
    cout << "  " << "dr-doom -v | --version" << endl << endl;
    cout << "Options:" << endl;
    cout << "  " << "-h --help" << "\t" << "Show this screen." << endl;
    cout << "  " << "-v --version" << "\t" << "Display the version of dr-doom." << endl;
}

Mode get_mode(string& str) {
    if (str == "-h" || str == "--help") {
        return help;
    }

    if (str == "-v" || str == "--version") {
        return version;
    }

    if (str == "memory-cannon") {
        return memory;
    }

    if (str == "fork-bomb") {
        return fork_proc;
    }

    if (str == "halt-catch-fire") {
        return cpu;
    }

    if (str == "too-many-file-handles") {
        return file_handles;
    }

    if (str == "thread-bomb") {
        return thread_bomb;
    }

    return unknown;
}

bool are_you_sure(const string& prompt) {
    cout << prompt << endl;
    cout << endl;
    cout << "Are you sure? [y/N]: ";

    char ret = 0;
    cin.get(ret);

    return ret == 'y' || ret == 'Y';
}

int main(int argc, char **argv) {

    if (argc != 2) {
        usage();
        return PROC_OTHER_ERROR;
    }

    string method(argv[1]);

    switch (get_mode(method)) {
        case memory: 
            if (are_you_sure("This process will consume as much memory as it possibly can. This may make your system unstable!")) {
                cout << endl << "Understood. Memory cannon mode activating!" << endl << endl;
                consume_memory();
            }
            break;
        case fork_proc:
            if (are_you_sure("This process will spawn as many processes as it can. These processes will spawn processes and so on. This is going to be difficult to clean up!")) {
                cout << "Understood. Fork-bomb mode activating." << endl << endl;
                fork_bomb();
            }
            break;
        case cpu:
            if (are_you_sure("This process will create a thread that runs an infinite loop for each core. Killing this process should restore normal behaviour.")) {
                cout << endl << "Understood. Halt and catch fire mode activating." << endl << endl;
                consume_cpu();
            }
            break;
        case thread_bomb:
            cout << "Not implemented" << endl;
            break;
        case file_handles:
            if (are_you_sure("This process will open a temp file for writing using as many file handles as possible.")) {
                cout << endl << "Understood. Opening file over and over again." << endl << endl;
                many_open_file_handles();
            }
            break;
        case version:
            show_version();
            break;
        case help:
        case unknown: 
        default: 
            usage();
            break;
    }

    return 0;    
}