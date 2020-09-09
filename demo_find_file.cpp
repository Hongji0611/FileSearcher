/**
 * DEMO for Finding file using FULL String Match.
 * Copyright (C) 2020 KangDroid, aka Jason. HW. Kang
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

/**
 * argc: Count of Args are stored
 * argv: "C-String List"
 * 
 * First of argument is "Execution name"
 */
int main(int argc, char** argv) {
    vector<string> path_container;
    if (argc < 2) {
        // There is no file name || target find directory from argument.
        return -1;
    }

    // C-String to CPP-String[File Name]
    string file_name = string(argv[1]);
    string target_directory = string(argv[2]);

    /**
     * Use Auto && Follow latest CPP reference
     * Also, push FULL ABSOLUTE path to vector
     */
    for (auto& iterator : filesystem::directory_iterator(target_directory)) {
        path_container.push_back(string(iterator.path()));
    }

    /**
     * Print Absolute Directores
     * either for (int i = 0; i < path_container.size(); i++) ...
     */
    cout << "Full Path" << endl;
    for (string iterator : path_container) {
        cout << iterator << endl;
    }
    cout << endl;

    /**
     * Print Relative Path
     */
    cout << "Relative Path(Subsituting Absolute Path)" << endl;
    for (string string_manip : path_container) {
        // The "Real file name", subsituting absolute path
        string file_name_found = string_manip.substr(target_directory.length()+1, (string_manip.length() - target_directory.length()));
        cout << file_name_found << endl;
    }
    cout << endl;

    /**
     * Find File Name[Full String Match] and print absolute/relatie path
     */
    for (string to_work : path_container) {
        string file_name_found = to_work.substr(target_directory.length()+1, (to_work.length() - target_directory.length()));
        if (file_name_found == file_name) {
            cout << "Found File, matching: " << file_name << endl;
            cout << "Absolute path: " << to_work << endl;
            cout << "Relative path: " << file_name_found << endl;
        }
    }
    return 0;
}
