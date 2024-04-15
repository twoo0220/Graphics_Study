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

#### GLint glGetUniformLocation(GLuint prog, const GLchar* name)

- name : uniform 변수 이름 문자열
- uniform 변수가 몇번 register를 쓰고 있는지에 대한 index 값을 반환
- 없다면 -1을 반환

#### void glUniform1f ~ 4f(GLint loc, GLfloat v0 ... , GLfloat v3)

- uniform 변수 값 설정
- vertex 변수마다 들어가는것이 아니고 전역 변수처럼 사용되어 모든 vertexShader가 이 값을 공유함

#### void glUniform1fv ~ 4fv(GLint loc, GLsizei count, const GLfloat* value);
  - 1~4차원 벡터를 컴포넌트로 제공
  - count가 1이라는 것은 uniform vec4 한개를 의미
  - count가 2fkaus, uniform vec4 uValues[2];를 의미
  - 이거 말고도 3i, 3iv, 3ui, 3uiv 등등 integer 버전도 있으며, glUniformMatrix4fv도 있음

#### void glDepthRangef(GLfloat nearVal, GLfloat farVal);
  - view volume의 z 좌표(-1.0 ~ +1.0)을 매핑시키는 window 좌표값 설정
  - -1.0 -> nearVal, +1.0 -> farVal로 매핑됨
  - 초기 값은 0.0 ~ 1.0
  - 주의 : 꼭 nearVal < farVal 일 필요는 없음

#### void glClearDepth(GLdouble depth);
  - Z-buffer를 clear 시키는 값 설정
  - 초기 값은 1.0

#### void glDrawArrays(GLenum mode, GLint first, GLsizei count);
  - render primitives from array data
  - mode = GL_POINTS, GL_LINES, GL_TRIANSGLES, ...
  - first : start index in your attribute arrays
  - count : number of vertices in your attribute arrays

#### void glPointSize(GLfloat size);
  - 포인트의 크기 rasterized points 지름 설정
  - 초기값은 1

#### void glLineWidth(GLfloat width);
  - rasterized lines 폭 설정
  - 초기값은 1