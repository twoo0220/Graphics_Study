// Vertex Shader source code
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aColor;
}


// Layouts help OpenGL read the Vertex Datait receives
// In this case, we say that on the 0th layout there is a vec3 datatype for positions
// Fragment Shader는 색상을 담당하는 Shader이기 때문에 Vertex Shader의 색상을 Fragment Shader로 출력해야 함
// 그렇게 하려면 color라는 이름의 vec3을 출력하고 main 에서 정점 배열에서 가져온 aColor와 동일하게 만들면 됨
// Fragment shader에서 vec3을 입력으로 받으면 됨.