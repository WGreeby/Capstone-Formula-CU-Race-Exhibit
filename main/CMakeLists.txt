idf_component_register(SRCS "nooch_ps3_event_handler.c" "nooch_wifi_main.c" "nooch_mqtt_event_handler.c" "blink_example_main.c"
                       INCLUDE_DIRS ".")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")

