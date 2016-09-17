

set(INCLUDE_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/include     )
set(SRC_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/src         )


set(LWR_INC ${INCLUDE_DIR}/lwr/lwr.h
            ${INCLUDE_DIR}/lwr/lwr_options.h
            ${INCLUDE_DIR}/lwr/lwr_flann.h
)

set(LWR_SRC ${SRC_DIR}/lwr/lwr.cpp
            ${SRC_DIR}/lwr/lwr_flann.cpp
)

include_directories(${INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${FLANN_INCLUDE_DIRS})

add_library(lwr SHARED ${LWR_SRC} ${INCLUDE_DIR}/utils/npr_utils.h ${LWR_INC})
target_link_libraries(lwr ${ARMADILLO_LIBRARIES} ${FLANN_LIB})

# INSTALL

message(status "    CMAKE_INSTALL_PREFIX:" ${CMAKE_INSTALL_PREFIX})

install(TARGETS lwr DESTINATION lib/npr)
install(FILES ${LWR_INC} DESTINATION include/npr/lwr)
install(FILES ${INCLUDE_DIR}/utils/npr_utils.h DESTINATION include/npr/utils)
