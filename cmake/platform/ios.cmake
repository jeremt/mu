
function(add_framework TARGET_NAME DEST_PATH INCLUDE_FILES SOURCE_FILES)
    set(FRAMEWORK_PATH ${DEST_PATH}/${TARGET_NAME}.framework)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E make_directory ${FRAMEWORK_PATH}/Versions/A
    )

    # Library
    add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${FRAMEWORK_PATH}/Versions/A
        PREFIX ""
        SUFFIX ""
    )
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E create_symlink ${FRAMEWORK_PATH}/Versions/A ${FRAMEWORK_PATH}/Versions/Current
    )
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E create_symlink ${FRAMEWORK_PATH}/Versions/Current/${TARGET_NAME} ${FRAMEWORK_PATH}/${TARGET_NAME}
    )

    # Headers
    foreach(INCLUDE_FILE ${INCLUDE_FILES})
        get_filename_component(BASE_PATH ${INCLUDE_FILE} DIRECTORY)
        get_filename_component(FILE_NAME ${INCLUDE_FILE} NAME)
        string(REPLACE ${CMAKE_SOURCE_DIR}/mu/ "" PATH ${BASE_PATH})
        add_custom_command(
            TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${INCLUDE_FILE} ${FRAMEWORK_PATH}/Versions/A/Headers/${PATH}/${FILE_NAME}
        )
    endforeach()
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E create_symlink ${FRAMEWORK_PATH}/Versions/Current/Headers ${FRAMEWORK_PATH}/Headers
    )

    # Resources
    # TODO
endfunction()