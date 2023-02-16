idf_component_register(SRCS "drive_control.c" "management_buffer.c" "main.c" "nooch_ps3_event_handler.c" "nooch_wifi_main.c" "nooch_mqtt_event_handler.c"
                       INCLUDE_DIRS ".")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")

