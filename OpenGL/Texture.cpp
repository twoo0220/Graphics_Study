#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;

	// Texture
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// 텍스처가 바인딩 되었으므로 이것저것 설정해줄 수 있는데, 먼저 이미지를 확대/축소할 때 처리 방법을 선택
	// GL_NEAREST 픽셀 아트로 작업할 때 선호, 모든 픽셀을 유지
	// GL_LINEAR 주변 픽셀에 따라 새 픽셀을 생성, 일반적으로 이미지가 흐릿해짐
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 두 번째 설정은 텍스처를 반복하는 방법
	// GL_REPEAT 단순 반복
	// GL_MIRRORED_REPEAT 반복할 때마다 미러링
	// GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER 이미지의 테두리를 늘림, 늘리고 선택한 단색을 이미지 외부에 배치
	// 한 축에만 적용되므로 수식 축에는 텍스처가 반복되도록 하고 수평 축에는 단색만 가지도록 할 수도 있음
	// 

	// x,y,z 축에 해당하는 이름은 s, t, r
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
