# Project name
#project(tdd VERSION 0.1.0 LANGUAGES CXX)


#include(GNUInstallDirs)
#FILE(GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB SRCS *.cpp)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(Diagnostics.App ${SRCS})
add_dependencies(Diagnostics.App Util Lexer) #sqlitedb logbook lexer)

list(APPEND TEACC_INCLUDE_PATHS "${TEACC_ROOT}/Util/include" "${TEACC_ROOT}/Lexer/include")# "${TEACC_ROOT}/xdb/sqlite3/include""${XIO_ROOT}/interpreter/include")
target_include_directories(Diagnostics.App PRIVATE  "$<BUILD_INTERFACE:${TEACC_INCLUDE_PATHS}>")

target_link_libraries(Diagnostics.App ${CMAKE_DL_LIBS} Util Lexer)# sqlitedb logbook sqlite3 lexer interpreter)#journal grammar lexer utils sqlitedb)
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_17)

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            )
ENDIF ()


install(TARGETS UtilTests.app RUNTIME DESTINATION bin)

