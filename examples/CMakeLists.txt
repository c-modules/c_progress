file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "example*.c")

foreach(SOURCE_FILE ${EXAMPLE_SOURCES})

    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE c_progress_bar::c_progress_bar)
    if(ENABLE_SANITIZERS AND NOT MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE -fsanitize=address,undefined)
        target_link_options(${TARGET_NAME} PRIVATE -fsanitize=address,undefined)
    endif()

endforeach()