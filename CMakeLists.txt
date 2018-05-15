cmake_minimum_required (VERSION 3.6)
project (pgcache)

set(THREADS_PREFER_PTHREAD_FLAG 	ON)
set(CMAKE_CXX_STANDARD 			11)
set(Boost_USE_MULTITHREADED 		ON)
set(BOOST_ROOT "/usr/local/include/boost")
find_package(Boost 1.67.0 REQUIRED COMPONENTS program_options log system)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(pgcache src/main.C)
target_link_libraries(pgcache Threads::Threads ${Boost_LIBRARIES})
