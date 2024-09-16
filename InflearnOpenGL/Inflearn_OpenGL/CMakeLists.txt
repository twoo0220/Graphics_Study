cmake_minimum_required (VERSION 3.8)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("OS is Windows")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("OS is Linux")
	set(GL_LIBRARY GL GLU X11)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Inflearn_OpenGL")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INDLUCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/Inflearn_OpenGL/lib)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory(${LIB_DIR}/glfw)
add_subdirectory(${LIB_DIR}/glew)
add_subdirectory ("Inflearn_OpenGL")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${LIB_DIR}/glfw/include
		${LIB_DIR}/glew/include
)
