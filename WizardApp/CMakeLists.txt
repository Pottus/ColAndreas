cmake_minimum_required (VERSION 2.6)

find_package(Qt5 COMPONENTS Core Gui Widgets)

if(NOT WIN32)
	set(CMAKE_C_FLAGS "")
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-write-strings")
	set(CMAKE_SHARED_LINKER_FLAGS "-fshort-wchar -shared")
endif(NOT WIN32)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/WizardApp" ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

file(GLOB Wizard_SRC
	"src/*.c"
	"src/*.cpp"
)

file(GLOB Wizard_MOC
	"src/Qt*.cpp"
)

file(GLOB Wizard_UI
	"ui/*.ui"
)

qt5_wrap_cpp(Qt_MOC ${Wizard_MOC})
qt5_wrap_ui(Qt_UI ${Wizard_UI})
qt5_add_resources(Qt_RES "Resources.qrc")
add_executable(WizardApp ${Wizard_SRC} ${Qt_MOC} ${Qt_UI} ${Qt_RES})

if(NOT WIN32)
	target_link_libraries(WizardApp -pthread Qt5::Core Qt5::Gui Qt5::Widgets)
else()
	target_link_libraries(WizardApp Qt5::Core Qt5::Gui Qt5::Widgets)
endif()
