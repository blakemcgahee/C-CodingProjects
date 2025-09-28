cmake_minimum_required(VERSION 3.22)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

# Define flags for GCC/Clang (e.g., Gradescope environment)
set(GCC_CLANG_FLAGS "-Wall -Wextra -Werror")

# Define flags for MSVC (e.g., Visual Studio environment)
set(MSVC_FLAGS "/W4 /WX")

# Apply compiler-specific flags to CMAKE_CXX_FLAGS
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "MSVC compiler detected. Applying MSVC-specific flags.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_FLAGS}")
else()
    message(STATUS "GCC/Clang compiler detected. Applying GCC/Clang-specific flags.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CLANG_FLAGS}")
endif()

include_directories(src)

add_executable(Main
        src/main.cpp
        src/program.cpp # NEW: Now includes program.cpp for runProgram definition
        src/AdjacencyList.h src/AdjacencyList.cpp
        )
        
# These tests can use the Catch2-provided main
add_executable(Tests
        test/test.cpp
        src/program.cpp # NEW: Now includes program.cpp for runProgram definition
        src/AdjacencyList.h src/AdjacencyList.cpp
        # REMOVED: src/main.cpp from here to avoid main() conflict
        )
        
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) # Link Catch2 to the test.cpp file

# Pull in desired version of Catch2 through CMake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Note: Comment out below section if using CLion.
include(CTest)
include(Catch)
catch_discover_tests(Tests) # Must be named the same as my test executable
