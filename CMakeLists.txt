cmake_minimum_required(VERSION 2.6)
project(SpacePirates)

# enable c++11, MSVC has it by default
if(NOT MSVC)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
 	   message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different 	C++ compiler.")
	endif()
endif()

# Find cmake modules like FindSDL2.cmake, etc
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SpacePirates_SOURCE_DIR}/cmake")

# Get SDL2 libs
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(SpacePirates Block.h Block.cpp GameObject.h GameObject.cpp Gold.h Gold.cpp Graphics.h Graphics.cpp Input.h Input.cpp Level.h Level.cpp main.cpp Platform.h Platform.cpp RigidBody.h RigidBody.cpp Ship.h Ship.cpp Time.h Time.cpp Texture.h Texture.cpp)

target_link_libraries(SpacePirates ${SDL2_LIBRARY})
target_link_libraries(SpacePirates ${SDL2_TTF_LIBRARY})

if(MSVC)
	get_filename_component(SDL2_TTF_LIBRARY_DIR ${SDL2_TTF_LIBRARY} DIRECTORY)
	add_custom_command(TARGET SpacePirates POST_BUILD
	                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
	                   "${SDL2_TTF_LIBRARY_DIR}/SDL2_ttf.dll" $<TARGET_FILE_DIR:SpacePirates>
	                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
	                   "${SDL2_TTF_LIBRARY_DIR}/libfreetype-6.dll" $<TARGET_FILE_DIR:SpacePirates>
	                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
	                   "${SDL2_TTF_LIBRARY_DIR}/zlib1.dll" $<TARGET_FILE_DIR:SpacePirates>
	                   )
endif()

add_custom_command(TARGET SpacePirates POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/levels ${CMAKE_BINARY_DIR}/levels
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/ships ${CMAKE_BINARY_DIR}/ships
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/DejaVuSans-ExtraLight.ttf ${CMAKE_BINARY_DIR}/DejaVuSans-ExtraLight.ttf
                   )
