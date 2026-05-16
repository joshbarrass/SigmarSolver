# scikit-build-core requires at least 3.15
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# use the variables set by scikit-build-core based on the pyproject.toml
project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION})

# add the actual library from the parent directory. 
add_subdirectory(.. lib_build)

# scikit-build-core sets the install prefix to the wheel build
# directory, so all paths are relative to that. The library
# built by the parent project is installed to /lib, and we
# manually install the binding to the wheel root.
install(TARGETS sigmarsolver
        LIBRARY DESTINATION sigmarsolver/lib
        RUNTIME DESTINATION sigmarsolver/lib
        ARCHIVE DESTINATION sigmarsolver/lib
)
