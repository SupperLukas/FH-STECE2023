add_library(
    sensor

    analog-sensor-event-generator.cpp
    analog-sensor-event-generator.h
    analog-sensor-mock.cpp
    analog-sensor-mock.h
    analog-sensor.h
    pressure-sensor-bmp280.cpp
    pressure-sensor-bmp280.h
)

# 1. Verknüpfung (Abhängigkeiten)
target_link_libraries(
    sensor
    PRIVATE adc utilities
)

# 2. Interne Includes (PRIVATE)
target_include_directories(
    sensor
    PRIVATE
    # Pfad zu src/door/analog_stuff/adc (Geschwister-Ordner)
    # Damit der Sensor-Code Header wie "adc-ads1115.h" findet.
    ${CMAKE_CURRENT_SOURCE_DIR}/../adc 
    
    # Pfad zu src/door/ (z.B. für structs.h oder door.h)
    ${CMAKE_CURRENT_SOURCE_DIR}/../.. 
)

# 3. Externe Includes (INTERFACE)
target_include_directories(
    sensor
    INTERFACE
    # Ermöglicht Nutzern, die die 'sensor'-Lib verlinken, 
    # Header wie "analog-sensor.h" zu finden.
    ${CMAKE_CURRENT_SOURCE_DIR}
)