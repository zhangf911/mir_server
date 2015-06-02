if (WIN32)
  set (PROJECT_WINVER "0x0601" CACHE STRING "Windows version maro. Default is 0x0601 - win7, user can reset")
  add_definitions (-D_WIN32_WINNT=${PROJECT_WINVER})
endif ()

include_directories("${PROJECT_SOURCE_DIR}/../../boost_1_58_0")
include_directories(${PROJECT_SOURCE_DIR}/Library)
include_directories("${PROJECT_SOURCE_DIR}/../libs/json/include")
include_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL/include/x64")
include_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL Connector C++ 1.1.2/include/x64")
include_directories("${PROJECT_SOURCE_DIR}/../libs/redis-cplusplus-client/include")

file (GLOB_RECURSE COMMON_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file (GLOB_RECURSE COMMON_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(Common STATIC ${COMMON_HEADER_FILES} ${COMMON_SOURCE_FILES})

install (TARGETS Common DESTINATION bin)
install (FILES ${COMMON_HEADER_FILES} DESTINATION include)