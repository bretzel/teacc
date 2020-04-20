
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
# Project name
project(Util VERSION 0.1.0 LANGUAGES CXX)
set(FrameWorkName "teacc")

option(BUILD_UTIL "Enable building Utility library" ON)
option(BUILD_LOGBOOK "Enable building the Logbook Library" OFF)
option(BUILD_LEXER "Enable building the Lexer & Tokens Library" ON)
option(BUILD_TEACCDB   "Enable building teacc database provider engines support (SQLite3; Prosgres)" OFF)
option(BUILD_TDD "Enable building tdd" OFF)
option(BUILD_INTERPRETER "Enable building the teacc interpreter" OFF)

SET(TEACC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
SET(UTILS_INCLUDE_DIR ${TEACC_ROOT}/Util/include})
SET(LOGBOOK_INCLUDE_DIR ${TEACC_ROOT}/Logbook/include})
SET(LEXER_INCLUDE_DIR ${TEACC_ROOT}/Lexer/include})
SET(TEACCDB_INCLUDE_DIR ${TEACC_ROOT}/TeaccDB/Sqlite3/include})
SET(INTERPRETER_INCLUDE_DIR ${TEAC_ROOT}/Interpreter/include})


# testing noswap in nvim...
if(BUILD_UTIL)
    add_subdirectory(Util)
endif()
if(BUILD_LEXER)
    add_subdirectory(Lexer)
endif()
if(BUILD_LOGBOOK)
    add_subdirectory(Logbook)
endif()
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif()
if(BUILD_TEACCDB)
    add_subdirectory(TeaccDB)
endif()
if(BUILD_INTERPRETER)
    add_subdirectory(Interpreter)
endif()

message ("Project SourceDir:" ${PROJECT_SOURCE_DIR})


IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()


