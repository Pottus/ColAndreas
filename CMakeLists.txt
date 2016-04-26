cmake_minimum_required (VERSION 2.8.11)

project(ColAndreas)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
find_package(Bullet REQUIRED)

set(CA_VERSION "v1.4.0")
set(CA_DATABASE_VERSION 2)
add_definitions(-DCA_VERSION="${CA_VERSION}" -DCA_DATABASE_VERSION=${CA_DATABASE_VERSION})

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING " " FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(BuildWizard "Compile the Wizard application." OFF)

if(WIN32)
	add_definitions(-DWIN32 -D_WIN32)

	set(CMAKE_C_FLAGS "/nologo /EHsc /MT")
	set(CMAKE_CXX_FLAGS "/nologo /EHsc /MT")
	set(CMAKE_SHARED_LINKER_FLAGS "/NOLOGO /MACHINE:X86 /DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/src/ColAndreas.def\"")

	set(CMAKE_C_FLAGS_DEBUG "/Od /Zi")
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
	set(CMAKE_C_FLAGS_RELEASE "/Ox")
	set(CMAKE_CXX_FLAGS_RELEASE "/Ox")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ox /Zi")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ox /Zi")

	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/DEBUG")
else()
	add_definitions(-DLINUX)

	set(CMAKE_C_FLAGS "-m32")
	set(CMAKE_CXX_FLAGS "-m32 -std=c++11 -Wno-write-strings")
	set(CMAKE_SHARED_LINKER_FLAGS "-m32 -fshort-wchar -shared")

	set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
	set(CMAKE_C_FLAGS_RELEASE "-O3 -g0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g0")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g3")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g3")

	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-O3 -s")
endif(WIN32)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src/SDK" "${CMAKE_CURRENT_SOURCE_DIR}/src/SDK/amx" ${BULLET_INCLUDE_DIR})

file(GLOB CA_Source
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SDK/*.cpp"
)

add_library(ColAndreas SHARED ${CA_Source})
set_target_properties(ColAndreas PROPERTIES PREFIX "")
target_link_libraries(ColAndreas ${BULLET_LIBRARIES})

if(NOT WIN32 AND ${BULLET_COLLISION_LIBRARY} MATCHES ".a$")
	set_target_properties(ColAndreas PROPERTIES SUFFIX "_static.so")
endif()

if(BuildWizard)
	add_subdirectory(WizardApp)
endif()
