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