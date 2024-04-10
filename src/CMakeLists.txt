add_executable(${ProjectName}
                  main.c
                  bridge_common.c

)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    pico_btstack_ble      # BLE stack
    pico_btstack_cyw43    # BLE stack with CYW43
    pico_cyw43_arch_none  
    )

target_compile_definitions(${ProjectName}  PRIVATE
  CYW43_ENABLE_BLUETOOTH=1  # otherwise cyw43_arch_init() will not initialize BLE
)

pico_enable_stdio_uart(${ProjectName} 0)
pico_enable_stdio_usb(${ProjectName} 1)

pico_btstack_make_gatt_header(${ProjectName} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/temp_sensor.gatt")
pico_add_extra_outputs(${ProjectName})  