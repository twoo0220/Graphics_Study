# CMake

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

      ```cmake
      cmake_minimum_required(VERSION 3.0.0)
      ```

    - 필요한 CMake의 버전을 명시
    - 사용자에게 특정 버전 이상의 CMake 버전 사용을 강제함으로써 호환성과 안정성 유지
  - [project(<project-name> [VERSION \<major>[.\<minor>[.\<patch>[.\<tweak>]]]   
  [LANGUAGES \<language-name> ...]])](https://cmake.org/cmake/help/latest/command/project.html)
    - 예시

      ```cmake
      project(Hello-cmake VESION 0.0.1 LANGUAGES C CXX)
      ```

    - 프로젝트의 이름, 버전, 사용하는 언어를 명시
    - 버전은 프로젝트의 릴리즈 버전을 식별하는데 사용
    - 언어는 CMake가 프로젝트를 빌드할 때 사용할 컴파일러를 결정하는 데 사용
  - [message([\<mode>] "text" ...)](https://cmake.org/cmake/help/latest/command/message.html)
    - 예시

      ```cmake
      message("Hello CMake!")
      message(STATUS "Hello CMake in STATUS!")
      ```

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

      ```cmake
      option(BUILD_EXAMPLE "Enable build examples." ON)
      ```

    - 사용자가 선택할 수 있는 옵션을 정의
    - 초기 값을 지정하지 않으면 OFF가 default
  - [list(\<sub-comand> \<list> ...)](https://cmake.org/cmake/help/latest/command/list.html)
    - 예시

      ```cmake
      list(APPEND FILES foo.cpp bar.cpp baz.cpp qux.cpp)
      list(FIND baz.cpp baz_cpp_index)
      list(SORT FILES)
      ```

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
  - [foreach(\<loop_var> IN \[LISTS \<lists>\]\[ITEMS \<items>\])](https://cmake.org/cmake/help/latest/command/foreach.html)
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

      ```cmake
      add_subdirectory(subDir)
      ```

    - 빌드에 포함할 소스 디렉토리를 추가
    - 소스 디렉토리에는 CMakeLists.txt가 있어야 함
    - 프로젝트에서 폴더마다 CMakeLists.txt를 가질 수 있지만 CMake 실행할 때 지정된 CMakeLists.txt만 실행되기 때문에 해당 커맨드를 사용하여 빌드에 포함할 소스 디텍토리를 추가함
  - [add_compile_options(\<option> ...)](https://cmake.org/cmake/help/latest/command/add_compile_options.html)
    - 예시

      ```cmake
      add_compile_options(-Wall -Wextra)
      ```

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

    ```cmake
    add_executable(foo src/foo.cpp)
    ```
  
  - 명시된 소스 파일을 사용하여 실행 타켓을 정의
- [add_library(\<name> [STATIC|SHARED] [\<source>...])](https://cmake.org/cmake/help/latest/command/add_library.html)
  - 예시

    ```cmake
    add_library(bar STATIC
      lib/bar/include/bar.h
      lib/bar/src/bar.cpp
    )
    ```

  - 명시된 소스 파일을 사용하여 라이브러리 타겟을 정의
    - 최종 결과물이 STATIC 혹은 SHARED가 되도록 정의
- [set_target_properties(\<target>... PROPERTIES \<prop value>...)](https://cmake.org/cmake/help/latest/command/set_target_properties.html)
  - 예시

    ```cmake
    set_target_properties(foo PROPERTIES
      WINDOWS_EXPORT_ALL_SYMBOLS YES # Windows만 적용됩니다
      MACOSX_BUNDLE YES              # macOS, iOS만 적용됩니다
    )
    ```

  - 타겟의 속성을 설정. 운영체제에서 지원하지 않는 속성은 무시됨.
- [target_link_libraries(\<target> [PUBLIC|PRIVATE] \<item>...)](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)
  - 예시

    ```cmake
    target_link_libraries(foo PRIVATE bar)
    # foo 타겟이 빌드되기 전에 bar 타겟이 먼저 빌드가 되어야 하도록 정의
    # bar 타겟의 코드가 변경되면 foo 타겟도 역시 다시 빌드
    # 만약 some 타겟이 foo 타겟의 의존성을 가지고 있다고 하더라도,   
    # foo 타겟은 bar 타겟의 의존성을 PRIVATE로 가지고 있기 때문에   
    # some 타겟(다른 타겟)은 bar 타겟의 영향을 받지 않게 됨
    ```

  - 타겟을 링킹할 때 필요한 타겟이나 라이브러리를 지정
  - 타겟이 지정된 경우 의존성이 정의
  - 빌드 과정 중 링크 단계에 영향을 줌
    - PUBLIC 혹은 PRIVATE 통해 타겟에 정의된 의존성들을 전파할지 말지 정의 가능
    - 동작 원리는 클래스와 거의 유사
- [target_sources(\<target> [PUBLIC|PRIVATE] \<source>...)](https://cmake.org/cmake/help/latest/command/target_sources.html)
  - 예시

    ```cmake
    target_sources(bar PRIVATE
      src/baz.h
      src/baz.cpp
    )
    ```

  - 소스 파일에 타겟을 추가
  - PUBLIC 혹은 PRIVATE으로 추가하는 소스 파일 공개 범위 지정 가능
- [target_compile_definitions(\<target> [PUBLIC|PRIVATE] \<item>...)](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html)
  - 예시

    ```cmake
    target_compile_definitions(foo PRIVATE NOMINMAX)
    # foo 타겟에 PRIVATE로 NOMINMAX를 지정
    # foo 타겟은 NOMINMAX를 사용할 수 있지만, foo 타겟을 의존성으로 가지고 있는 다른 타겟들은 NOMINMAX를 사용할 수 없음
    ```

  - 타겟을 컴파일할 때 사용할 컴파일 디파인을 지정
  - 빌드 과정 중 전처리 단계에 영향
  - PUBLIC 혹은 PRIVATE를 사용하여 추가하는 컴파일 디파인 공개 범위 지정 가능
- [target_include_directories(\<target> [PUBLIC|PRIVATE] \<item>...)](https://cmake.org/cmake/help/latest/command/target_include_directories.html)
  - 예시

    ```cmake
    target_include_directories(bar PUBLIC bar/include)
    # PUBLIC이기 때문에 bar 타겟에 의존성을 가지고 있는 다른 타겟들도 해당 인클루드 디렉토리 사용 가능
    ```

  - 타겟을 컴파일할 때 사용할 include 디렉토리를 지정
  - 빌드 과정 중 전처리 단계에 영향
    - PUBLIC 혹은 PRIVATE를 사용하여 사용할 include 디렉토리 공개 범위 지정 가능
- [target_compile_options(\<target> [PUBLIC|PRIVATE] \<item>...)](https://cmake.org/cmake/help/latest/command/target_compile_options.html)
  - 예시

    ```cmake
    target_compile_options(bar PRIVATE -pedantic)
    ```

  - 타겟에 컴파일 옵션을 추가
    - PUBLIC 혹은 PRIVATE를 사용하여 추가하는 컴파일 옵션 공개 범위 지정 가능
  - 타켓마다 다른 컴파일 옵션을 가질 수 있기 때문에 **ABI에 영향을 주지 않는 컴파일 옵션들만 사용해야 함**

### Property

- 타겟이나 파일의 속성을 의미

## CMake 변수

- 변수 : 값을 저장할 수 있는 저장 공간
- CMake는 문자열 타입만 지원
- 변수의 이름은 대소문자를 구분
  - 따라서 알파벳, -, _ , 만 사용해서 변수 이름 짓기를 권장(숫자도 가능은 함)
  - CMake 자체 내장 변수들을 제공하는데 CMAKE_, _CMAKE_ 로 시작함

  ```cmake
    # 변수 생성 및 출력
    set(I_AM_VARIABLE TRUE)
    message(STATUS ${I_AM_VARIABLE})

    # CMake 내장 변수 출력
    message(STATUS "System Name: ${CMAKE_SYSTEM_NAME}")
    message(STATUS "System Version: ${CMAKE_SYSTEM_VERSION}")
    message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "Install Directory: ${CMAKE_INSTALL_PREFIX}")
  ```

- CLI 실행시 변수를 설정할 수 있음

### 자주 사용하는 CMake 내장 변수

- 내장 변수는 전역 변수이기 때문에 최대한 사용하지 않는 것을 권장
- [CMAKE_SYSTEM_NAME](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html)
  - 빌드를 실행할 운영체제의 이름

  ```cmake
  # CMAKE_SYSTEM_NAME을 사용하여 운영체제마다 다른 명령어 실행
  if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("OS is Windows.")
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("OS is Linux.")
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("OS is macOS.")
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    message("OS is Android.")
  else()
    message("OS is unknown.")
  endif()
  ```

  - 운영체제를 설명하는 변수
    - WIN32, LINUX, APPLE, ANDROID, IOS ...
- [BUILD_SHARED_LIBS]()
  - 라이브러리 타겟이 동적 또는 정적으로 빌드될지 결정

  ```cmake
  # 라이브러리 타겟이 동적(TRUE) 또는 정적(FALSE) 빌드 설정
  set(BUILD_SHARED_LIBS FALSE)

  # BUILD_SHARED_LIBS에 의해 라이브러리 타겟이 동적 또는 정적으로 빌드
  # 아래 예시에서는 타겟 foo의 빌드 결과물이 지정되지 않았기 때문에 정적으로 빌드
  add_library(foo
    src/foo.cpp
  )
  ```

- [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html)
  - 바이너리가 설치될 경로를 지정
- [CMAKE_CXX_STANDARD](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html)
  - 모든 타겟의 C++ 버전 기본값을 설정
  - C++ 버전이 타겟마다 다를 경우 ABI가 깨질 수 있기 때문에 사용해서 설정하는 것을 권장

### CMake Test

#### CTest 모듈

- CMake에서 제공하는 테스트 도구 모듈
- 테스트를 쉽게 정의 가능
- include(CTest)를 통해 호출할 수 있으며, 테스트를 정의하기 위한 커맨드와 변수들이 정의되어 있음
- **[BUILD_TESTING]()**
  - CTest 모듈에서 생성하고 사용하는 변수
  - 변수의 기본 값은 ON이며, OFF인 경우에는 테스트가 활성화되지 않음
  - enable_testing() 명령어를 통해 테스트 강제 활성화 가능
    - 명령어를 입력한 현재 경로 이하에 대한 테스트를 활성화
    - BUILD_TESTING이 OFF인 경우에도 강제로 활성화
- [add_test(NAME \<name> COMMAND \<command> [\<arg>...])]()
  - 테스트를 정의
  - 예시

    ```cmake
    # 테스트 정의
    # 실행 파일의 반환값이 0이면 성공이고, 0이 아니면 실패
    add_test(NAME foo-test COMMAND pass)

    add_test(NAME bar-test COMMAND fail)
    ```

- [set_test_properties(\<test>... PROPERTIES \<prop value>...)]()
  - 테스트 속성을 설정하여 동작을 제어
  - 테스트 환경 변수, 실행 옵션, 타임아웃 등의 속성을 설정
  - 예시

    ```cmake
    # 테스트 정의
    add_test(NAME baz-test COMMAND fail "Fail is not fail.")

    # 테스트 속성 정의
    # PASS_REGULAR_EXPRESSION 정규식 속성을 정의
    # 프로그램의 출력값이 정의한 정규 표현식을 만족하면 테스트 통과
    set_test_properties(baz-test PROPERTIES PASS_REGULAR_EXPRESSION "Fail is not fail.")
    ```

### CMake를 이용한 프로그램 설치

- [install(TARGETS \<target>...   
[EXPORT \<export-name>]   
[[ARCHIVE|LIBRARY|RUNTIME] [DESTINATION \<dir>]]   
[INCLUDES DESTINATION \<dir>...])](https://cmake.org/cmake/help/latest/command/install.html)
  - 타겟들을 어떻게 그리고 어디에 설치할지 설정
  - 예시

    ```cmake
    # 타겟들의 설치 규칙 설정
    # CMAKE_INSTALL로 정의된 경로에 설치
    # EXPORT installing-config는 install 이후 CMake에서 설치된 파일을 참조하기 위한 파일을 생성하기 위해 필요
    install(TARGETS foo EXPORT installing-config   
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDESDIR})
    ```

- [install(FILES \<files>... TYPE \<type> | DESTINATION \<dir>)](https://cmake.org/cmake/help/latest/command/install.html)
  - 파일들을 타입에 따라 설치하거나 어디에 설치할지 설정
  - 예시

    ```cmake
    # 파일들을 어디에 설치할지 설정
    install(FILES include/foo.h DESTINATION ${CMAKE_INSTALL_INCLUDESDIR})

    # 파일들을 타입에 따라 설치
    install (FILES include/foo.h TYPE INCLUDE)
    ```

- [install(EXPORT \<export-name> DESTINATION \<dir> [NAMESPACE \<namespace>])](https://cmake.org/cmake/help/latest/command/install.html)
  - CMake에서 설치된 타겟을 사용하기 위한 파일을 생성하고 설치
  - 네임스페이스는 C++과 동일한 개념이며 설치되는 대상들을 그룹화하고 이름 충돌을 방지하기 위해 사용
  - 예시

    ```cmake
    install(EXPORT installing-config
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/installing
      NAMESPACE installing::
    )
    ```

### CMake를 이용한 프로그램 배포

- [IntallRequiredSystemLibraries](https://cmake.org/cmake/help/latest/module/InstallRequiredSystemLibraries.html#installrequiredsystemlibraries) 모듈
  - 필요한 시스템 런타임 라이브러리를 자동으로 찾아 패키징에 추가
- [CPack](https://cmake.org/cmake/help/latest/release/3.1.html#cpack) 모듈
  - 설치 프로그램과 소스 패키지를 생성할 수 있는 CPackConfig.cmake와 CPackSourceConfig.cmake를 생성
- CPack
  - 패키징을 실행하는 도구

## 모던 빌드 시스템(Modern Build System)

- 기존 빌드 시스템 문제점

  ```cmake
  # 빌드에 포함할 소스 디렉토리를 추가
  add_subdirectory(tcp)

  # 타겟 프로그램 정의
  add_executable(client main.cpp)

  # 컴파일할 때 사용할 인클루드 디렉토리를 지정
  include_directories(tcp/include)

  # 컴파일할 때 사용할 컴파일 디파인을 지정
  add_definitions(IPV6)

  # 타겟을 링킹할 때 필요한 타겟이나 라이브러리를 지정
  target_link_libraries(client tcp)
  ```

- 위 예시는 모던 빌드 시스템을 위반하고 있음
  - include_directories를 사용하여 tcp의 인클루드 디렉토리를 지정한 부분
  - add_definitions을 사용하여 tcp에 필요한 컴파일 디파인을 지정한 부분
    - tcp에 관련된 내용들이 client 타겟을 정의할 때 사용되고 있기 때문!
    - **tcp에 관련된 내용들은 tcp 타겟을 정의할 때 정의되어야 함**
- 빌드를 정의할 때 변수를 사용하기 때문에 모든 설정이 전역으로 영향을 미침
  - 전역으로 영향을 미치기 때문에 빌드 스케일업이 불가능
  - 빌드 확장을 할 수 없다는 의미는 빌드 병렬화가 불가능하다는 말
  - 타겟끼리 상호 참조나 숨겨진 의존성이 발생하기 쉬움

### Modular 디자인 정의

- John Lakos가 Large-Scale C++ Software Design에서 제안
- 디펜던시 그래프는 단방향 그래프이어야 함
- 모듈은 고유한 역할을 담당해야 함
- 모듈은 쉽게 재사용될 수 있어야 함
  - CMake는 3.0부터 본격적으로 도입
  - 즉, 모듈이 핵심!
- 장점
  - 상호 참조나 숨겨진 의존성 사용을 막아줌
  - 개발자가 모듈 레벨로 생각할 수 있게 해줌
- 작성법
  1. 모듈을 정의
     - CMake에서 **타겟을 정의**하는 것에 해당
  2. 모듈을 설정
     - CMake에서 **속성을 정의**하는 것에 해당
  3. 모듈이 공개해야 할 것과 하지 않을 것을 분리
     - CMake에서 PUBLIC과 PRIVATE 사용하는 것에 해당
  
### 모던 CMake 작성법

- ABI 영향을 주는 전역 설정
  - 예시
    ```cmake
    # 사용할 C++ 버전을 20으로 설정
    set(CAMEK_CXX_STANDARD 20)

    # 컴파일러에 따른 컴파일 옵션 설정
    if (MSVC)
      add_compile_options(/W3 /WX)
    else()
      add_compile_options(-Wall -Werror)
    endif()
    ```
- 타겟을 정의
  - 예시
    ```cmake
    # 라이브러리 타겟을 정의
    add_library(foo STATIC lib/foo.cpp)

    # 실행 타겟을 정의
    add_executable(bar src/bar.cpp)
    ```
- 타겟에서 PUBLIC과 PRIVATE 구분
- 타겟의 프로퍼티(Property) 설정
  - 예시
    ```cmake
    # 타겟을 컴파일할 때 사용할 include 디렉토리를 지정
    target_include_directories(foo
    PUBLIC
      include
    PRIVATE
      src
    )

    # 타겟을 링킹할 때 필요한 타겟이나 라이브러리를 지정
    target_link_libraries(foo
    PUBLIC
      abc
    PRIVATE
      wyz
    )
    ```
  - 가급적 하지 말아야할 금기 사항
    - 전역으로 영향을 주는 설정을 하지 말 것
    - 타겟에 ABI에 영향을 주는 설정을 하지 말 것
    - 타겟 밖의 디렉토리를 include 디렉토리로 지정하지 말 것
    - 예시
      ```cmake
      # 모든 타겟에 영향을 주는 include 디렉토리를 지정
      include_directories(include)

      # 모든 타겟에 영향을 주는 컴파일 디파인을 지정
      add_definitions(NOMINMAX)

      # 모든 타겟이 링킹할 타겟이나 라이브러리를 지정
      link_libraries(abc xyz)

      # ABI에 영향을 주는 컴파일 옵션을 타겟에 지정
      target_compile_options(foo PRIVATE -no-rtti -std=c++0x)

      # 타겟 밖의 디렉토리를 타겟의 include 디렉토리로 지정
      target_include_directories(foo PUBLIC ../bar/include)
      ```


#### vcpkg

- 오픈 소스 패키지 매니저
- C++은 오래전에 출시되었기 때문에 패키지 매니저가 없었음
  - 프로젝트에서 의존성을 관리하는 것이 매우 어렵고 이로 인해 많은 문제들이 생겨남
  -  이를 해결하고자 마이크로소프트에서 C++ 패키지 매니저 vcpkg를 개발
  -  오픈 소스로 공개
-  사용하기 매우 쉬움
-  다양한 환경에서 사용 가능
   -  크로스 플랫폼을 고려한다면 매우 쉽게 관리 가능
-  신뢰성 보장
-  설치는 vcpkg 깃허브 홈페이지에서 다운로드 후 설치 스크립트파일 실행
-  기본적으로 ./vcpkg -help 명령어를 통해 알 수 있음
-  

#### CMake를 이해하기 위한 동적/정적 라이브러리 차이

- 라이브러리 빌드 과정
  - 소스 코드 → 전처리기 → 컴파일러(어셈블리 코드) → 어셈블러(오브젝트 파일) → 링커
  - 링커가 오브젝트 파일을 받아어 동적 or 정적 라이브러리 생성
- 동적 라이브러리
  - 실행가능한 코드
  - 프로그램이 실행될 때 또는 실행 중에 메모리에 로드
  - 여러 프로그램에 공유되어 사용 가능
  - 동적 라이브러리를 업데이트 하면, 해당 라이브러리를 사용하는 모든 프로그램이 새 버전의 라이브러리를 사용
  - 새 버전의 동적 라이브러리가 호환성을 보장하지 않는다면 기존 프로그램이 동작하지 않을 수 있음
- 정적 라이브러리
  - 오브젝트 파일의 모음
  - 컴파일 시간에 프로그램의 실행 파일에 포함
  - 여러 프로그램에 공유되지 않음
  - 프로그램은 정적 라이브러리의 복사본을 갖기 때문에, 여러 프로그램이 동일한 라이브러리를 사용할 경우 저장공간 사용량 증가
  - 호환성을 고려하지 않아도 괜찮음
  - 메모리와 저장공간의 비용은 매우 비싸고 보안상의 이유로 일부 운영체제에서는 정적 라이브러리를 요구
- C++ 동적 라이브러리 구현 주의점
  - C++은 함수 오버로딩을 지원하기 위해 함수 이름 맹글링(Name Mangling)이 적용
  - 예시
    |기존 함수 이름|맹글링된 이름|
    |---|---|
    |void my_func()|_Z5my_funcv|
    |void my_func(int a, char c)|_Z5my_funcic|
  - 동적 라이브러리의 함수 주소를 얻기 위해서는 함수 이름이 필요
  - 맹글링된 함수 이름을 알아내는 것은 매우 어려움
  - C는 네임 맹글링이 없음
  - C++에서 네임 맹글링을 방지하기 위해 함수 링킹을 C로 강제
- 동적 라이브러리 검색 순서
  - 운영체제마다 다름
  - Windows
    - 실행 파일 디렉토리
    - System32와 같은 시스템 디렉토리
    - Windows 디렉토리
    - 환경 변수 PATH에 지정된 디렉토리
  - Linux
    - 환경변수 LD_LIBRARY_PATH에 지정된 디렉토리
    - etc/ld.so.conf에 지정된 디렉토리
    - /lib, /usr/lib와 같은 시스템 디렉토리
- 동적 라이브러리 사용 방법
  - 동적 로딩 기능을 제공하는 라이브러리를 링킹
  - 동적 로딩 기능을 제공하는 라이브러리가 운영체제마다 다름
    - CMake는 CMAKE_DL_LIBS 변수를 제공하여 개발자에게 편의 제공
    - CMAKE_DL_LIBS 변수 값은 운영체제마다 다르게 설정
  - 사용 순서
    - 동적 라이브러리 열기
    - 동적 라이브러리에서 사용하고자 하는 함수의 주소 가져오기
    - 얻어온 함수의 주소 호출
    - 프로그램이 종료될 때 동적 라이브러리 닫기   
      ||Windows|UNIX 계열|
      |---|---|---|
      |라이브러리 열기|LoadLibrary|dlopen|
      |라이브러리 닫기|FreeLibrary|dlclose|
      |함수 주소 가져오기|GetProcAddress|dlsym|
  - Windows 동적 라이브러리 사용 예시
    ```C++
    #include <windows.h>

    HMODULE hMod = LoadLibrary("foo.dll");

    if (hMod) {
      typedef void (*FuncType)();
      FuncType func = (FuncType)GetProcAddress(hMod, "foo_print");

      if (func) {
        func();
      }

      FreeLibrary(hMod);
    }
    ```
  - UNIX 계열 동적 라이브러리 사용 예시
    ```C++
    #include <dlfcn.h>

    void* handle = dlopen("foo.so", RTLD_LAZY);

    if (handle) {
      typedef void (*FuncType)();
      FuncType func = (FuncType)dlsym(handle, "foo_print");

      if (func) {
        func();
      }

      dlclose(handle);
    }
    ```
  - 운영체제마다 다른 API를 사용하기 때문에 추상화시킬 것
