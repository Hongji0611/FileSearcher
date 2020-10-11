#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include "Flags.h"
using namespace std;

#define ERR_SEARCH_NOT_DEFINED -1 
#define ERR_INVALID_SEARCH_DIRECTORY -2
#define ERR_INVALID_ARGUMENT -3
#define ERR_INVALID_OUTPUT_DIRECTORY -4

#define WARN_DEFAULT_TYPE_DETECTED 1
#define WARN_DEFAULT_VERBOSE_DETECTED 2
#define WARN_DEFAULT_SOUT_DETECTED 3
#define WARN_DEFAULT_SEARCHDIR_DETECTED 4

#define HELP -100

using namespace std;

class Parser {
public:
    Flags* global_settings;
    Parser(Flags* global_data, int argc, char **argv);
    void print_err(int err_num);
    void parse_each_elements(string args);
    void split(string key, string value);
    bool check_datapath(string value);
    void help(){
        cout <<"HELP: $ program_name --to_find=”some_strings..” --directory=”to_search” --type=”grep|file_name|directory_name” --save_output=”to_save_directory” --file_verbose=”true|false”\n"<<endl;
        cout<<"--directory=”to_search”    Search basis directory recognized by strings, can be absolute directory or relative directory. If this isn’t defined, program will set directory value to program-called directory as default.\n"<<endl;
        cout<<"--to_find=”some_strings”    Things to search, could be any strings including ‘?’, ‘*’ wildcards. If this isn’t defined, program will throw error and exit.\n"<<endl;
        cout<<"--type=”grep|file_name|directory_name”    The search type. Grep will search every file containing specific string[which is defined on --to_find]. If this value isn’t defined, program will set type to file_name as default.\n"<<endl;
        cout<<"--save_output=”to_save_directory”    The file path to redirect STDOUT, can be absolute/relative path. If this isn’t defined, program will not redirect output to file.\n"<<endl;
        cout<<"--file_verbose=”true|false”    Whether to see output as verbose output, only accepting “true” or “false”. If this isn’t defined, program will set --file_verbose to false as default.\n"<<endl;
        cout<<"eg. $ among_file --to_find=”what” --directory=”/” --type=”grep” --save_output=”/Users/kangdroid/otp.txt” --file_verbose=”false"<<endl;
    }
};