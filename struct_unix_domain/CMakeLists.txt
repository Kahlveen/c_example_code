cmake_minimum_required (VERSION 2.8.11)
project(unix_domain)

set(LIBRARY_VERSION_MAJOR 1)
set(LIBRARY_VERSION_MINOR 1)
set(LIBRARY_VERSION_PATCH 1)
Set (LIBRARY_VERSION_STRING ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})

set(CMAKE_BUILD_TYPE Release) # Debug, Release, RelWithDebInfo

file(GLOB CLIENT_SRC src/client.c src/cli.c)
file(GLOB SERVER_SRC src/server.c src/cli.c)

# Header search path (-I)
include_directories("/usr/local/include/" "/usr/include")

# Library search paths (-L)
LINK_DIRECTORIES(“/usr/local/lib” “/usr/lib”)

add_executable(${PROJECT_NAME}_c ${CLIENT_SRC})
add_executable(${PROJECT_NAME}_s ${SERVER_SRC})

