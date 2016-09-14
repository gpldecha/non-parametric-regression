# Compile C++ tests (here only one, but it will grab whatever cxx is in the test directory)
file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Iterate over all tests found. For each, declare an executable and add it to the tests list.
#set(ALL_TESTS)
#foreach(FILE ${TEST_FILES})
#    string(REGEX REPLACE "[./]" "_" NAME ${FILE}) # create exe name
#    add_executable(${NAME} ${FILE})
#    target_link_libraries(${NAME} ProjA ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}) # link against our lib and boost test
#    add_test(NAME ${NAME} COMMAND ${NAME})                              # this is how to add tests to CMake
#endforeach(FILE ${TEST_FILES})


#add_executable(lwr_run ${SRC_DIR}/lwr_run.cpp )
#target_link_libraries(lwr_run lwr ${ARMADILLO_LIBRARIES} hdf5)

#add_executable(lwr_test ${SRC_DIR}/lwr_test.cpp )
#target_link_libraries(lwr_test lwr  ${ARMADILLO_LIBRARIES} boost_system boost_timer boost_chrono hdf5)


#include(CTest)
