# Inflearn OpenGL 강의 정리

### 컴퓨터 그래픽스(Computer Graphics)
- 컴퓨터를 이용해서 이미지/애니메이션을 만들어내는 모든 기술


### 그래픽스 시스템
이미지는 프레임버퍼에 저장  
- 이미지 -> 색깔 있는 사각형의 2차원 배열  
- 픽셀 - picture elemenet  
- 래스터 raster = 픽셀의 2차원 배열  
- 프레임 버퍼 = 픽셀을 저장한 메모리 영역  
- 인간의 눈은 약 24FPS 정도의 성능
- 프로젝션(projection), 투사, 투영  
3차원 물체 -> 2차원 화면  

### 그래픽스 아키텍처
#### 모델링-렌더링 패러다임  
- 서로 독립적인 프로그램, 파일로 자료교환  
- 모델링 프로그램 / 렌더링 프로그램이 서로 독립적  
- 모델러(AutoCAD, 3DS, MAYA 등) // 렌더러(Renderer) 프로그램, 픽사의 렌더맨 등

#### 대화형 처리 모델
- CPU 단독 처리 모델
- 단점 : CPU가 해야할 계산량이 너무 많음
- 호스트 컴퓨터(Host Computer) -> 이미지 생성 -> D/A coverter(초기 그래픽 카드) -> 아날로그 모니터

#### DPU 모델
- 그래픽스 처리만 전담하는 특별만 목적의 프로세서 장착
- 파이프라인 모델로 가는 중간 단계
- 호스트 컴퓨터 -> DPU -> 아날로그 모니터

#### 파이프라인 모델
- 전용 그래픽 카드 방식 모델
- 그래픽스 처리 과정을 단계별로 VLSI 칩으로 처리
- 실리콘 그래픽스(Silicon Graphics)가 도입
- 호스트 컴퓨터 -> Vertex Processing -> Primitive Assembly -> rasterizer -> fragment processing -> 모니터

#### 프로그래머블(programmable) 파이프라인 모델
- 고정된 VLSI 칩 대신, 프로그래밍 가능한 processor, GPU를 사용
- 호스트 컴퓨터 -> Vertex Shader -> Primitive assembly ->rasterizer -> fragment shader- > 모니터


#### 과거의 기술을 돌아봐야 하는 이유
1. 과거의 흔적이 남아있어 과거에 왜 그랬는지를 돌아보면 현재 동작 방식을 이해하는데 수월함
2. 현재 생각하고 있는 기술들을 당시에도 생각해봤다는 것을 이해할 수 있음


### OpenGL 2.0 이후
- GPU 기반으로 모든 일을 처리
- shader program 방식
    - OpenGL라이브러리 내에, shader를 compile / link 하는 기능 포함
### OpenGL 3.0 이후
- backward compatibility 포기, 예전 코드들은 작동하지 않음
### OpenGL 4.0 이후
- geometry shader, tesselation shader 등의 새로운 기능 추가
- OpenGL 3.3 이후에 획기적인 변화는 없음

## OpenGL 라이브러리
### OpenGL core library
- libGL.so : 대부분의 Unix/Linux 시스템, Mac 시스템
- opengl32.dll : 마이크로소프트 윈도우
    - 윈도우 최초 설치 시에는 매우 오래된 버전을 제공(1.1)
    - 윈도우 그래픽스 드라이버를 업데이트하면 OpenGL32.dll 등이 최신 버전으로 업데이트됨(4.6)

### OpenGL Utility Library(GLU) -> 사용중지(deprecated)
- libGLU.so, glu32.dll 등
- 일부 core library 보강 기능, 예전 코드에서 사용

#### 윈도우 시스템의 역할
- 2D 화면 전체의 제어
- 화면에 2D 윈도우 생성/이동/크기 조정/축소/삭제 등
    - GLX(X window)
    - WGL(MS window)
    - AGL(Macintosh)

#### OpenGL 입장
- 2D 윈도우 내에 2D/3D 그래픽 출력
- 윈도우 자체는 윈도우 시스템이 제어
- 단일 플랫폼에서는 상관없지만 멀티플랫폼이라면 각 윈도우 시스템마다 별도 설정을 해줘야함
    - 이를 도와주는 툴킷이 OpenGL Utility Toolkit(GLUT), 거의 모든 윈도우 시스템의 공통 기능만 제공
    - 높은 이식성이 있지만 제한된 기능만 제공되며 현재는 사용 중지
    - freeglut 저작권문제, 관리부재로 사용중지
- 결국 최근에 가장 많이 사용하는 것은 GLFW (OpenGL Frame Work)
    - 오픈소스, 멀티플랫폼(OpenGL, ES, Vulkan)


### OpenGL Extensions
#### OpenGL core library / core feature
- OpenGL version X.YY 에서는 반드시 제공해야 하는 기능

#### OpenGL extensions
- 핵심 기능은 아니지만 표준의 일부
- 현재 약 400개 이상의 표준 extension 제공
- 기술의 빠른 발달로 인하여, 하드웨어 제공자가 좋은 기능을 바로 추가
- 일단 extension으로 등록후 나중에 core library 기능으로 포함 가능
- core feature만 사용한다면 높은 이식성(high portability) 확보 가능
    - extension을 사용하면 최신 기능을 더 효과적으로 구현 가능
    - 특정 그래픽카드에서만 돌아가는 프로그램의 경우 익스텐션을 활용하여 구현한 경우가 많음

## GLEW
#### OpenGL Extension Wrangler Library
- OpenGL extension 사용을 도와주는 라이브러리
- OpenGL 모든 version의 사용을 지원
- 어떤 extension이 사용 가능한지 체크 가능
- 모든 OpenGL version / 표준 extension의 모든 함수에 대한 인터페이스 제공
    - 해당 함수를 실행 -> 하드웨어가 지원하는 경우에만 결과가 나옴, 지원하지 않으면 에러처리
- 반드시 GLEW 먼저 include 하고 glfw include 하도록 순서 주의!

### 3D 그래픽스에서 필요한 기능들
#### 프리미티브 출력 (primitives)
- 점(points), 선분(line segments), 삼각형(triangles)
- 3D 출력이 가능한 요소들을 제공
- 삼각형들을 거리에 따라서 정밀(refine) 혹은 단순하게(simple) 그림

#### 속성 설정(attribute)
- 프리미티브의 속성 : 삼각형의 색상 등  
#### 질의(query)
- 현재 상태에 대한 질의
#### 좌표 변환(transformation)
- 모델링 변환, 뷰잉 변환, 프로젝션 변환

-> 여기까지 OpenGL이 담당
윈도우 제어(window control) : 윈도우 시스템, 장치 입력 등은 GLFW 담당

### OpenGL 스테이트 관리(state)
#### OpenGL은 state machine 개념으로 구현
- 내부 상태 state (예: color = white)
- OpenGL draw 과정
  - state chagne : 내부 상태 설정
  - primitive output : 프리미티브 출력
  - 같은 primitive로, 다른 출력 가능!

### 객체 지향 개념의 결여
#### OpenGL은 1980년대에 이미 개념 정립
#### C언어 기반, function overloading 사용 불가
- C++ 인터페이스도 제안되었으나, 효율성 문제로 사용하지 않음
  - 짧은 시간안에 최대한 많이 그려야하므로
- 사용하려는 자료형에 따라 함수 이름이 바뀜

#### OpenGL 함수 작명법
- gl / glfw / glew : OpenGL / GLFW / GLEW library
- function name 함수 이름 : 기능 설명
- 2/3/4 차원 dimension 필요한 argument 숫자
- i/ui/f/d 자료형(data type)
- v: vector 또는 array 배열
- 예시
  - void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
  - gl + Uniforom + 3 + f

#### 보일러 플레이트(boiler plate) 코드
- 표준코드, 표준 문서, 상용구라는 의미
- (최소한의 변경으로) 여러 번 재사용되고 반복적으로 비슷한 형태를 사용하는 코드
- 강철로 만들어서 재사용하는 인쇄판이 본래 뜻
- 즉, 반복해서 재사용하는 부분만 강철로 제작

### 2개의 좌표계
#### 윈도우 시스템 좌표계
- 프레임버퍼 / 픽셀 = 2차원 배열 : 컴퓨터 디스플레이 기준
- integer 정수 좌표 사용
- upper-left corner에 원점(좌상단)
  
#### 3D 그래픽스 좌표계
- 수학에서 사용하는 3차원 좌표계 : 교과서 기준
- float 실수 좌표 사용
- lower-left 또는 center에 원점(좌하단)

#### Callback 함수
- 미리 등록해두었다가 나중에 특별한 이벤트가 생기면 자동 호출되는 함수

### OpenGL : delayed execution
- 지연 실행
- OpenGL 함수는 효율성을 높이기 위해, 명령어 큐에 기록하고 바로 return
- 실제 그 함수의 실행은 명령어 큐에서 delated execution
- 실행 순서 예시
  - OpenGL 응용 프로그램
  - 모든 OpenGL 함수는 자기가 실행시키고 싶은 기능을 queue에 기록하고 즉시 return
  - 명령어 큐 GL command queue
    - delayed execution : queue에 들러온 순서대로 실행
    - 렌더링 파이프라인이 할 일이 없어 기다리는 걸 방지하려고 만든 구조
  - OpenGL rendering pipeline
    - 항상 항 일이 있으므로, 대기 시간이 없음
- glflush, glfinish 함수들은 최대한 적게 사용하는 것이 좋음

#### 컬러 모델(color model)
- 컴퓨터 하드웨어/소프트웨어에서 색상을 표현하는 방법
- RGB, CMY, grayscale 등등
- color gamut(색 영역)
    - 특정 컬러 모델에서 표현 가능한 모든 색상 영역
    - 컬러 큐브(color cube, color solid)
- RGB
    -인간 시각에 가장 민감한 3원색(빨강, 녹색, 파랑)
    - 가산 색계 : 더할수록 밝아짐
    - 모니터, LCD용
        - 형광물질로 RGB 색상
        - 컴퓨터 그래픽스의 주된 관심사
- CMY
    - 인쇄용으로 가장 적합한 3원색
    - 감산 색계 : 더할수록 어두워짐
    - 프린터, 인쇄용
    - CMYK (CMY + K(black))
        - 이론적으로는 cyan + magenta + yellow = black 이어야 하지만 그렇지 않음
        - 실제로는 짙은 회색이 나옴(dark gray)
        - 공학적 해결책으로 black 별도 제공
- RGB 색상과 CMY 잉크 변환 가능
    - 이론적으로는 대응 관계이지만 실제로는 각 회사마다 고유 기술로 출력값들이 다름

#### Color depth 색 깊이, 컬러 심도
- 픽셀 당 몇 bit를 쓸 것인가?
- 품질 문제 : 더 많은 bit -> 더 좋은 품질
- 비용 문제 : 더 많은 bit -> 더 많은 memory
- 인간의 시각은 약 200단계 색상 차이를 인식
    - 200 < 256 = 2^8 -> 8bit!
    - 따라서 보통은 8bit정도면 충분함(0 ~ 255)
    - 전문가 : 더 많은 단계 인식 가능


#### Color Image
- 3 color channels 사용(RGB)
- 각 채널마다 8bit 사용
- 1 pixel = 3 color channels -> 3 * 8bit -> 24bit per pixel (24비트 컬러 모델)
- 그래픽 카드 내부 구조
    - framebuffer : pixel마다 red / green / blue, 3channels
    - 각 채널마다, n bit 할당 : 2^n * 2^n * 2^n colors = 총 2^3n colors
    - True Color System
        - 3n = 24 -> 현재 가장 많이 사용하는 LCD 모니터
    - HDRI = high dynamic range imaging
        - 3n = 30 -> 더 넓은 명도 범위로 고품질, 이미지 편집 시에 유리
        - 일반인이 이걸 사용한다고 해도 구분 못하는 경우가 많음


#### RGBA colormodel
- RGB + A(Alpha channel)
- 알파 채널에 투명도 저장
    - 투명도 1.0 -> 완전 불투명
    - 투명도 0.5 -> 50% 투명
    - 투명도 0.0 -> 완전 투명
- True Color System, with alpha channel
    - 4n = 32
    - 픽셀당 4 byte 사용 -> (R, G, B, A)
        - 직관적 표현 방식 : 정수 사용
        - RGBA 모두 0 ~ 255 사이의 정수
    - OpenGL 방식
        - 정수 표현은 4n = 32일 때만 정확한 색상
        - 정확성을 위해, 0.0 ~ 1.0 사이의 실수(float) 사용
- Zhang, et.al. "Colorful Image Colorization", EVVC 2016