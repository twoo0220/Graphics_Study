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
    - 윈도우 그래픽스 드라이버를 업데이트하면 최신 버전으로 업데이트됨(4.6)

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


