cmake_minimum_required(VERSION 3.22)
project(ImageCompressor)

message("QT_ASSUME_STDERR_HAS_CONSOLE  = ${QT_ASSUME_STDERR_HAS_CONSOLE}")

add_subdirectory(utility)
add_subdirectory(compression_library)
add_subdirectory(frontend)
