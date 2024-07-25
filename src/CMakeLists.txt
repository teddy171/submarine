add_executable(src
    main.c
)

target_include_directories(src PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(src
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    )

pico_add_extra_outputs(src)
if (TARGET tinyusb_device)

 
 # enable usb output, disable uart output
pico_enable_stdio_usb(src 1)
pico_enable_stdio_uart(src 0)


 
 elseif(PICO_ON_DEVICE)
 message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in
  the SDK")
 endif()