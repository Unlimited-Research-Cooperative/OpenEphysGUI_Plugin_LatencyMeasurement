# FindZMQ.cmake
find_path(ZMQ_INCLUDE_DIR
    NAMES zmq.hpp
    PATHS /usr/local/include /usr/include
)

find_library(ZMQ_LIBRARY
    NAMES zmq
    PATHS /usr/local/lib /usr/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZMQ DEFAULT_MSG ZMQ_LIBRARY ZMQ_INCLUDE_DIR)

if(ZMQ_FOUND)
    set(ZMQ_LIBRARIES ${ZMQ_LIBRARY})
    set(ZMQ_INCLUDE_DIRS ${ZMQ_INCLUDE_DIR})
endif()
