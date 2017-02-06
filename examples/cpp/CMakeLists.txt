cmake_minimum_required(VERSION 3.0)

project(example1 VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "-std=c++11"                          )

set(SRC_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/src   )

find_package(lwr)
find_package(Armadillo)




include_directories(${LWR_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_DIR}/example1.cpp)
target_link_libraries(${PROJECT_NAME} ${ARMADILLO_LIBRARIES} ${LWR_LIBRARIES})
