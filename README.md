# Dijkstra_RATP
Dijkstra Algorithm for parisian underground lines app in C++

## PROJECT Advanced C++  : RATP App 
#### M1 - Smart System Engineering
##### Sorbonne Université
###### April 2023





## Author

- Emir TAS



## Compilation flags

The command for compilation was following the indicated guidelines (use of flags...)

Also the environment used in this project was Visual Studio Code.

```bash
g++ -std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors -O3 My_station_parser.cpp main.cpp -o main.exe
```



## PART 1 
#### __'Grade' problem__

When compiling including the 'object' file Grade 2019:


```bash
g++ -std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors -O3 My_station_parser.cpp main.cpp "Grade 2019 clang-1001.0.46.3 MACOSX.o" -o main.exe
```
There is a problem that arises that cannot be solved :
```bash
(base) emir@MacBook-Air-de-Emir Resources-20230329 % g++ -std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors -O3 My_station_parser.cpp main.cpp "Grade 2019 clang-1001.0.46.3 MACOSX.o" -o main.exe

ld: warning: ignoring file Grade 2019 clang-1001.0.46.3 MACOSX.o, building for macOS-arm64 but attempting to link with file built for unknown-x86_64
Undefined symbols for architecture arm64:
  "travel::Grade::stations(travel::Generic_station_parser const&)", referenced from:
      _main in main-6ac6bb.o
  "travel::Grade::Grade(bool)", referenced from:
      __GLOBAL__sub_I_main.cpp in main-6ac6bb.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

```


## Inside the folder : 

- **Project report -> TAS_Emir_C++_report.pdf**

- Generic_station_parser.hpp -> already in the project
- Generic_connection_parser.hpp -> already in the project
- Generic_mapper.hpp -> already in the project
- **My_station_parser.hpp -> this is the header of my own file**
- **My_station_parser.cpp -> this is the source code where all the methods are implemented**
- **main.cpp -> main file where the tests are done**

- *Grade.hpp -> not used*


