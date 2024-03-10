#### void glfwMakeContextCurrent(GLFWwindow* win);
- GLFW에서 윈도우를 여러개 만들었을 경우, 특정 한 개를 골라서 해당 윈도우에 OpenGL 출력하도록 설정하도록 고르는 명령

#### int glfwWindowShoudlClose(GLFWwindow* win)
- 윈도우의 현재 상태를 점검하여 지금 닫아야하는지 확인
- 윈도우 창의 x버튼을 누르면 terminate 호출

#### void glfwPollEvents(void)
- 지금 어떤 이벤트들이 발생했는지 확인

#### void glfwSwapBuffers(GLFWwindow* win)
- 윈도우 화면을 업데이트

#### void glFlush()
- OpenGL 명령 큐를 flush
- 커맨드 큐에 명령이 없다는 것을 보장해주는 함수
- 대부분은 바로 실행되지만, 일부는 시간이 더 필요할 수도 있음

#### void glFinish()
- OpenGL 명령어 큐를 flush하고, 모두 완료되는 것을 확인 후에 return
- 주의: 시간이 오래 걸릴 수도 있음