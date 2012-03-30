cmake_minimum_required(VERSION 2.8)

# Set project's name
project(indigets)

# Setup version number
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Add sub-directories
add_subdirectory(src)
