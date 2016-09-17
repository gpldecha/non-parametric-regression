cmake_minimum_required(VERSION 2.8.3)
project(non-parametric-regression)


set(CMAKE_CXX_FLAGS "-O1 -O2 -O3 -std=c++11 -mtune=native -fPIC -Wall -DARMA_BLAS_LONG -fopenmp")        ## Optimize
set(CMAKE_BUILD_TYPE Release                                                                    )
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}"                                          )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}"                                        )


set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin                                           )
set(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib                                           )
set(LIB_INSTALL_PATH        ${CMAKE_INSTALL_PREFIX}lib/npr                                      )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN"                   )
set(CMAKE_INSTALL_RPATH    "$ORIGIN"                                                            )
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE                                                         )


set(CMAKE_INSTALL_RPATH     "${CMAKE_INSTALL_PREFIX}/lib/npr"                                   )
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE                                                      )

set(NPR_CURRENT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}                                         )



find_package(Armadillo)
find_package(Boost REQUIRED COMPONENTS python)

find_library(FLANN_LIB NAMES flann HINTS /usr/lib/x86_64-linux-gnu/)
set(FLANN_INCLUDE_DIRS /usr/include/flann/)

if(NOT FLANN_LIB)
  message(FATAL_ERROR "flann library not found")
else()
    message(status " FLANN library: " ${FLANN_LIB})
endif()



message(status "    CMAKE_INSTALL_PREFIX:" ${CMAKE_INSTALL_PREFIX})


add_subdirectory(lwr)
add_subdirectory(python)
add_subdirectory(tests)



