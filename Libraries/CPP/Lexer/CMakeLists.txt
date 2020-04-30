cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# Project name

project(Lexer VERSION 0.1.0 LANGUAGES CXX)


include(GNUInstallDirs)
FILE(GLOB HDRS include/${FrameWorkName}/${PROJECT_NAME}/*)
FILE(GLOB SRCS src/*)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )



add_library(
        ${PROJECT_NAME}
        SHARED
        ${HDRS}
        ${SRCS}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_17)

include(GenerateExportHeader)
#generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${${PROJECT_NAME}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()

add_dependencies(${PROJECT_NAME} Util) #  sqlitedb logbook )
#set_target_properties(${PROJECT_NAME}
#        SOVERSION
#        )
list(APPEND TEACC_INCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${TEACC_ROOT}/Util/include")# "${TEACC_ROOT}/xdb/sqlite3/include" "${TEACC_ROOT}/logbook/include")
message("TEACC_INCLUDE_PATHS:(${PROJECT_NAME}) " ${TEACC_INCLUDE_PATHS})

target_include_directories(${PROJECT_NAME} PUBLIC
		"$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>"
        $<INSTALL_INTERFACE:include/${FrameWorkName}/${PROJECT_NAME}>  # <prefix>/include/mylib
        )

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} Util)


install(DIRECTORY
        include/${FrameWorkName}/${PROJECT_NAME}/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${FrameWorkName}/${PROJECT_NAME}"
#        FILES_MATCHING PATTERN "*.h"
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

add_subdirectory(Tests)

string(REPLACE "++" "" NS PROJECTNAME)

