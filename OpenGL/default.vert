// Vertex Shader source code
#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Textures
layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

// Outputs the color for the Fragment Shader
out vec3 color;
out vec2 texCoord;

out vec3 Normal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos,1.0f));

	//gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	color = aColor;
	texCoord = aTex;

	Normal = aNormal;
}


// Layouts help OpenGL read the Vertex Datait receives
// In this case, we say that on the 0th layout there is a vec3 datatype for positions
// Fragment Shader는 색상을 담당하는 Shader이기 때문에 Vertex Shader의 색상을 Fragment Shader로 출력해야 함
// 그렇게 하려면 color라는 이름의 vec3을 출력하고 main 에서 정점 배열에서 가져온 aColor와 동일하게 만들면 됨
// Fragment shader에서 vec3을 입력으로 받으면 됨.

// uniform 을 사용하지 않는다면 절대 선언하지 말것.
// OpenGL이 유니폼을 자동으로 삭제하여 오류가 발생할 수 있기 때문