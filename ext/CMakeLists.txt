## Rot8
set(BUILD_SHARED_LIBS ON CACHE BOOL " " FORCE)


## GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_INSTALL OFF CACHE BOOL " " FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL " " FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw")

set(GLFW_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

set(CompilerFlags ${CompilerFlags}
    GLFW_INCLUDE_DIR)


## GLAD
set(GLAD_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

set(CompilerFlags ${CompilerFlags}
    GLAD_INCLUDE_DIR)

add_library(glad SHARED "${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c")
target_include_directories(glad PRIVATE ${GLAD_INCLUDE_DIR})


## GLM
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glm")

set(GLM_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)

set(CompilerFlags ${CompilerFlags}
    GLM_INCLUDE_DIR)


## Kr8md
set(KR8MD_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/kr8md/include)

set(CompilerFlags ${CompilerFlags}
    KR8MD_INCLUDE_DIR)


## STB
set(STB_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/stb)

set(CompilerFlags ${CompilerFlags}
    STB_INCLUDE_DIR)


## Rot8
foreach(CompilerFlag ${CompilerFlags})
    set(${CompilerFlag} "${${CompilerFlag}}" PARENT_SCOPE)
endforeach()
