cmake_minimum_required(VERSION 3.0)
project(Rot8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message("Build type: ${CMAKE_BUILD_TYPE}")

# Good practices
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wshadow-all")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wconversion")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")

# Enable all instruction subsets supported by the local machine
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(Threads REQUIRED)

add_subdirectory(ext)

add_executable(rot8
    # Header files
    # Source files
    src/main.cpp
    )

target_include_directories(rot8 SYSTEM PRIVATE
    # Rot8 include files
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # Kr8md Vectorization (SIMD) library
    ${KR8MD_INCLUDE_DIR}
    )

target_link_libraries(rot8 glfw glad)
