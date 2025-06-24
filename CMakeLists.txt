cmake_minimum_required(VERSION 3.14)
project(broadLocalization VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable verbose makefile
set(CMAKE_VERBOSE_MAKEFILE ON)


# Configure header
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/broadLocalization.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/broadLocalizationConfig.h
)

# Add subdirectories
add_subdirectory(src)