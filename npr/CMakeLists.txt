cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_FLAGS "-O1 -O2 -O3 -std=c++11 -mtune=native -fPIC -Wall -DARMA_BLAS_LONG -fopenmp")        ## Optimize
set(CMAKE_BUILD_TYPE Release                                                                    )
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}"                                          )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}"                                        )


find_package(Armadillo)
find_package(Boost)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")



include(NPR_FindFLANN)
message(STATUS "    FLANN_FOUND         = ${FLANN_FOUND}"           )
message(STATUS "    FLANN_LIBRARIES     = ${FLANN_LIBRARIES}"       )


set(NPR_DIR       ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILS_DIR     ${NPR_DIR})
message(STATUS "    NPR DIR = ${NPR_DIR}")


add_subdirectory(lwr)
