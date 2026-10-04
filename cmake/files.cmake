# Add sources to executable/library
target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/syscall.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/sysmem.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/startup_stm32f411xx.S"

    "${CMAKE_CURRENT_SOURCE_DIR}/drivers/Src/stm32f411xx_gpio_driver.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/drivers/Src/stm32f411xx_spi_driver.c"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/drivers/Inc"
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/stm32f411xe_flash.ld" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/stm32f411xe_flash.ld")
