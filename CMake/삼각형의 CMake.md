<script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.7.0/languages/cmake.min.js"></script>

## CMake 기본 폴더 구조
- CMake는 Make로부터 발전되었기 때문에 일반적으로 GNU 폴더 구조를 따름.
- .
  - bin // 동적 라이브러리와 실행 파일
  - data // 데이터와 에셋(DB, 그림 파일 등)
  - demo // 데모 파일
  - doc // 문서
  - include // 헤더 파일(Public 헤더 파일 등)
  - lib // 라이브러리
  - src // 소스 파일
  - test // 테스트


### 예제

#### 폴더 구조
- .
  - CMakeLists.txt
  - src
    - main.cpp
```C++
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello CMake" << std::endl;
    return EXIT_SUCCESS;
}
```      

```cmake
# 최소 CMake 버전 요구사항 명시
# 명시한 버전보다 낮을 경우 에러 출력
cmake_minimum_required(VERSION 3.0.0)

# 프로젝트 이름 지정
project(hello-cmake)

# 타겟 프로그램 정의
add_executable(hell_cmake src/main.cpp)

# 조건문
if (BUILD_TESTING)
    # 메시지 출력
    message("Hello Test")
endif()
```


### CMake 단계
- CMake는 빌드에 필요한 파일을 생성하기 위해 2단계를 수행
  - Configure, Generate
  - **Configuring done**과 **Generating done** 이 출력되는지 반드시 확인
- Condigure
  - CMakeLists.txt를 분석하고 이를 토대로 CMakeCache.txt를 생성
  - CMakeCache.txt
    - 캐시는 <이름>:<타입>=[값]의 형식
    - CMake에서 필요한 데이터를 저장
    - CMake를 사용하면서 발생하는 모든 문제의 근원
- Generate
  - Configure단계에서 생성된 파일들을 사용해서 Native Build System 파일을 생성
    - Visual Studio, Xcode, Ninja, Make처럼 빌드를 하기 위해 필요한 파일들을 생성
    - CMakeCache.txt에 정의된 변수를 사용하기 때문에 CMakeCache.txt가 갱신되지 않는다면 원치 않는 Native Build System 파일이 생성될 수 있음
- 간단한 해결 방법
  - --fresh 옵션
    - CMakeCache.txt를 지우고 다시 생성
  - 생성된 CMakeCache.txt를 직접 지우는 방법

### 커맨드 형식
#### 커맨드_이름(공백으로 구분된 문자열)
- 다양한 기본 커맨드를 제공하며, 개발자가 필요한 커맨드를 직접 정의할 수 있음
- 대표적인 커맨드
  - [cmake_minimum_required(VERSION \<min>)](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html)
    - 예시
      - cmake_minimum_required(VERSION 3.0.0)
    - 필요한 CMake의 버전을 명시
    - 사용자에게 특정 버전 이상의 CMake 버전 사용을 강제함으로써 호환성과 안정성 유지
  - [project(<project-name> [VERSION \<major>[.\<minor>[.\<patch>[.\<tweak>]]]   
  [LANGUAGES \<language-name> ...]])](https://cmake.org/cmake/help/latest/command/project.html)
    - 예시
      - proejct(Hello-cmake VESION 0.0.1 LANGUAGES C CXX)
    - 프로젝트의 이름, 버전, 사용하는 언어를 명시
    - 버전은 프로젝트의 릴리즈 버전을 식별하는데 사용
    - 언어는 CMake가 프로젝트를 빌드할 때 사용할 컴파일러를 결정하는 데 사용
  - [message([\<mode>] "text" ...)](https://cmake.org/cmake/help/latest/command/message.html)
    - 예시
      - message("Hello CMake!")
      - message(STATUS "Hello CMake in STATUS!")
    - 텍스트를 출력
    - STATUS 모드로 메시지 출력
      - 메시지 앞에 --이 먼저 출력됨
  - [set(\<variable> \<value>...)](https://cmake.org/cmake/help/latest/command/set.html)
  - [unset(\<variable>)](https://cmake.org/cmake/help/latest/command/unset.html)
      - 예시 
        ```cmake
        set(variable CMAKE) #변수 생성
        message("This is a " ${variable} "! ${variable}!") #변수 참조
        unset(variable) #변수 파괴
        ```
       - 변수를 생성하고 파괴
       - $<variable> 형식으로 변수 참조
  - [option(\<variable> "<help_test>" [value])](https://cmake.org/cmake/help/latest/command/option.html)
    - 예시
      - option(BUILD_EXAMPLE "Enable build examples." ON)
    - 사용자가 선택할 수 있는 옵션을 정의
    - 초기 값을 지정하지 않으면 OFF가 default
  - [list(\<sub-comand> <list> ...)](https://cmake.org/cmake/help/latest/command/list.html)
    - 예시
      - list(APPEND FILES foo.cpp bar.cpp baz.cpp qux.cpp)
      - list(FIND baz.cpp baz_cpp_index)
      - list(SORT FILES)
    - 리스트를 쓰고, 읽고, 검색, 정렬
    - 주로 APPEND, FIND를 사용
    - FIND에서 찾으려는 값이 없다면 -1 return
  - [if(\<condition>)](https://cmake.org/cmake/help/latest/command/if.html)   
  [elseif(\<condition>)](https://cmake.org/cmake/help/latest/command/elseif.html)
    - 예시
        ```cmake
        if(APPLE)
            message(STATUS "My system is macOS.")
        elseif(WIN32)
            message(STATUS "My system is Windows.")
        elseif(UNIX)
            message(STATUS "My system is Linux.")
        else()
            message(STATUS "My system is unknown.")
        endif()
        ```
    - 주어진 조건에 따라 별도의 명령을 수행하도록 제어
    - 프로그래밍 if문과 유사하지만 endif()를 사용해서 분기문의 종료를 명시해야함
  - [foreach(\<loop_var> IN [LISTS \<lists>][ITEMS \<items>])](https://cmake.org/cmake/help/latest/command/foreach.html)
    - 예시
      ```cmake
      foreach(FILE IN LISTS FILES)
        message(${FILE} " is in the list")
      endforeach()
      ```
    - 프로그래밍의 반복문과 유사하지만 endforeach()를 사용해서 반복문의 종료를 명시해야함
    - 리스트의 각 값에 대해서 명령을 수행, 보통 리스트와 함께 사용
  - [add_subdirectory(\<source_dir>)](https://cmake.org/cmake/help/latest/command/add_subdirectory.html)
    - 예시
      - add_subdirectory(subDir)
    - 빌드에 포함할 소스 디렉토리를 추가
    - 소스 디렉토리에는 CMakeLists.txt가 있어야 함
    - 프로젝트에서 폴더마다 CMakeLists.txt를 가질 수 있지만 CMake 실행할 때 지정된 CMakeLists.txt만 실행되기 때문에 해당 커맨드를 사용하여 빌드에 포함할 소스 디텍토리를 추가함
  - [add_compile_options(\<option> ...)](https://cmake.org/cmake/help/latest/command/add_compile_options.html)
    - 예시
      - add_compile_options(-Wall -Wextra)
    - 컴파일 옵션을 전역적으로 추가
    - 주로 ABI(Application Binary Interface)를 일관적으로 유지하기 위한 컴파일 옵션들을 지정하기 위해 사용
      - ABI가 일치하지 않으면 프로그램이 강제 종료될 수 있음
      - ABI는 C++버전, 매개 변수 전달 방식, 가상 함수 테이블 변경 등이 다르면 깨짐
      - 이러한 컴파일 옵션들은 항상 동일해야함

## 매우 중요한 커맨드
### Target
  - CMake에서 빌드를 정의하는 기본 단위
  - [add_executable(\<name> [WIN32] [MACOS_BUNDLE][\<source> ...])](https://cmake.org/cmake/help/latest/command/add_executable.html)
    - 예시
      - add_executable(foo src/foo.cpp)
    - 명시된 소스 파일을 사용하여 실행 타켓을 정의
    - 
### Property
  - 타겟이나 파일의 속성을 의미