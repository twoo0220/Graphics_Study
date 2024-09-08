# OpenGL과의 차이점

- OpenGL은 상태 머신(State Machine)이 존재하기 때문에 멀티 스레드를 지원할 수 없음.
  - 상태 머신의 동기화가 보장되지 않기 때문.
  - Vulkan은 상태 머신이 없지만 커맨드 버퍼에 커맨드를 기록하는 방식
- OpenGL은 멀티 코어 CPU를 활용하지 못하지만 Vulkan은 가능
  - 성능의 문제가 되는 경우 대부분은 CPU 병목현상 때문
- OpenGL은 암시적(Implicit)이고 Vulkan은 명시적(Explicit)
  - 명시적이기 때문에 API를 호출했을 때 발생하는 오버헤드를 예측할 수 있음
- Vulkan은 성능을 극한으로 낼 수 있지만 프로그래밍 난이도가 매우 높음
- Vulkan 개발을 돕기 위해 다양한 도구를 사용할 수 있음
  - RenderDoc, GfxReconstructor, Validation Layer

## Vulkan SDK 구성

|목록|설명|
|-----|-----|
|Vulkan Header File|Vulakn API 호출을 위한 헤더 파일|
|Vulakn Loader|어플리케이션, Layer, 드라이버 사이의 중개자 역할을 하는 라이브러리|
|Validation Layer|잘못된 API 사용에 대한 피드백을 제공하여 오류를 쉽게 수정할 수 있게 도와주는 Layer|
|쉐이더 컴파일러|GLSL에서 SPIR-V로 변환하는 컴파일러|
|Vulkan 도구|Vulkan 개발에 도움이 되는 도구들|
|Vulkan 예제|Vulkan으로 작성한 예제|

- Vulkan 개발에 필요한 모든 것들이 Android NDK에 포함되어 있음