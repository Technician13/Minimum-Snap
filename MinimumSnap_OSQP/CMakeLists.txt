cmake_minimum_required(VERSION 3.10)

PROJECT (MINI_SNAP)

SET(SRC_LIST main.cpp MiniSnap.cpp)

MESSAGE(STATUS "This is BINARY dir " ${MINI_SNAP_BINARY_DIR})

MESSAGE(STATUS "This is SOURCE dir " ${MINI_SNAP_SOURCE_DIR})

ADD_EXECUTABLE(MINI_SNAP ${SRC_LIST})


FIND_PACKAGE(Eigen3 REQUIRED)
SET(Eigen3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Eigen3_INCLUDE_DIRS})


# Find OSQP library and headers
FIND_PACKAGE(osqp REQUIRED)
# Link the OSQP shared library
TARGET_LINK_LIBRARIES(MINI_SNAP PRIVATE osqp::osqp)
# or...
# Link the OSQP static library
TARGET_LINK_LIBRARIES(MINI_SNAP PRIVATE osqp::osqpstatic)

SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O3 -Wall") # -Wextra -Werror