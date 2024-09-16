cmake_minimum_required(VERSION 3.12)
project(Inflearn_OpenGL)

set(CMAKE_CXX_STANDARD 20)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("OS is Windows")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("OS is Linux")
	find_package(OpenGL REQUIRED)
	if (NOT OPENGL_FOUND)
		message("Error: OpenGL not found")
	endif(NOT OPENGL_FOUND)
	set(GL_LIBRARY GL GLU X11)
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INDLUCE_DIR})

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Inflearn_OpenGL.cpp")

# Add glfw libraries
set(GLFW_DIR ${LIB_DIR}/glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME}
	${GLFW_LIBRARIES}
	glfw
	OpenGL::GL
)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# Add Glad libraries
#set(GLAD_DIR ${LIB_DIR}/glad)
#add_library(glad ${GLAD_DIR}/src/glad.c)
#target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
#target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
#target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})

#set(GLM_DIR ${LIB_DIR}/glm)
#include_directories(${GLM_DIR})