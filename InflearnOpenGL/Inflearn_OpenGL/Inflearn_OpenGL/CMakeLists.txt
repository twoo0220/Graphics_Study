cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Inflearn_OpenGL.cpp")

target_link_libraries(${PROJECT_NAME}
	${GLFW_LIBRARIES}
	glfw
	libglew_static
	OpenGL::GL
)

# Add Glad libraries
#set(GLAD_DIR ${LIB_DIR}/glad)
#add_library(glad ${GLAD_DIR}/src/glad.c)
#target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
#target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
#target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})

#set(GLM_DIR ${LIB_DIR}/glm)
#include_directories(${GLM_DIR})