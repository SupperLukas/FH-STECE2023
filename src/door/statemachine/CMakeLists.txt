add_library(
    statemachine

    door.h
    door.cpp
    structs.h
    inputs.h
    inputs.cpp
    outputs.h
    outputs.cpp
)

target_link_libraries(
    statemachine

    PUBLIC

    motor
    utilities
    input
    output
    sensor
)

target_include_directories(
    statemachine
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(
    statemachine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
