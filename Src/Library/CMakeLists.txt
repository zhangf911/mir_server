if (WIN32)
  set (PROJECT_WINVER "0x0601" CACHE STRING "Windows version maro. Default is 0x0601 - win7, user can reset")
  add_definitions (-D_WIN32_WINNT=${PROJECT_WINVER})
endif ()

include_directories("${PROJECT_BINARY_DIR}/../../boost_1_58_0")

file (GLOB_RECURSE LIBRARY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file (GLOB_RECURSE LIBRARY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(Library STATIC ${LIBRARY_HEADER_FILES} ${LIBRARY_SOURCE_FILES})