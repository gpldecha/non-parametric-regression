# Find FLANN library
# This module defines
# FLANN_LIBRARIES
# FLANN_FOUND

find_library(FLANN_LIBRARY
  NAMES flann
  PATHS /usr/lib/x86_64-linux-gnu/)

if (FLANN_LIBRARY)
  set(FLANN_LIBRARIES ${FLANN_LIBRARY})
  set(FLANN_FOUND "YES")
else (FLANN_LIBRARY)
  set(FLANN_FOUND "NO")
endif (FLANN_LIBRARY)

mark_as_advanced(
  FLANN_LIBRARY
)
