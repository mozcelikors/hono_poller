cmake_minimum_required (VERSION 2.8.11)
project (hono_poller)
#For find_package packages, export someextlib_DIR=/path/to/..
#find_package (someextlib REQUIRED)

#Where to put binary files after "make"
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#Where to put library files after "make"
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

#Include directory
include_directories (${PROJECT_BINARY_DIR})

add_library (hono_interaction SHARED hono_interaction.cpp)

add_executable(hono_poller hono_poller.cpp)

target_link_libraries(hono_poller hono_interaction)

#Install binary, shared library, static library (archives)
install (TARGETS hono_poller hono_interaction
  RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/build
  LIBRARY DESTINATION /usr/lib 
  ARCHIVE DESTINATION /usr/lib)
