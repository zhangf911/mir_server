#cmake��������汾��
cmake_minimum_required(VERSION 3.0)

#��Ŀ����
project(MirServer)

#���ù��̰汾��
set (MirServer_VERSION_MAJOR 0)
set (MirServer_VERSION_MINOR 1)

#����һ��ͷ�ļ���ͨ������Դ�����д���һЩCMake����
configure_file (
"${PROJECT_SOURCE_DIR}/MirServerConfig.h.in"
"${PROJECT_BINARY_DIR}/MirServerConfig.h"
)

# ���������ļ�����ӵ������ļ�������·���У��������ǿ����ҵ�ConquerorConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#���̰�װĿ¼
set(CMAKE_INSTALL_PREFIX ../mir_server_install)

if (WIN32)
  # Set vc bigobj
  if (${CMAKE_GENERATOR} MATCHES "Visual Studio *")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
  endif ()
endif ()

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -static")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -static")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

if (WIN32)
  # Set >= vc10 SAFESEH to NO
  if (${CMAKE_GENERATOR} MATCHES "Visual Studio 1*")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
  endif ()
endif()

#����ӹ���Ŀ¼
add_subdirectory(Common)
add_subdirectory(GateServer)
add_subdirectory(GameServer)
add_subdirectory(Library)