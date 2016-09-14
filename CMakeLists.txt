cmake_minimum_required(VERSION 2.8.3)
project(non-parametric-regression)


set(CMAKE_CXX_FLAGS "-O1 -O2 -O3 -std=c++11 -mtune=native -fPIC -Wall -DARMA_BLAS_LONG -fopenmp")        ## Optimize
set(CMAKE_BUILD_TYPE Debug                                                                      )
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}"                                          )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}"                                        )


set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin                                           )
set(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib                                           )


find_package(Armadillo)
find_package(Boost REQUIRED COMPONENTS python)
find_package(Numpy)

find_library(FLANN_LIB NAMES flann HINTS /usr/lib/x86_64-linux-gnu/)


set(FLANN_INCLUDE_DIRS /usr/include/flann/)

if(NOT FLANN_LIB)
  message(FATAL_ERROR "flann library not found")
else()
    message(status " FLANN library: " ${FLANN_LIB})
endif()


#set(LZ4_LIB  /usr/local/lib/liblz4.so)


set(INCLUDE_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/include     )
set(SRC_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/src         )
set(PYTHON_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/python      )


set(LWR_INC ${INCLUDE_DIR}/utils/npr_utils.h
            ${INCLUDE_DIR}/lwr/lwr.h
            ${INCLUDE_DIR}/lwr/lwr_options.h
            ${INCLUDE_DIR}/lwr/lwr_flann.h
)

set(LWR_SRC ${SRC_DIR}/lwr.cpp
            ${SRC_DIR}/lwr_flann.cpp
)

include_directories(${INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${FLANN_INCLUDE_DIRS})



add_library(lwr SHARED ${LWR_SRC} ${LWR_INC})
target_link_libraries(lwr ${ARMADILLO_LIBRARIES} ${FLANN_LIB})

                                
#add_executable(lwr_run ${SRC_DIR}/lwr_run.cpp )
#target_link_libraries(lwr_run lwr ${ARMADILLO_LIBRARIES} hdf5)

#add_executable(lwr_test ${SRC_DIR}/lwr_test.cpp )
#target_link_libraries(lwr_test lwr  ${ARMADILLO_LIBRARIES} boost_system boost_timer boost_chrono hdf5)



FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
if(APPLE AND ${PYTHON_VERSION_MAJOR} EQUAL 3)
    FIND_PACKAGE(Boost COMPONENTS python3)
else()
    FIND_PACKAGE(Boost COMPONENTS python)
endif()

ENABLE_TESTING()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!


# BUILD PYTHON MODULES

PYTHON_ADD_MODULE(pylwr ${PYTHON_DIR}/lwr_module.cpp)
target_link_libraries(pylwr lwr)








