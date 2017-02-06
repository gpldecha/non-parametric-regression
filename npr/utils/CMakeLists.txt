


set(include_install_dir "include")


# Headers:
#   * include/utils/*.h -> <prefix>/include/utils/*.h
install(
          DIRECTORY "include/"
          DESTINATION "${include_install_dir}/npr"
          FILES_MATCHING PATTERN "*.h"
)
