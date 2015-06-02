if (WIN32)
  set (PROJECT_WINVER "0x0601" CACHE STRING "Windows version maro. Default is 0x0601 - win7, user can reset")
  add_definitions (-D_WIN32_WINNT=${PROJECT_WINVER})
endif ()

include_directories("${PROJECT_SOURCE_DIR}/../../boost_1_58_0")
include_directories("${PROJECT_SOURCE_DIR}/../../gce_install_boost_1.58_debug/include")
include_directories("${PROJECT_SOURCE_DIR}/../../lua_install_5.15_debug/include")
include_directories("${PROJECT_SOURCE_DIR}/../../OpenSSL-Build/Build-OpenSSL-VC-64-dbg/include")
include_directories("${PROJECT_SOURCE_DIR}/Library")
include_directories("${PROJECT_SOURCE_DIR}/Common")
include_directories("${PROJECT_SOURCE_DIR}/../libs/json/include")
include_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL/include/x64")
include_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL Connector C++ 1.1.2/include/x64")
include_directories("${PROJECT_SOURCE_DIR}/../libs/redis-cplusplus-client/include")


link_directories("${CMAKE_INSTALL_PREFIX}/lib")
link_directories("${PROJECT_SOURCE_DIR}/../../boost_1_58_0/stage/lib")
link_directories("${PROJECT_SOURCE_DIR}/../../lua_install_5.15_debug/lib")
link_directories("${PROJECT_SOURCE_DIR}/../../OpenSSL-Build/Build-OpenSSL-VC-64-dbg/lib")
link_directories("${PROJECT_SOURCE_DIR}/../libs/json/lib/x64/")
link_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL/lib/x64/")
link_directories("${PROJECT_SOURCE_DIR}/../libs/MySQL Connector C++ 1.1.2/lib/x64/")
link_directories("${PROJECT_SOURCE_DIR}/../libs/redis-cplusplus-client/lib/x64/")

file (GLOB_RECURSE GAMESERVER_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file (GLOB_RECURSE GAMESERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Bin)

add_executable(GameServer ${GAMESERVER_HEADER_FILES} ${GAMESERVER_SOURCE_FILES})

target_link_libraries(GameServer Library)
target_link_libraries(GameServer Common)
target_link_libraries(GameServer lua)
target_link_libraries(GameServer ssleay32)
target_link_libraries(GameServer libeay32)

install (TARGETS GameServer DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/MirServerConfig.h" DESTINATION include)