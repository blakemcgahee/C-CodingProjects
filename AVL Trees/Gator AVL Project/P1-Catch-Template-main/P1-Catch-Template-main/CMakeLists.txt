cmake_minimum_required(VERSION 3.22)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Ensure 'src' and 'test' directories are in the include paths for all targets.
include_directories(src test)

# Define the executable for your main application
add_executable(Main
    src/main.cpp        # Your main application's entry point
    src/avl_tree.cpp    # Include the AVL tree implementation for Main executable
    src/avl_tree.h      # Include the AVL tree header for Main executable
)

# Define the executable for your tests.
# List ALL source files that are part of the Tests executable directly here.
add_executable(Tests
    test/test.cpp       # Your test file
    src/avl_tree.cpp    # Include the AVL tree implementation for Tests executable
    src/avl_tree.h      # Include the AVL tree header for Tests executable
)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(Tests)
