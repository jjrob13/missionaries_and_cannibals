project(missionaries_and_cannibals C CXX)
cmake_minimum_required(VERSION 2.8)

 IF(CMAKE_COMPILER_IS_GNUCXX)
SET(CMAKE_CXX_FLAGS "-std=gnu++14 -g3 -ggdb") #Turn on C++14 and advanced debugging support
ENDIF()

set(MAIN_FILE src/Main.cpp)
set(APPLICATION_CODE_FILES src/Action.cpp
			src/Action.hpp
			src/Node.cpp
			src/Node.hpp
			src/Problem.cpp
			src/Problem.hpp
			src/State.cpp
			src/State.hpp )


add_library(application_code ${APPLICATION_CODE_FILES})

SET_TARGET_PROPERTIES(application_code PROPERTIES LINKER_LANGUAGE CXX)

add_executable(missionaries_and_cannibals ${MAIN_FILE})
target_link_libraries(missionaries_and_cannibals application_code)

