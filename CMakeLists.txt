cmake_minimum_required(VERSION 3.10)

project(BasicRenderer)

# Add OpenGL
find_package(OpenGL REQUIRED)

# Add glfw
set(GLFW_DIR lib/glfw)
add_subdirectory(${GLFW_DIR})

# Add glad
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/lib/glad)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

# Create Executable
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)
add_executable(BasicRenderer ${SOURCES})

target_include_directories(BasicRenderer PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Add glm 
target_include_directories(BasicRenderer PRIVATE ${CMAKE_SOURCE_DIR}/lib/glm)

# Link libraries
target_link_libraries(BasicRenderer PRIVATE glad glfw OpenGL::GL)
