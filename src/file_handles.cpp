#include "file_handles.h"

void many_open_file_handles() {
    std::string temp_file_name = std::tmpnam(nullptr);
    std::vector<std::FILE*> file_handles;

    for (;;) {
        errno = 0; // reset this
        FILE* fp = fopen(temp_file_name.c_str(), "w");
        if (fp==NULL) {
            std::cout << "Failed to open handle to " << temp_file_name << " on iteration #" << file_handles.size() << std::endl; 
            std::cout << "Reason: " << std::strerror(errno) << " (" << errno << ")" << std::endl;
            break;
        }
        file_handles.push_back(fp);
    }

    std::cout << std::endl;
    std::cout << "Would you like to close the open file handles now? [Y/n]: ";

    char cont = 0;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(cont);

    if (cont != 'n' && cont != 'N') {
        std::cout << "Closing #" << file_handles.size() << " file handles" << std::endl;

        for (FILE* fh : file_handles) { 
            fclose(fh);
        }
    } else {
        std::cout << "Leaving #" << file_handles.size() << " file handles dangling on exit" << std::endl;
    }


}