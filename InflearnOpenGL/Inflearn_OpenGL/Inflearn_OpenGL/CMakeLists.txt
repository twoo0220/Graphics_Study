cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"Inflearn_OpenGL.cpp"
	"include/Renderer.h"
	"src/Renderer.cpp"
)

target_link_libraries(${PROJECT_NAME}
	${GLFW_LIBRARIES}
	glfw
	libglew_static
	#glad
	OpenGL::GL
)
