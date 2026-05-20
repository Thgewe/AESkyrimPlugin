cmake_minimum_required(VERSION 3.21)

project(AESkyrimPlugin VERSION 1.0.0 LANGUAGES CXX)

set(ENABLE_SKYRIM_AE ON )
set(ENABLE_SKYRIM_SE OFF)
set(ENABLE_SKYRIM_VR OFF)
set(BUILD_TESTS      OFF)

add_subdirectory(extern/CommonLibSSE-NG)

add_library(${PROJECT_NAME} SHARED src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)