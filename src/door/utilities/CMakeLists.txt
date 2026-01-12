add_library(
    utilities

    timespec.h
    timespec.cpp
    eventloop.h
    eventloop.cpp
    periodic-timer.cpp
    periodic-timer.h
    i2c.h
    i2c.cpp
    i2c-interface.h
    i2c-real.h
    i2c-real.cpp
    i2c-mock.h
    i2c-mock.cpp
)

target_include_directories(
    utilities
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
