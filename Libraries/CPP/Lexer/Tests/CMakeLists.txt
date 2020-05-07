
#include(GNUInstallDirs)
#FILE(GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB SRCS *.cpp)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(TargetName LexerTests.App)
SET(ExecName   Lexer.App)

#target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#include(GenerateExportHeader)
#add_dependencies(tdd journal grammar Lexer Lexers)


add_executable(${TargetName} ${SRCS})
#add_executable(${ExecName} ${SRCS} )

add_dependencies(${TargetName} Util Diagnostics Lexer ) #sqlitedb logbook Lexer)
#add_dependencies(${ExecName} Util Diagnostics Lexer ) #sqlitedb logbook Lexer)

list(APPEND TEACC_INCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${TEACC_ROOT}/Lexer/include")# "${TEACC_ROOT}/xdb/sqlite3/include" "${XIO_ROOT}/Lexer/include" "${XIO_ROOT}/interpreter/include")

target_link_libraries(${TargetName}  Util Diagnostics Lexer)# sqlitedb logbook sqlite3 Lexer interpreter)#journal grammar Lexer Lexers sqlitedb)
#target_link_libraries(${ExectName}  Util Diagnostics Lexer)# sqlitedb logbook sqlite3 Lexer interpreter)#journal grammar Lexer Lexers sqlitedb)

target_compile_features(${TargetName}
        PUBLIC cxx_std_17
        )

#target_compile_features(${ExecName} PUBLIC cxx_std_17)

#target_include_directories(${ExecName} PUBLIC  "$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>" )
target_include_directories(${TargetName} PUBLIC "$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>" )




IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            )
ENDIF ()


install(TARGETS ${TargetName}
        RUNTIME DESTINATION bin
        )



SET(EXPR "\\'A = sin pi/2\;\\'")


#add_custom_command(TARGET ${TargetName} POST_BUILD
#    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TargetName}
#
#        "--Test=\\'Lexer::TokenData::Scan\\' \\'\\>\\<\\'"
#        "--Test=\\'Util::AppBook\\' --File=/home/bretzel/Applications/bin/logs/AppBook-Test.log"
#        "--Test=\\'Lexer::TokenScan\\' ${EXPR}"
#
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BIN_DIR}
#    COMMENT "Running ${TargetName}..."
#)


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

