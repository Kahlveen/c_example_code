cmake_minimum_required (VERSION 2.8.11)
project(pcre_example)

set(LIBRARY_VERSION_MAJOR 1)
set(LIBRARY_VERSION_MINOR 1)
set(LIBRARY_VERSION_PATCH 1)
Set (LIBRARY_VERSION_STRING ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})

set(CMAKE_BUILD_TYPE Release) # Debug, Release, RelWithDebInfo

# RPM configurations
set(CPACK_GENERATOR “RPM”)
set(CPACK_RPM_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_RPM_PACKAGE_VERSION ${LIBRARY_VERSION_STRING})
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_SUMMARY “pcre”)
set(CPACK_RPM_PACKAGE_GROUP “Nil”)
set(CPACK_RPM_PACKAGE_LICENSE “Nil”)
set(CPACK_RPM_PACKAGE_VENDOR “Nil”)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME “${CPACK_RPM_PACKAGE_NAME}-${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}-${CMAKE_SYSTEM}”)
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION “/usr/local/” “/usr/local/include” “/usr/local/lib”)
set(CPACK_RPM_PACKAGE_REQUIRES “libpcre-devel >= 1.5”)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS src/*.h)

# Header search path (-I)
include_directories("/usr/local/include" "/usr/include")

# Library search paths (-L)
LINK_DIRECTORIES(“/usr/local/lib” “/usr/lib”)

#add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pcre)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib/)
install(FILES ${HEADERS} DESTINATION /usr/local/include/some_folder) # will auto create folder if using RPM



