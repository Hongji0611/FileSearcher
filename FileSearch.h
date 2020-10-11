#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <chrono>
#include <iomanip>

#include "Flags.h"

using namespace std;
using namespace std::chrono_literals;

class FileSearch{
private:
    Flags* flags;
public:
    FileSearch(Flags* flags);
    
    int file_name();
    int directory_name();
    int grep();

    int save_output(string& output);
    string type_string(filesystem::file_type);
    string convert_lwt(filesystem::path t);
    string convert_perm(filesystem::perms p);
    string get_directory_size(filesystem::path t);
};
