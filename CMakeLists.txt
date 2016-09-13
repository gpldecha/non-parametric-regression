cmake_minimum_required(VERSION 2.8.3)
project(non-parametric-regression)


set(CMAKE_CXX_FLAGS "-O1 -O2 -O3 -std=c++11 -mtune=native -fPIC -Wall -DARMA_BLAS_LONG -fopenmp")        ## Optimize
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(Armadillo)
find_library(Flann flann_cpp)
find_package(Boost REQUIRED COMPONENTS system)
find_library(LZ4 lz4)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

# workaround a FindHDF5 bug
macro(find_hdf5)
    find_package(HDF5)

    set( HDF5_IS_PARALLEL FALSE )
    foreach( _dir ${HDF5_INCLUDE_DIRS} )
        if( EXISTS "${_dir}/H5pubconf.h" )
            file( STRINGS "${_dir}/H5pubconf.h"
                HDF5_HAVE_PARALLEL_DEFINE
                REGEX "HAVE_PARALLEL 1" )
            if( HDF5_HAVE_PARALLEL_DEFINE )
                set( HDF5_IS_PARALLEL TRUE )
            endif()
        endif()
    endforeach()
    set( HDF5_IS_PARALLEL ${HDF5_IS_PARALLEL} CACHE BOOL
        "HDF5 library compiled with parallel IO support" )
    mark_as_advanced( HDF5_IS_PARALLEL )
endmacro(find_hdf5)

find_hdf5()
if (NOT HDF5_FOUND)
        message(WARNING "hdf5 library not found, some tests will not be run")
else()
    include_directories(${HDF5_INCLUDE_DIR})
endif()

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



set(INCLUDE_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/include     )
set(SRC_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/src         )
set(PYTHON_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/python      )


set(INC  ${INCLUDE_DIR}/utils/npr_utils.h
         ${INCLUDE_DIR}/lwr/lwr.h
         ${INCLUDE_DIR}/lwr/lwr_options.h
         ${INCLUDE_DIR}/lwr/lwr_flann.h
)

set(SRC  ${SRC_DIR}/lwr.cpp
         ${SRC_DIR}/lwr_flann.cpp
)

include_directories(${INCLUDE_DIR})
add_library(lwr SHARED ${SRC} ${INC})
target_link_libraries(lwr ${ARMADILLO_LIBRARIES} lz4 ${HDF5_LIBRARIES} flann_cpp)

                                
add_executable(lwr_run ${SRC_DIR}/lwr_run.cpp )
target_link_libraries(lwr_run lwr  ${ARMADILLO_LIBRARIES})

add_executable(lwr_test ${SRC_DIR}/lwr_test.cpp )
target_link_libraries(lwr_test lwr  ${ARMADILLO_LIBRARIES} boost_system boost_timer boost_chrono)




# BUILD PYTHON MODULES

PYTHON_ADD_MODULE(pylwr ${PYTHON_DIR}/lwr_module.cpp)
target_link_libraries(pylwr lwr)








