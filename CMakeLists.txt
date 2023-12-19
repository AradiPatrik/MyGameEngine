cmake_minimum_required(VERSION 3.27)
project(opengl_playground)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files from the 'engine' directory
file(GLOB ENGINE_SOURCES "engine/*.cpp" "engine/*.h")
file(GLOB LIGHTING_SOURCES "tutorials/lighting/*.cpp" "tutorials/lighting/*.h")

add_executable(opengl_playground main.cpp ${ENGINE_SOURCES})
add_executable(exercise_1 exercise_1.cpp ${ENGINE_SOURCES})
add_executable(shader_lesson shader_lesson.cpp ${ENGINE_SOURCES})
add_executable(texture_lesson texture_lesson.cpp ${ENGINE_SOURCES})
add_executable(transformations transformations.cpp ${ENGINE_SOURCES})
add_executable(coordinate_systems coordinate_systems.cpp ${ENGINE_SOURCES})
add_executable(moving_around moving_around.cpp ${ENGINE_SOURCES})
add_executable(snake games/snake/SnakeGame.cpp ${ENGINE_SOURCES} games/snake/Snake.cpp games/snake/Snake.h
        games/snake/GameBoard.cpp
        games/snake/GameBoard.h
        games/snake/Food.cpp
        games/snake/Food.h
)
add_executable(colors ${LIGHTING_SOURCES} ${ENGINE_SOURCES})

if (WIN32)
    find_package(glad CONFIG REQUIRED)
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(glm_DIR libs/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})

# Link against OpenGL and glm for all platforms
foreach (target
        opengl_playground
        exercise_1
        shader_lesson
        texture_lesson
        transformations
        coordinate_systems
        moving_around
        snake
        colors)

    target_link_libraries(${target} PRIVATE glfw ${OPENGL_gl_LIBRARY} glm::glm)

    # Add glad only for Windows
    if (WIN32)
        target_link_libraries(${target} PRIVATE glad::glad)
    endif ()
endforeach ()

function(copy_resources_to_target target_name)
    add_custom_target(copy_shaders_${target_name} ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${target_name}>/shaders
            COMMENT "Copying shaders to build directory for ${target_name}"
    )

    add_custom_target(copy_textures_${target_name} ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:${target_name}>/textures
            COMMENT "Copying textures to build directory for ${target_name}"
    )

    add_dependencies(${target_name} copy_shaders_${target_name})
    add_dependencies(${target_name} copy_textures_${target_name})
endfunction()

copy_resources_to_target(opengl_playground)
copy_resources_to_target(exercise_1)
copy_resources_to_target(shader_lesson)
copy_resources_to_target(texture_lesson)
copy_resources_to_target(transformations)
copy_resources_to_target(coordinate_systems)
copy_resources_to_target(moving_around)
copy_resources_to_target(snake)
copy_resources_to_target(colors)
