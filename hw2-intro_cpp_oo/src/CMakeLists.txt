# Glob source files
set(CMAKE_CXX_STANDARD 14)
file(GLOB sources "*.cc")

add_executable(main ${sources})
