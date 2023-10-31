cmake_minimum_required(VERSION 3.26)
project(opengl_playground)

set(CMAKE_CXX_STANDARD 11)

# Collect all source files from the 'engine' directory
file(GLOB ENGINE_SOURCES "engine/*.cpp" "engine/*.h")

add_executable(opengl_playground main.cpp ${ENGINE_SOURCES})
add_executable(exercise_1 exercise_1.cpp ${ENGINE_SOURCES})
add_executable(shader_lesson shader_lesson.cpp ${ENGINE_SOURCES})
add_executable(texture_lesson texture_lesson.cpp ${ENGINE_SOURCES})

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(glm_DIR libs/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(opengl_playground glfw ${OPENGL_gl_LIBRARY} glm::glm)
target_link_libraries(exercise_1 glfw ${OPENGL_gl_LIBRARY} glm::glm)
target_link_libraries(shader_lesson glfw ${OPENGL_gl_LIBRARY} glm::glm)
target_link_libraries(texture_lesson glfw ${OPENGL_gl_LIBRARY} glm::glm)

add_custom_command(TARGET texture_lesson POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:shader_lesson>/shaders)
add_custom_command(TARGET texture_lesson POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:texture_lesson>/textures)
