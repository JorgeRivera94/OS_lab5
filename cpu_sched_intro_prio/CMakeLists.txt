cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-03 -DNDEBUG -s")
set(CMAKE_C_FLAGS "-std=c99")

# Set the project name
project(cpu_sched_prio)

# Include the directory for header files
include_directories(include)

# Add the executable
add_executable(${CMAKE_PROJECT_NAME} 
  src/cpu_sched_prio.c
	src/main.c)

target_link_libraries(${CMAKE_PROJECT_NAME}
    )
