# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Pico_CLI C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Pico_CLI 
    Pico_CLI.c 
    editLine.c
    pico_parser.c
    )

pico_set_program_name(Pico_CLI "Pico_CLI")
pico_set_program_version(Pico_CLI "1.0.0")

# Generate PIO header
# pico_generate_pio_header(Pico_CLI ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Pico_CLI 0)
pico_enable_stdio_usb(Pico_CLI 1)

# Add the standard library to the build
target_link_libraries(Pico_CLI
        pico_stdlib
        hardware_rtc
        )

# Add the standard include files to the build
target_include_directories(Pico_CLI PRIVATE
        include
        ${CMAKE_CURRENT_LIST_DIR}
)

# additional compiler instructions informations
target_compile_definitions(Pico_CLI PRIVATE
        PICO_STACK_SIZE=0x1000
        PICO_CORE1_STACK_SIZE=0x800
        PICO_STDIO_DEFAULT_CRLF=0
        PICO_STDIO_ENABLE_CRLF_SUPPORT=0
        )

# Add any user requested libraries
target_link_libraries(Pico_CLI 
        # hardware_spi
        # hardware_i2c
        # hardware_pio
        # hardware_timer
        # hardware_clocks
        )

pico_add_extra_outputs(Pico_CLI)

