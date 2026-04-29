# Setup project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(SigmarsGardenSolver)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fno-math-errno -fno-trapping-math -march=native")
#set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -fno-math-errno -fno-trapping-math -march=native")

# set build type variable in preprocessor
if(CMAKE_BUILD_TYPE)
    string(TOUPPER "${CMAKE_BUILD_TYPE}" _upper_build_type)
    add_compile_definitions(BUILD_${_upper_build_type}=1)
endif()

# add include dir
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# add libraries
link_directories(${PROJECT_SOURCE_DIR}/lib)

# add sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

# build library
add_library(sigmarsolver SHARED ${sources} ${headers})
set_property(TARGET sigmarsolver PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(sigmarsolver PROPERTIES PREFIX "lib")
#target_link_libraries(sigmarsolver)

# build test binary
add_executable(test test.cpp ${headers})
target_link_libraries(test sigmarsolver)
add_executable(test2 test2.cpp ${headers})
target_link_libraries(test2 sigmarsolver)
