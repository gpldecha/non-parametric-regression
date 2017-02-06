cmake_minimum_required(VERSION 3.0)

project(pynpr VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "-std=c++11"                          )

find_package(PythonInterp)
find_package(PythonLibs)
find_package(Boost COMPONENTS python)
find_package(Armadillo)

enable_testing()

set(PYNPR_DIR       ${CMAKE_CURRENT_SOURCE_DIR})

find_package(lwr)


include_directories(${LWR_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

# BUILD PYTHON MODULES

python_add_module(pylwr src/lwr_module.cpp)
target_link_libraries(pylwr ${LWR_LIBRARIES} ${ARMADILLO_LIBRARIES} ${FLANN_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})


# INSTALL PYTHON MODULES
set(PYTHON_SITE_PACKAGES /usr/local/lib/python2.7/dist-packages/pynpr)
install(TARGETS pylwr DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ${PYNPR_DIR}/python/__init__.py DESTINATION ${PYTHON_SITE_PACKAGES})
