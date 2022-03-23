project(runtime)
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
find_package (Threads)

include_directories(include)
file(GLOB SOURCES 
    src/*cpp
    include/*.hpp
    )
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
${CMAKE_THREAD_LIBS_INIT}
)