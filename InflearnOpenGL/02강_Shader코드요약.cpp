

// 3개의 OpenGL 데이터 구조체, 각각에 대해 ID number가 필요함
GLuint vert = 0;    // vertex shader ID number
GLuint frag = 0;    // fragment shader ID number
GLuint prog = 0;    // shader program ID number, 위 2개를 결합시킨 것

void initFunc()
{
    vert = glCreateShader(GL_VERTEX_SHADER);    // vertex 혹은 fragment 쉐이더 타입을 넣어주면 shaderID를 반환
    glShaderSource(vert, 1, &vertSource, NULL); // 이전에 작성한 버텍스 쉐이더 넣어주기
    // 보통은 char* source만 전달하기 때문에 두번째 매개변수는 1
    glCompileShader(vert);  // 버텍스 쉐이더 컴파일하여 .obj 파일 생성

    // fragment shader 역시 위와 동일한 방법으로 생성하며,
    // OpenGL 프로그램 전체로는 여러 개의 program이 존재 가능

    glCreateProgram(); // 쉐이더 프로그램 ID를 반환하고 이를 이용하여 그릴 대상을 정함

    glAttachShader(GLuint programID, GLuint shaderID);
    // 앞에서 만든 vert, frag 를 결합하려고 할 때 사용
    // 주의할 점은 반드시 vert와 frag 한 쌍으로 결합시켜야 하며, vertx 2개 이런식으로 하면 안됨
}

void drawFunc()
{
    glClear(GL_COLOR_BUFFER_BIT); // 화면 깨끗이 지우기

    // GLfloat vertPos[] = { -0.5f, -0.5f, 0.0f, 1.0f, ... 0.0f, 1.0f };
    // 아래 예시는 이미 vert + frag를 program으로 만들어서 돌리고 있는 경우
    // vertexPos 변수에다가 값을 주겠다는 의미, 그것의 위치를 찾는 함수(몇번 register에 가있는지)
    GLuint loc = glGetAttribLocation(prog, "vertexPos");
    // 찾았으면 그 데이터를 쓰겠다
    // C프로그램 Array와 연결
    glEnableVertexAttribArray(loc);
    // glDisableVertexAttribArray(loc); // 사용하지 않고 const 상수값으로 이용할 때 사용
    
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPos);
    // glVertexAttribPointer(Gluint index, GLint size, GLenum type, GLboolean normalized,
    // GLsizei stride, const GLvoid* pointer);
    // pointer -> 사용자가 작성한 배열의 시작 주소를 포인터로 전달
    // size : 1,2,3,4 -> float, vec2, vec3, vec4
    // 큰 배열을 전달할 것이기 때문에 몇개씩 끊어서 받을건지를 전달
    // type :GL_INT, GL_FLOAT 등

    // 실제로 그릴 함수
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawArray(GLenum mode, GLint first, GLsizei count);
    // mode : GL_POINTS, GL_LINES, GL_TRIANGLES
    // first : 전체 배열에서 얼마나 떨어진 부분부터 그릴지
    // count : total 몇개의 버텍스들을 사용할지
    // 1개의 array에 다양한 물체를 함께 저장 가능!
    glFinish();
}

// 각 꼭지점마다 RGB 값을 가진 삼각형 출력 예제
void drawFunc()
{
    // GLfloat vertPos[] = { xxxx }; 출력할 좌표
    // GLfloat vertColor[] = { xxxx }; rgb 값

    glClear(GL_COLOR_BUFFER_BIT);

    GLuint loc = glGetAttribLocation(prog, "aPos");
    // vertex shader 코드에서 'in vec4 aPos; // vertex position'에 해당
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPos);

    loc = glGetAttribLocation(prog, "aColor");
    // vertex shader 코드에서 'in vec4 aColor; // vertex color'에 해당
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FLASE, 0, vertColor);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 삼각형을 여러개 그릴꺼라면
    {
        // fragment는 위에서 설정해주었기 때문에 좌표만 따로 추가하면 됨
        // 이렇게 하나하나 추가하는 방법도 있지만 수백 수천개를 그릴때에는 좋은 방법이 아님
        glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPosSecond);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glFinish();
}


// uniform 변수 사용한 방법
void drawFunc()
{
    // provide the vertex attributs
    // 버텍스 어트리뷰트 설정
    GLuint locPos = glGetAttribLocation(prog, "aPos");
    glEnableVertexAttribArray(locPos);
    glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FLASE, 0, vertPos);

    // 프래그먼트 설정 생략

    // 첫번째 삼각형 그리기
    GLuint locMove = glGetUniformLocation(prog, "uMove");
    glUniform4f(locMove, -0.5f, -0.5f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 두번째 삼각형 그리기
    // 전역변수 uMove 값을 바꿔주어서 출력할 좌표를 변경
    glUniform4f(locMove, 0.0f, 0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}