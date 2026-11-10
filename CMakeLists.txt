cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/bin/pico-sdk-2.3.1")
set(TINYUSB_PATH "${CMAKE_SOURCE_DIR}/external/tinyusb")
set(PICO_TINYUSB_PATH "${TINYUSB_PATH}")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(midi_controller_test_pico)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main
    src/main.c
    usb_descriptors.c
)

pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${TINYUSB_PATH}/src
    ${TINYUSB_PATH}/hw
)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)


target_link_libraries(main PRIVATE
    pico_stdlib
    pico_time
    tinyusb_device
    tinyusb_board
)


