#pragma once
#include <iostream>

using namespace std;

#define NOT_SPECIFIED "NON_SPECIFIED"

class Flags {
public:
    Flags() {
        this->type = NOT_SPECIFIED;
        this->directory_path = NOT_SPECIFIED;
        this->target_find = NOT_SPECIFIED;
        this->file_verbose = -1;
        this->save_path = NOT_SPECIFIED;
    }
    string type;
    string directory_path;
    string target_find;
    int file_verbose;
    string save_path;
};