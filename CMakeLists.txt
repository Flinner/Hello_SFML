cmake_minimum_required(VERSION 3.7) # not sure of version...
set(CMAKE_CXX_STANDARD 20)
project(VGA_SIMULATOR LANGUAGES CXX)

# Enable compile commands JSON for editor support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

### SFML https://github.com/SFML/cmake-sfml-project/blob/master/CMakeLists.txt

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)



add_executable(spiral src/spiral.cpp)
add_executable(walking src/walking.cpp)

target_link_libraries(spiral PRIVATE sfml-graphics)
target_compile_features(spiral PRIVATE cxx_std_20)
target_link_libraries(walking PRIVATE sfml-graphics)
target_compile_features(walking PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET spiral
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:spiral>
        VERBATIM)
endif()

if(WIN32)
    add_custom_command(
        TARGET walking
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:walking>
        VERBATIM)
endif()
