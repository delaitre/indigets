cmake_minimum_required(VERSION 2.8)

# All header files that should be treated with moc
set(MOC_HDRS
    tools.hpp
    steptickengine.hpp
    abstractscale.hpp
    linearscale.hpp
    circularscale.hpp
    fixedtickengine.hpp
    ellipse.hpp
    scalezone.hpp
    valuemapper.hpp
    tickengine.hpp
    linearvaluemapper.hpp
    standardscalezone.hpp
    plugin.hpp
    timestamptickengine.hpp
)

# All source files
set(SRCS
    qmldir
    tools.hpp
    tools.cpp
    steptickengine.hpp
    steptickengine.cpp
    abstractscale.hpp
    abstractscale.cpp
    linearscale.hpp
    linearscale.cpp
    circularscale.hpp
    circularscale.cpp
    fixedtickengine.hpp
    fixedtickengine.cpp
    ellipse.hpp
    ellipse.cpp
    scalezone.hpp
    scalezone.cpp
    valuemapper.hpp
    valuemapper.cpp
    tickengine.hpp
    tickengine.cpp
    linearvaluemapper.hpp
    linearvaluemapper.cpp
    standardscalezone.hpp
    standardscalezone.cpp
    plugin.hpp
    plugin.cpp
    timestamptickengine.cpp
    timestamptickengine.hpp
)

# Since it is a QML plugin, we need to output its binaries to a "indigets" sub-directory
if(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(INDIGETS_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    set(INDIGETS_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()
get_filename_component(INDIGETS_DIRECTORY "${INDIGETS_DIRECTORY}" ABSOLUTE)
set(INDIGETS_DIRECTORY "${INDIGETS_DIRECTORY}/indigets")
file(MAKE_DIRECTORY "${INDIGETS_DIRECTORY}")

# Copy the qmldir file
add_custom_command(OUTPUT "${INDIGETS_DIRECTORY}/qmldir"
                   COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/src/qmldir" "${INDIGETS_DIRECTORY}"
                   MAIN_DEPENDENCY "${PROJECT_SOURCE_DIR}/src/qmldir"
)

# Add the project's source directory to the include search path
include_directories("${PROJECT_SOURCE_DIR}/core")

# Find external libraries
find_package(Qt4 4.7.0 COMPONENTS QtCore QtGui QtDeclarative REQUIRED)

# (QT_USE_FILE is a variable defined by find_package(Qt4) that contains a path to CMake script)
include(${QT_USE_FILE})

# Run moc on needed files
set(MOC_SRCS) # clear the variable as the next command doesn't do it
QT4_WRAP_CPP(MOC_SRCS ${MOC_HDRS})
source_group(moc FILES ${MOC_SRCS})

# Create the target
add_library(indigets MODULE ${SRCS} ${MOC_SRCS})

# Set target version
set_target_properties(indigets PROPERTIES VERSION ${VERSION})

# Since this plugin will be loaded at runtime, it must have a consistent name: remove the platform-specific prefix if any
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set_target_properties(indigets PROPERTIES PREFIX "")
endif()

# Link the target to its dependencies
target_link_libraries(indigets ${QT_LIBRARIES})

# Modify the output path so that the plugin is created in the "indigets" sub-directory
set_target_properties(indigets PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${INDIGETS_DIRECTORY}")
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    set_target_properties(indigets PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${config} "${INDIGETS_DIRECTORY}")
endforeach()
