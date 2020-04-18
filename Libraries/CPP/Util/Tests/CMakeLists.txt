# Project name
#project(tdd VERSION 0.1.0 LANGUAGES CXX)


#include(GNUInstallDirs)
#FILE(GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB SRCS *.cpp)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#include(GenerateExportHeader)
#add_dependencies(tdd journal grammar lexer utils)

add_executable(UtilTests.app ${SRCS})
add_dependencies(UtilTests.app Util ) #sqlitedb logbook lexer)

list(APPEND TEACC_INCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${TEACC_ROOT}/Util/include")# "${TEACC_ROOT}/xdb/sqlite3/include" "${XIO_ROOT}/lexer/include" "${XIO_ROOT}/interpreter/include")
target_include_directories(UtilTests.app PUBLIC
        "$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>"
        )

target_link_libraries(UtilTests.app ${CMAKE_DL_LIBS} Util)# sqlitedb logbook sqlite3 lexer interpreter)#journal grammar lexer utils sqlitedb)


IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            )
ENDIF ()


install(TARGETS UtilTests.app
        RUNTIME DESTINATION bin
        )


#install(DIRECTORY
#		include/${FrameWorkName}/${PROJECT_NAME}/
#		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${FrameWorkName}/${PROJECT_NAME}"
#		#        FILES_MATCHING PATTERN "*.h"
#		)
#
#
#install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
#		RUNTIME DESTINATION bin
#		INCLUDES DESTINATION include
#		)
#
#
#string(REPLACE "++" "" NS PROJECTNAME)

