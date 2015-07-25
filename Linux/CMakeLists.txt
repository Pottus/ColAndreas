cmake_minimum_required (VERSION 2.6)

project(ColAndreas)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
find_package(Bullet REQUIRED)

add_definitions(-DLINUX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING " " FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_FLAGS "-m32 -std=c++11 -Wno-write-strings")
set(CMAKE_SHARED_LINKER_FLAGS "-m32 -fshort-wchar -shared")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3 -g0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -g0")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS} -O2 -g3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O2 -g3")

set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} -O3 -s")

set(CA_ProjectRoot "${CMAKE_CURRENT_SOURCE_DIR}/..")

include_directories("${CA_ProjectRoot}/src" "${CA_ProjectRoot}/src/SDK" "${CA_ProjectRoot}/src/SDK/amx" ${BULLET_INCLUDE_DIR})

file(GLOB CA_Source
	"${CA_ProjectRoot}/src/*.cpp"
	"${CA_ProjectRoot}/src/SDK/*.cpp"
)

add_library(ColAndreas SHARED ${CA_Source})
set_target_properties(ColAndreas PROPERTIES PREFIX "")
target_link_libraries(ColAndreas ${BULLET_LIBRARIES})

if(${BULLET_COLLISION_LIBRARY} MATCHES ".a$")
	set_target_properties(ColAndreas PROPERTIES SUFFIX "_static.so")
endif()
