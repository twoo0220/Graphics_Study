
OpenGLES API 활용

Window Manager


### EGL 초기화를 위해 윈도우 시스템에서 EGLDisplay 얻기 -> 렌더링을 할 수 있는 자원, 하드웨어, 리소스

EGLDisplay eglGetDisplay(NativeDisplayType native_display);
Win32 : HDC
Wayland : wl_display

```cpp
app.display = eglGetDisplay(Window::native_display(window));
if (app.disdiplay == EGL_NO_DISPLAY)
{
    spdlog::warn("윈도우로부터 EGLDiplay를 얻을 수 없습니다.");
    app.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
}

if (app.display == EGL_NO_DISPLAY)
{
    spdlog::error("기본 디스플레이로부터 EGLDisplay를 얻을 수 없습니다.");
    std::terminate();
}
```
1. 윈도우로부터 native_display를 얻어옴
2. EGL_NO_DISPLAY면 기본 디스플레이로 설정하고, 그래도 안된다면 그릴 수 없는 상태니 앱 종료

### EGL 초기화
EGLBoolean eglInitialize(EGLDisplay display, EGLint* major, EGLint* minor);
```cpp
EGLint majorVersion = 0;
EGLint minorVersion = 0;
if (!eglInitialize(app.display, &majorVersion, &minorVersion)) {
    spdlog::error(E"EGL의 초기화를 실패하였습니다.");
    std::terminate();
}
```

### EGL 렌더링 API 설정
EGLBoolean eglBindAPI(EGLenum api);

EGL은 OpenGL, OpenGLES, OpenVG와도 연결하여 사용할 수 있도록 설계되어있음
```cpp
if (!eglBindAPI(EGL_OPENGL_ES_API)) {
    spdlog::error("OpenGL ES를 EGL의 렌더링 API로 설정할 수 없습니다.");
    std::terminate();
}
```

### EGL 종료
EGLBoolean eglTerminate(EGLDisplay display);
```cpp
if (!eglTerminate(app.display)) {
    spdlog::error("EGL을 종료할 수 없습니다.");
    std::terminate();
}
```

### EGL 에러 검사
EGLint eglGetError(void);
- EGL에서 정의해놓은 에러값 출력
- 마지막 호출의 에러만 저장
- EGL 함수 호출이 실패했을 때 원인을 알려면 많은 자원(리소스)이 필요함. 따라서 따로 eglGetError 함수가 만들어짐
```cpp
#ifndef NDEBUG
#define EGL_TEST(function) do { \
    if (!function) { \
        EGLint error = eglGetError(); \
        if (error != EGL_SUCCESS) { \
            spdlog::error("{} with 0x{:x}.", STRING(function), error); \
            throw std::runtime_error("Err to call EGL function."); \
        } \
    } \
} while(false)
#else
#define EGL_TEST(function) \
    function
#endif

EGL_TEST(eglInitialize(app.display, nullptr, nullptr));
EGL_TEST(eglBindAPI(EGL_OPENGL_ES_API));
```

### EGLConfig 선택하기
- 원하는 옵션들을 넣고 맞는 EGLConfig 얻어오는 방법
- 모든 EGLConfig 얻어오는 방법

EGLBoolean eglGetConfigs(EGLDisplay display, EGLConfig* configs, EGLint config_size, EGLint* num_config);
```cpp
EGLint num_config;
EGL_TEST(eglGetConfigs(app.display, nullptr, 0, &num_config));

std::vector<EGLConfig> configs(num_config);
EGL_TEST(eglGetConfigs(app.display, configs.data(), confgs.size(), &num_configs));
```

EGLBoolean eglChooseConfig(EGlDisplay display, EGlint const* attrib_list, EGLConfig* configs, EGlInt config_size, EGlint* num_config);

- 유틸리티성 함수 제공
- attrib_list 매개변수는 원하는 특성을 넘겨주면 이것과 가장 잘 매치되는 특성을 넘겨줌
```cpp
EGLint config_attributes[] = {
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 16,
    EGL_STENCIL_SIZE, 8,
    EGL_NONE
};
EGLint num_config;
EGL_TEST(eglChooseConfig(app.display, config_attributes, &app.config, 1, &_num_config));
```

### EGLConfig 속성값
EGLBoolean eglGetConfigAttrib(EGLDisplay display, EGLConfig config, EGLint attribute, EGLint* value);
- 자세한 내용은 EGL 사양서에서 확인 가능
```cpp
void print(EGLDisplay display, EGLConfig config) {
    spdlog::info("(EGLConfig){} 속성 출력 시작", config);
    for (auto[attribute, name]: config_attribute_and_names) {
        EGLint value;
        EGL_TEST(eglGetConfigAttrib(display, config, attribute, &value));
        spdlog::info(" {}는 {}입니다.", name, value);
    }
    spdlog::info("(EGLConfig){} 속성 출력 종료", config);
}
```