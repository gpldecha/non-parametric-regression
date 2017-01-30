set(LWR_INCLUDE_DIR "/usr/local/include/npr")
set(LWR_INCLUDE_DIRS ${LWR_INCLUDE_DIR})

set(LWR_LIBRARY_DIR "/usr/local/lib")
find_library(LWR_LIBRARY lwr HINTS ${LWR_LIBRARY_DIR})
set(LWR_LIBRARIES ${LWR_LIBRARY})

if(LWR_LIBRARY)
  message(STATUS " Found lwr")
  message(STATUS " LWR_INCLUDE_DIRS: ${LWR_INCLUDE_DIRS}")
  message(STATUS " LWR_LIBRARIES: ${LWR_LIBRARIES}")
  set(LWR_FOUND "YES")
else(LWR_LIBRARY)
  set(LWR_FOUND "NO")
endif(LWR_LIBRARY)