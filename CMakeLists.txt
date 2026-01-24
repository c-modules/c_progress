cmake_minimum_required(VERSION 3.14)

project(c_progress_bar
    VERSION 0.0.1
    LANGUAGES C
    DESCRIPTION "A colorful, lightweight progress bar library for C"
)

### Dependencies & Modules ###
include(GNUInstallDirs)

### Options ###
option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)
option(BUILD_EXAMPLES "Build example executables" OFF)

### Library ###
add_library(c_progress_bar STATIC
    src/c_progress_bar.c
    src/math_utils.c
    src/system_utils.c
)
add_library(c_progress_bar::c_progress_bar ALIAS c_progress_bar)

### Standard (c99) ###
set_target_properties(c_progress_bar PROPERTIES 
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

### Includes ###
target_include_directories(c_progress_bar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
)

### Warnings ###
if(MSVC)
    target_compile_options(c_progress_bar PRIVATE /W4)
else()
    target_compile_options(c_progress_bar PRIVATE 
        -Wall -Wextra -Wpedantic -Wshadow -Wpointer-arith 
        -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
    )
endif()

### Sanitizers ###
if(ENABLE_SANITIZERS)
    if(NOT MSVC)
        target_compile_options(c_progress_bar PRIVATE -fsanitize=address,undefined)
        target_link_options(c_progress_bar PRIVATE -fsanitize=address,undefined)
    endif()
endif()

### Definitions ###
target_compile_definitions(c_progress_bar PRIVATE CTB_VERSION="${PROJECT_VERSION}")

### Installation ###
if(PROJECT_IS_TOP_LEVEL)
    include(CMakePackageConfigHelpers)

    install(TARGETS c_progress_bar
        EXPORT c_progress_barTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    ### Package config & version ###
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfig.cmake.in"
        "@PACKAGE_INIT@\n\n"
        "include(\"\${CMAKE_CURRENT_LIST_DIR}/c_progress_barTargets.cmake\")\n\n"
        "check_required_components(c_progress_bar)\n"
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/c_progress_bar"
    )

    ### Export targets / install cmake files ###
    install(EXPORT c_progress_barTargets
        FILE c_progress_barTargets.cmake
        NAMESPACE c_progress_bar::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/c_progress_bar
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/c_progress_barConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/c_progress_bar
    )

    ### Build Examples ###
    if(BUILD_EXAMPLES)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt")
            add_subdirectory(examples)
        endif()
    endif()

endif()

### Testing ###
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    enable_testing() 
    add_subdirectory(tests)
endif()
