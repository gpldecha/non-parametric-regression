cmake_minimum_required(VERSION 3.0)

project(lwr VERSION 1.0.0)

set(INCLUDE_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/include     )
set(SRC_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/src         )

set(LWR_INC ${INCLUDE_DIR}/lwr/lwr.h
            ${INCLUDE_DIR}/lwr/lwr_options.h
            ${INCLUDE_DIR}/lwr/lwr_flann.h
)

set(LWR_SRC ${SRC_DIR}/lwr/lwr.cpp
            ${SRC_DIR}/lwr/lwr_flann.cpp
)

message(STATUS " utils dir: ${UTILS_DIR}")


include_directories(${INCLUDE_DIR} ${UTILS_DIR} ${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${LWR_SRC} ${LWR_INC} ${UTILS_DIR})
target_link_libraries(${PROJECT_NAME} ${ARMADILLO_LIBRARIES} ${FLANN_LIBRARIES})

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/liblwr.so
#   * header location after install: <prefix>/include/lwr/lwr.h
#   * headers can be included by C++ code `#include <lwr/lwr.h>
install(TARGETS               lwr
        LIBRARY DESTINATION   "lib"
        INCLUDES DESTINATION  "${include_install_dir}"
)
# Headers:
#   * include/lwr/*.h -> <prefix>/include/lwr/*.hpp
install(
          DIRECTORY "include/"
          DESTINATION "${include_install_dir}/npr"
          FILES_MATCHING PATTERN "*.h"
)
# Config
#   * <prefix>/lib/cmake/lwr/lwrConfig.cmake
#   * <prefix>/lib/cmake/lwr/lwrConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)
