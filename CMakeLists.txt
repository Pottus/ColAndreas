cmake_minimum_required (VERSION 2.8.11)

project(ColAndreas)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
find_package(Bullet REQUIRED)

execute_process(COMMAND git describe --tags --long WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE CA_VERSION_RESULT OUTPUT_VARIABLE CA_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT CA_VERSION_RESULT EQUAL 0)
	message(FATAL_ERROR "Failed to get version string.")
endif()

string(REGEX REPLACE "^v?([0-9]+)\\..*" "\\1" CA_VERSION_MAJOR "${CA_VERSION}")
string(REGEX REPLACE "^v?[0-9]+\\.([0-9]+).*" "\\1" CA_VERSION_MINOR "${CA_VERSION}")
string(REGEX REPLACE "^v?[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CA_VERSION_PATCH "${CA_VERSION}")
string(REGEX REPLACE "^v?[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]+-([0-9A-Za-z]+).*" "\\1" CA_VERSION_CODE "${CA_VERSION}")
set(CA_DATABASE_VERSION 2)
add_definitions(-DCA_VERSION="v${CA_VERSION_MAJOR}.${CA_VERSION_MINOR}.${CA_VERSION_PATCH}-${CA_VERSION_CODE}" -DCA_VERSION_MAJOR=${CA_VERSION_MAJOR} -DCA_VERSION_MINOR=${CA_VERSION_MINOR} -DCA_VERSION_PATCH=${CA_VERSION_PATCH} -DCA_DATABASE_VERSION=${CA_DATABASE_VERSION})

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
