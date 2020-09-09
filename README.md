Demos for FILE-Searcher Project.
=================================

To use
-------
```
$ program.out[or program.exe] "file_to_find" "directory_to_search"
```

For Example,
```
$ ./a.out "find_file.cpp" "/Users/KangDroid/Desktop"
```

Arguments
----------
1st Arguments: file name to find[찾을 파일의 이름]
2nd Arguments: search base directory[어디 폴더에서 찾을 것인가?]

Outputs
-------
- 먼저 인자로 들어온 디렉터리의 파일/폴더들을 리스트로 보여줌[단, 절대경로로]
- 위와 같은 출력을 내지만, 상대경로로 출력함
- 실제 인자로 들어온 폴더 내에, 인자로 들어온 타겟[파일 이름]이 존재 하는지 확인 후 출력[Non Case Sensitive]

Real example
-------------
현재 아래 사진처럼 데스크탑에 이러한 파일들이 있고, find_file.cpp를 "/Users/kangdroid/Desktop" 안에서 찾고 싶을 때,
![](https://i.imgur.com/7XBRM9A.png)


다음과 같은 명령어를 쓰고,
```
$ ./a.out "find_file.cpp" "/Users/KangDroid/Desktop"
```

다음과 같은 OUTPUT을 산출함
![](https://i.imgur.com/Kj6u1st.png)
