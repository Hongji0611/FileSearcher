#include <iostream>
#include <filesystem>
#include <regex>
#include "Parser.h"
#include "Flags.h"
#include "FileSearch.h"

using namespace std;

// * --> .*
// ? --> .
// "." --> \\. --> 레겍스의 메타 문자가 파일 이름에 포함되있을 경우, \\ 붙여서 리터럴로 만들기!

/*
 * 0. Flag 저장할 수 있는 공유 클래스 1개 (미승)
 * 1. 에러 넘버 저장하고 있는 ENUM 1개 (미승)
 * 2. 인자 분류 클래스 1 (1) - 강현우
 * 3. Search Class - File Search (2) (건령,지우), Wildcard Helper (2) (지은)
 */

int main(int argc, char**argv) {
    Flags search_flags;
    Parser args_parser(&search_flags, argc, argv);
    FileSearch tmp_fs(&search_flags);
    //tmp_fs.file_name();

    if(search_flags.type=="grep"){
        tmp_fs.grep();
    }else if(search_flags.type=="file_name"){
        tmp_fs.file_name();
    }else if(search_flags.type=="directory_name"){
        tmp_fs.directory_name();
    }

    return 0;
}