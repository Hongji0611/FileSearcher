#include "FileSearch.h"

FileSearch::FileSearch(Flags* flags)
    :flags(flags)
{
}

string FileSearch::type_string(filesystem::file_type type_file) {
    string return_value = "";
    if (type_file == filesystem::file_type::not_found) {
        return_value = "Not Found";
    } else if (type_file == filesystem::file_type::none) {
        return_value = "None";
    } else if (type_file == filesystem::file_type::regular) {
        return_value = "Regular";
    } else if (type_file == filesystem::file_type::directory) {
        return_value = "Directory";
    } else if (type_file == filesystem::file_type::symlink) {
        return_value = "Symlink";
    } else if (type_file == filesystem::file_type::block) {
        return_value = "Block";
    } else if (type_file == filesystem::file_type::character) {
        return_value = "Character";
    } else if (type_file == filesystem::file_type::fifo) {
        return_value = "FIFO";
    } else if (type_file == filesystem::file_type::socket) {
        return_value = "System Socket";
    } else if (type_file == filesystem::file_type::unknown) {
        return_value = "Unknown";
    }

    return return_value;
}

string FileSearch::convert_lwt(filesystem::path t) {
    auto ftime = filesystem::last_write_time(t);
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__linux__) || defined(__unix__)
    auto converted = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    time_t tmp_converting = std::chrono::system_clock::to_time_t(converted);
    struct tm* dt;
    char buffer[50];
    dt = localtime(&tmp_converting);
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", dt);
    return string(buffer);
#else
    std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
    return string(std::asctime(std::localtime(&cftime)));
#endif
}

string FileSearch::convert_perm(filesystem::perms p) {
    string ret_val = "";
    ret_val += ((p & filesystem::perms::owner_read) != filesystem::perms::none ? "r" : "-");
    ret_val += ((p & filesystem::perms::owner_write) != filesystem::perms::none ? "w" : "-");
    ret_val += ((p & filesystem::perms::owner_exec) != filesystem::perms::none ? "x" : "-");
    ret_val += ((p & filesystem::perms::group_read) != filesystem::perms::none ? "r" : "-");
    ret_val += ((p & filesystem::perms::group_write) != filesystem::perms::none ? "w" : "-");
    ret_val += ((p & filesystem::perms::group_exec) != filesystem::perms::none ? "x" : "-");
    ret_val += ((p & filesystem::perms::others_read) != filesystem::perms::none ? "r" : "-");
    ret_val += ((p & filesystem::perms::others_write) != filesystem::perms::none ? "w" : "-");
    ret_val += ((p & filesystem::perms::others_exec) != filesystem::perms::none ? "x" : "-");
    return ret_val;
}

int FileSearch::file_name(){
    vector<filesystem::directory_entry> path_container;
    /**
     * Use Auto && Follow latest CPP reference 
     * Also, push FULL ABSOLUTE path to vector
     */
    for (auto& iterator : filesystem::recursive_directory_iterator(flags->directory_path, filesystem::directory_options(std::filesystem::directory_options::skip_permission_denied))) {
        try {
            if(filesystem::is_regular_file(iterator.path())){
                path_container.push_back(iterator);
            }
        } catch(filesystem::filesystem_error what_err) {
            cout << iterator.path().string() << ": " << what_err.what() << endl;
        }  
    }

    // regex search
    regex re(flags->target_find);
    
    string output="";
    for(auto& iterator: path_container){
        if(regex_match(string(iterator.path().filename().string()), re)){
            if(!(flags->file_verbose)) {
                output += "File: "+ string(iterator.path().filename().string()) +"\tPath: " + string(iterator.path().string()) +"\n";
            } else {
                output += string(iterator.path().filename().string()) + "\t" +  string(iterator.path().string()) + "\t" + to_string(filesystem::file_size(iterator)) + "\t" 
                + type_string(filesystem::status(iterator.path()).type()) + "\t" + convert_perm(filesystem::status(iterator.path()).permissions()) + "\t" + convert_lwt(iterator.path()) + "\n";
            }
            
        }
    }
    cout << output << endl; 
    if(!(flags->save_path == "false")) save_output(output);
    return 0;
}

int FileSearch::directory_name(){
    vector<filesystem::directory_entry> path_container;
    /**
     * Use Auto && Follow latest CPP reference 
     * Also, push FULL ABSOLUTE path to vector
     */
    for (auto& iterator : filesystem::recursive_directory_iterator(flags->directory_path), filesystem::directory_options(std::filesystem::directory_options::skip_permission_denied)) {
         try {
            if(filesystem::is_directory(iterator.path())){
                path_container.push_back(iterator);
            }
        } catch(filesystem::filesystem_error what_err) {
            cout << iterator.path().string() << ": " << what_err.what() << endl;
        } 
    }
    // regex search
    regex re(flags->target_find);
    
    string output="";
    for(auto& iterator: path_container){
        if(regex_match(string(iterator.path().filename().string()), re)){
            if(!(flags->file_verbose)) {
                output += "File: "+ string(iterator.path().filename().string()) +"\tPath: " + string(iterator.path().string()) +"\n";
            } else {
                output += string(iterator.path().filename().string()) + "\t" +  string(iterator.path().string()) + "\t" + to_string(filesystem::file_size(iterator)) + "\t" 
                + type_string(filesystem::status(iterator.path()).type()) + "\t" + convert_perm(filesystem::status(iterator.path()).permissions()) + "\t" + convert_lwt(iterator.path());
            }
            
        }
    }
    cout << output << endl; 
    if(!(flags->save_path == "false")) save_output(output);
    return 0;
}
    
int FileSearch::grep(){
    vector<filesystem::directory_entry> path_container;

    //regex search
    regex re(flags->target_find);
    string target = flags->target_find;
    
    for (auto& iterator : filesystem::recursive_directory_iterator(flags->directory_path), filesystem::directory_options(std::filesystem::directory_options::skip_permission_denied)) {
        try {
            if(filesystem::is_regular_file(iterator.path())){
                ifstream readFile;
                readFile.open(iterator.path(), std::fstream::in | std::fstream::binary);
                if (readFile.is_open()) {
                    //get length of file
                    readFile.seekg(0, readFile.end);
                    int length = readFile.tellg();
                    readFile.seekg(0, readFile.beg);

                    char* buffer = new char[length];

                    //read data as a block
                    readFile.read(buffer, length);

                    if(regex_search(buffer, re)){   //find
                        path_container.push_back(iterator);
                    }

                    readFile.close();
                    delete[] buffer;
                }
            }
        } catch (filesystem::filesystem_error ec) {
            cout << iterator.path().string() << ": " << ec.what() << endl; 
        }
    }
    string output="";
    for(auto& iterator: path_container){
        if(!(flags->file_verbose)) {
            output += "File: "+ string(iterator.path().filename().string()) +"\tPath: " + string(iterator.path().string()) +"\n";
        } else {
            output += string(iterator.path().filename().string()) + "\t" +  string(iterator.path().string()) + "\t" + to_string(filesystem::file_size(iterator)) + "\t" 
            + type_string(filesystem::status(iterator.path()).type()) + "\t" + convert_perm(filesystem::status(iterator.path()).permissions()) + "\t" + convert_lwt(iterator.path());
        }
    }
    cout << output << endl; 
    if(!(flags->save_path == "false")) save_output(output);
    return 0;
}

int FileSearch::save_output(string& output){
    ofstream out;
    out.open(flags->save_path);
    out << output << endl;
    cout<< "Successfully saved output to: "<< flags->save_path <<endl;
    out.close();
    
    return 0;
}
