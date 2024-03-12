# Inflearn OpenGL 강의 정리

## 그래픽스 파이프라인

- 매우 많은 데이터를 단계적으로 처리(step-by-step)
- 조금 더 세분화한 순서
  1. Primitive Processing
  2. Transform and Lighting
  3. Primitive Assembly
  4. Rasterizer
  5. Texture Environment
  6. Color Sum
  7. Fog
  8. Alpha Test
  9. Depth Stencil
  10. Color Buffer Blend
  11. Dither
  12. Frame Buffer
- 간소화 및 필수적인 순서
  1. Vertex Input
  2. vertex processing
  3. primitive assembly
  4. rasterization
  5. fragment processing
  6. blend (post-processing)
  7. frame buffer
- Vertex : 기하학 관점의 삼각형 꼭지점
- Fragment : 래스터 관점의 삼각형에서 pixel + 관련 자료(색상, 깊이 등)

### 프로그래머블 그래픽스 파이프라인

- 중요 단계마다 병렬 처리로 가속(parallel processing acceleration)
- 일부를 shader로 구현
  - vertex shader
  - fragment shader

## GLSL

- Open**GL** **S**hading **L**anguage
  - OpenGL 2.0 이상
  - C언어와 유사
- 새로운 자료형 도입 + 연산 추가
  - 2/3/4차원 벡터 vector : vec2, vec3, vec4
  - 2/3/4차원 행렬 matrix : mat2, mat3, mat4
  - 샘플러 samplers
- OpenGL 3.3부터는 GLSL이 많이 쓰일 것을 확인하여 GLSL version도 3.3으로 통일
  - 그 전에는 GLSL 버전이 OpenGL 버전과 다름
  - GLSL 4.0부터 Geometry shader 사용 가능

### Register 이름

- attribute : primitive의 attribute(속성, 성질)
- varying : 바뀌는, 변화하는
- uniform : 일정한, 변하지 않는 -> 사실상 global constant
- attribute registers : input 버텍스 -> 입력이 되는 인풋 버텍스들을 저장하는 레지스터, 역사적으로 그렇게 부르기로 함
- varying register : output 버텍스 -> 자주 쓰는 아웃풋 버텍스들은 pre-defined output registers로 정의  


### Registers in GPU

- a register (cluster) = 4 x float
  - use 1,2,3 or 4 float's according to the cases
  - RGBA
  - float.x,y,z,w = 16 byte
- Primitive Assembly & Rasterization
  - 3개의 버텍스를 모아서 삼각형 하나 생성
- Processing Varying Variables
  - 이중 선형 보간(bi-linear interpolation) : 출력해야 하는 모든 fragment 마다 비례식으로 계산
- fragment shader
  - 모든 프래그먼트마다 적용

## Shader Program 구조

- step 1: shader program의 compile, link, use
  - Vertex Shader
    - glCreateShader
    - glShaderSource (VS source code)
    - glCompileShader
  - Fragment Shader
    - glCreateShader
    - glShaderSource (FS source code)
    - glCompileShader
  - Shader Program
    - glCreateProgram
    - glAttachProgram (VS.obj 붙이기)
    - glAttachProgram (FS.obj 붙이기)
    - glLinkProgram
      - 하나의 shader.EXE 파일 만들기
    - glUserProgram
      - 전체 OpenGL 관점에서 이런 shader program을 여러개 사용할 수 있는데 어떤 걸 사용할지 알려주는 함수
- step 2 : vertex data를 제공 -> shader program은 자동 실행
  - vertex shader
    - in : attribute register
    - out : varying register
    - gl_Position : pre-defined out, vertex position을 저장
    - GPU에서 병렬처리됨!
        - 각 좌표들마다 vertex shader를 동시에 처리
  - fragment shader
    - in : varying registers
    - out : framebuffer update
