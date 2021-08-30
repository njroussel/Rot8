cmake_minimum_required(VERSION 3.0)
project(Rot8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

message("Build type: ${CMAKE_BUILD_TYPE}")

# Good practices
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wshadow-all")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wconversion")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")

# Enable all instruction subsets supported by the local machine
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(Threads REQUIRED)

add_subdirectory(ext)

add_executable(rot8
    # Header files
    include/rot8/renderable.h
    include/rot8/helpers/shader.h
    include/rot8/helpers/vao.h
    include/rot8/models/triangle.h
    include/rot8/window.h

    # Source files
    src/renderable.cpp
    src/helpers/shader.cpp
    src/helpers/vao.cpp
    src/models/triangle/triangle.cpp
    src/window.cpp
    src/main.cpp
    )

target_include_directories(rot8 SYSTEM PRIVATE
    # Rot8 include files
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # GLFW OpenGL/Vulkan graphcis library framework
    ${GLFW_INCLUDE_DIR}
    # GLAD OpenGL function loader
    ${GLAD_INCLUDE_DIR}
    # Kr8md Vectorization (SIMD) library
    ${KR8MD_INCLUDE_DIR}
    )

target_link_libraries(rot8 glfw glad)
