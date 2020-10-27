#include "Parser.h"

Parser::Parser(Flags* global_data, int argc, char **argv) {

    this->global_settings = global_data;

    // No argument specified
    if (argc == 1) {
        help();
        exit(-1);
    }

    // First see if we parsed at all
    for (int i = 1; i < argc; i++) {
        string args = string(argv[i]);
        int find_dest = args.find("=");
        if (find_dest == string::npos) {
            if (args == "--help") {
                help();
                exit(HELP);
            } else {
                // Invalid Arguments
                print_err(ERR_INVALID_ARGUMENT);
                help();
                exit(ERR_INVALID_ARGUMENT);
            }
        }

        string key = args.substr(0, find_dest);
        string value = args.substr(find_dest+1, args.length());
        split(key, value);
    }

    // After parsing once, look for un-reset variable
    if (global_data->directory_path == NOT_SPECIFIED) {
        // Search Directory to default
        global_data->directory_path = filesystem::current_path().string();
        print_err(WARN_DEFAULT_SEARCHDIR_DETECTED);
    }

    if (global_data->file_verbose == -1) {
        // File Verbose NOT set
        global_data->file_verbose = false;
        print_err(WARN_DEFAULT_VERBOSE_DETECTED);
    }

    if (global_data->save_path == NOT_SPECIFIED) {
        global_data->save_path = "false";
        print_err(WARN_DEFAULT_SOUT_DETECTED);
    }

    if (global_data->target_find == NOT_SPECIFIED) {
        // This is error
        print_err(ERR_SEARCH_NOT_DEFINED);
        help();
        exit(ERR_SEARCH_NOT_DEFINED);
    }

    if (global_data->type == NOT_SPECIFIED) {
        global_data->type = "file_name";
        print_err(WARN_DEFAULT_TYPE_DETECTED);
    }
}

void Parser::split(string key, string value) {
    bool is_failed = false;
    int err_number = 0;
    
    if (key == "--directory") {
        filesystem::path path_directory(value);
        if (!filesystem::exists(path_directory)) {
            // Search Directory is invalid
            print_err(ERR_INVALID_SEARCH_DIRECTORY);
            is_failed = true; //just let them fail
            err_number = ERR_INVALID_SEARCH_DIRECTORY;
        } else {
            // need to check value first
            global_settings->directory_path = value;
        }
    } else if (key == "--type") {
        if (value != "grep" && value != "file_name" && value != "directory_name") {
            print_err(ERR_INVALID_ARGUMENT);
            is_failed = true;
            err_number = ERR_INVALID_ARGUMENT;
        } else {
            global_settings->type = value;
        }
    } else if (key == "--to_find") {
        string tmp_use = "";
        // For changing user-input wildcard to program-acceptable state.
        for (int i = 0; i < value.length(); i++) {
            if (value.at(i) == '*') {
                tmp_use.append(".*");
            } else if (value.at(i) == '?') {
                tmp_use.append(".");
            } else if (value.at(i) == '.') {
                tmp_use.append("\\.");
            } else if (value.at(i) == '^') {
                tmp_use.append("\\^");
            } else if (value.at(i) == '$') {
                tmp_use.append("\\$");
            } else if (value.at(i) == '[') {
                tmp_use.append("\\[");
            } else if (value.at(i) == ']') {
                tmp_use.append("\\]");
            } else if (value.at(i) == '-') {
                tmp_use.append("\\-");
            } else if (value.at(i) == '|') {
                tmp_use.append("\\|");
            } else if (value.at(i) == '(') {
                tmp_use.append("\\(");
            } else if (value.at(i) == ')') {
                tmp_use.append("\\)");
            } else if (value.at(i) == '+') {
                tmp_use.append("\\+");
            } else if (value.at(i) == '{') {
                tmp_use.append("\\{");
            } else if (value.at(i) == '}') {
                tmp_use.append("\\}");
            } else {
                tmp_use += value.at(i);
            }
        }
        global_settings->target_find = tmp_use;
    } else if (key == "--file_verbose") {
        if (value != "true" && value != "false") {
            print_err(ERR_INVALID_ARGUMENT);
            is_failed = true;
            err_number = ERR_INVALID_ARGUMENT;
        } else {
            global_settings->file_verbose = (value == "true") ? true:false;
        }
    } else if (key == "--save_output") {
        filesystem::path path_directory(value);
        if (!filesystem::exists(path_directory)) {
            filesystem::path abs_path = filesystem::absolute(path_directory);
            if (!filesystem::exists(abs_path.parent_path())) {
                // Search Directory is invalid
                print_err(ERR_INVALID_OUTPUT_DIRECTORY);
                is_failed = true; //just let them fail
                err_number = ERR_INVALID_OUTPUT_DIRECTORY;
            } else {
                global_settings->save_path = value;
            }
        } else {
            global_settings->save_path = value;
        }
    } else {
        // invalid key
        print_err(ERR_INVALID_ARGUMENT);
        is_failed = true;
        err_number = ERR_INVALID_ARGUMENT;
    }

    if (is_failed) {
        help();
        exit(err_number);
    } else {
        return;
    }
}


#define ECODE_ARG_INVALID -1


void Parser::print_err(int err_num){
    
    switch(err_num){
        case -1:
            cout<<"[ERROR] Target Search string is not specified."<<endl;
            break;
        case -2:
            cout<<"[ERROR] Current target search directory is invalid." <<endl;
            break;
        case -3:
            cout<<"[ERROR] Argument not specified [Invalid arguments]." <<endl;
            break;
        case -4:
            cout<<"[ERROR] Text output directory is invalid." <<endl;
            break;
        case 1:
            cout<<"[WARN] type is not specified. --type is set to file_name."<<endl;
            break;
        case 2:
            cout<<"[WARN] file_verbose is not specified. --file_verbose is set to false."<<endl;
            break;
        case 3:
            cout<<"[WARN] save_output is not specified. --save_output is set to false."<<endl;
            break;
        case 4:
            cout<<"[WARN] --directory is not specified. --directory is set to current directory."<<endl;
            break;
        default:
            cout<<"not defined errr_num"<<endl;
            break;
    
    }
    
}