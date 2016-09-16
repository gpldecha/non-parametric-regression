

find_package(PythonInterp)
find_package(PythonLibs)

if(APPLE AND ${PYTHON_VERSION_MAJOR} EQUAL 3)
    FIND_PACKAGE(Boost COMPONENTS python3)
else()
    FIND_PACKAGE(Boost COMPONENTS python)
endif()

ENABLE_TESTING()
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

# BUILD PYTHON MODULES

python_add_module(pylwr lwr_module.cpp)
target_link_libraries(pylwr lwr)

set(PYTHON_SITE_PACKAGES /usr/local/lib/python2.7/site-packages)



# INSTALL PYTHON MODULES

install(TARGETS pylwr DESTINATION ${PYTHON_SITE_PACKAGES})

#find_path( PYTHON_SITE_PACKAGES site-packages ${PYTHON_INCLUDE_PATH}/.. )
#execute_process ( COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
#message(status " site-package: " ${PYTHON_SITE_PACKAGES})
