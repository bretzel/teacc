
#include(GNUInstallDirs)
#FILE(GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB SRCS *.cpp)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#include(GenerateExportHeader)
#add_dependencies(tdd journal grammar Lexer Lexers)

add_executable(LexerTests.app ${SRCS})
add_dependencies(LexerTests.app Lexer ) #sqlitedb logbook Lexer)

list(APPEND TEACC_INCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${TEACC_ROOT}/Lexer/include")# "${TEACC_ROOT}/xdb/sqlite3/include" "${XIO_ROOT}/Lexer/include" "${XIO_ROOT}/interpreter/include")
target_include_directories(LexerTests.app PUBLIC
        "$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>"
        )

target_link_libraries(LexerTests.app ${CMAKE_DL_LIBS} Util)# sqlitedb logbook sqlite3 Lexer interpreter)#journal grammar Lexer Lexers sqlitedb)
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_17)

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            )
ENDIF ()


install(TARGETS LexerTests.app
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

