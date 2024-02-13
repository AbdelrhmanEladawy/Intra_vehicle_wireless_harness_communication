# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

# compile ASM with C:/10 2021.10/bin/arm-none-eabi-gcc.exe
# compile C with C:/10 2021.10/bin/arm-none-eabi-gcc.exe
# compile CXX with C:/10 2021.10/bin/arm-none-eabi-g++.exe
ASM_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DFREE_RTOS_KERNEL_SMP=1 -DLIB_FREERTOS_KERNEL=1 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_USB=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_CONFIG_RTOS_ADAPTER_HEADER=F:/Pico_Project/rp2040-freertos-template/lib/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include/freertos_sdk_config.h -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"rp2040-freertos-template\" -DPICO_USE_BLOCKED_RAM=0

ASM_INCLUDES = -IF:\Pico_Project\rp2040-freertos-template\src -IF:\pico\pico-sdk\src\common\pico_stdlib\include -IF:\pico\pico-sdk\src\rp2_common\hardware_gpio\include -IF:\pico\pico-sdk\src\common\pico_base\include -IF:\Pico_Project\rp2040-freertos-template\build\generated\pico_base -IF:\pico\pico-sdk\src\boards\include -IF:\pico\pico-sdk\src\rp2_common\pico_platform\include -IF:\pico\pico-sdk\src\rp2040\hardware_regs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_base\include -IF:\pico\pico-sdk\src\rp2040\hardware_structs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_claim\include -IF:\pico\pico-sdk\src\rp2_common\hardware_sync\include -IF:\pico\pico-sdk\src\rp2_common\hardware_irq\include -IF:\pico\pico-sdk\src\common\pico_sync\include -IF:\pico\pico-sdk\src\common\pico_time\include -IF:\pico\pico-sdk\src\rp2_common\hardware_timer\include -IF:\pico\pico-sdk\src\common\pico_util\include -IF:\pico\pico-sdk\src\rp2_common\hardware_uart\include -IF:\pico\pico-sdk\src\rp2_common\hardware_resets\include -IF:\pico\pico-sdk\src\rp2_common\hardware_clocks\include -IF:\pico\pico-sdk\src\rp2_common\hardware_pll\include -IF:\pico\pico-sdk\src\rp2_common\hardware_vreg\include -IF:\pico\pico-sdk\src\rp2_common\hardware_watchdog\include -IF:\pico\pico-sdk\src\rp2_common\hardware_xosc\include -IF:\pico\pico-sdk\src\rp2_common\hardware_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_runtime\include -IF:\pico\pico-sdk\src\rp2_common\pico_printf\include -IF:\pico\pico-sdk\src\common\pico_bit_ops\include -IF:\pico\pico-sdk\src\common\pico_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_double\include -IF:\pico\pico-sdk\src\rp2_common\pico_float\include -IF:\pico\pico-sdk\src\rp2_common\pico_malloc\include -IF:\pico\pico-sdk\src\rp2_common\pico_bootrom\include -IF:\pico\pico-sdk\src\common\pico_binary_info\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio_usb\include -IF:\pico\pico-sdk\src\rp2_common\pico_unique_id\include -IF:\pico\pico-sdk\src\rp2_common\hardware_flash\include -IF:\pico\pico-sdk\src\common\pico_usb_reset_interface\include -IF:\pico\pico-sdk\src\rp2_common\pico_int64_ops\include -IF:\pico\pico-sdk\src\rp2_common\pico_mem_ops\include -IF:\pico\pico-sdk\src\rp2_common\boot_stage2\include -IF:\pico\pico-sdk\lib\tinyusb\src -IF:\pico\pico-sdk\lib\tinyusb\src\common -IF:\pico\pico-sdk\lib\tinyusb\hw -IF:\pico\pico-sdk\src\rp2_common\pico_fix\rp2040_usb_device_enumeration\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\portable\ThirdParty\GCC\RP2040\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\include -IF:\pico\pico-sdk\src\rp2_common\hardware_exception\include -IF:\pico\pico-sdk\src\rp2_common\pico_multicore\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_arch\include -IF:\pico\pico-sdk\lib\cyw43-driver\src -IF:\pico\pico-sdk\lib\cyw43-driver\firmware -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\cybt_shared_bus -IF:\pico\pico-sdk\src\rp2_common\hardware_pio\include -IF:\pico\pico-sdk\src\rp2_common\hardware_dma\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\include -IF:\pico\pico-sdk\src\rp2_common\pico_async_context\include -IF:\Pico_Project\rp2040-freertos-template\build\pico-sdk\src\rp2_common\pico_cyw43_driver

ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections

C_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DFREE_RTOS_KERNEL_SMP=1 -DLIB_FREERTOS_KERNEL=1 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_USB=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_CONFIG_RTOS_ADAPTER_HEADER=F:/Pico_Project/rp2040-freertos-template/lib/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include/freertos_sdk_config.h -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"rp2040-freertos-template\" -DPICO_USE_BLOCKED_RAM=0

C_INCLUDES = -IF:\Pico_Project\rp2040-freertos-template\src -IF:\pico\pico-sdk\src\common\pico_stdlib\include -IF:\pico\pico-sdk\src\rp2_common\hardware_gpio\include -IF:\pico\pico-sdk\src\common\pico_base\include -IF:\Pico_Project\rp2040-freertos-template\build\generated\pico_base -IF:\pico\pico-sdk\src\boards\include -IF:\pico\pico-sdk\src\rp2_common\pico_platform\include -IF:\pico\pico-sdk\src\rp2040\hardware_regs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_base\include -IF:\pico\pico-sdk\src\rp2040\hardware_structs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_claim\include -IF:\pico\pico-sdk\src\rp2_common\hardware_sync\include -IF:\pico\pico-sdk\src\rp2_common\hardware_irq\include -IF:\pico\pico-sdk\src\common\pico_sync\include -IF:\pico\pico-sdk\src\common\pico_time\include -IF:\pico\pico-sdk\src\rp2_common\hardware_timer\include -IF:\pico\pico-sdk\src\common\pico_util\include -IF:\pico\pico-sdk\src\rp2_common\hardware_uart\include -IF:\pico\pico-sdk\src\rp2_common\hardware_resets\include -IF:\pico\pico-sdk\src\rp2_common\hardware_clocks\include -IF:\pico\pico-sdk\src\rp2_common\hardware_pll\include -IF:\pico\pico-sdk\src\rp2_common\hardware_vreg\include -IF:\pico\pico-sdk\src\rp2_common\hardware_watchdog\include -IF:\pico\pico-sdk\src\rp2_common\hardware_xosc\include -IF:\pico\pico-sdk\src\rp2_common\hardware_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_runtime\include -IF:\pico\pico-sdk\src\rp2_common\pico_printf\include -IF:\pico\pico-sdk\src\common\pico_bit_ops\include -IF:\pico\pico-sdk\src\common\pico_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_double\include -IF:\pico\pico-sdk\src\rp2_common\pico_float\include -IF:\pico\pico-sdk\src\rp2_common\pico_malloc\include -IF:\pico\pico-sdk\src\rp2_common\pico_bootrom\include -IF:\pico\pico-sdk\src\common\pico_binary_info\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio_usb\include -IF:\pico\pico-sdk\src\rp2_common\pico_unique_id\include -IF:\pico\pico-sdk\src\rp2_common\hardware_flash\include -IF:\pico\pico-sdk\src\common\pico_usb_reset_interface\include -IF:\pico\pico-sdk\src\rp2_common\pico_int64_ops\include -IF:\pico\pico-sdk\src\rp2_common\pico_mem_ops\include -IF:\pico\pico-sdk\src\rp2_common\boot_stage2\include -IF:\pico\pico-sdk\lib\tinyusb\src -IF:\pico\pico-sdk\lib\tinyusb\src\common -IF:\pico\pico-sdk\lib\tinyusb\hw -IF:\pico\pico-sdk\src\rp2_common\pico_fix\rp2040_usb_device_enumeration\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\portable\ThirdParty\GCC\RP2040\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\include -IF:\pico\pico-sdk\src\rp2_common\hardware_exception\include -IF:\pico\pico-sdk\src\rp2_common\pico_multicore\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_arch\include -IF:\pico\pico-sdk\lib\cyw43-driver\src -IF:\pico\pico-sdk\lib\cyw43-driver\firmware -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\cybt_shared_bus -IF:\pico\pico-sdk\src\rp2_common\hardware_pio\include -IF:\pico\pico-sdk\src\rp2_common\hardware_dma\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\include -IF:\pico\pico-sdk\src\rp2_common\pico_async_context\include -IF:\Pico_Project\rp2040-freertos-template\build\pico-sdk\src\rp2_common\pico_cyw43_driver

C_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections

CXX_DEFINES = -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DCYW43_LWIP=0 -DFREE_RTOS_KERNEL_SMP=1 -DLIB_FREERTOS_KERNEL=1 -DLIB_PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_MULTICORE=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_USB=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_CONFIG_RTOS_ADAPTER_HEADER=F:/Pico_Project/rp2040-freertos-template/lib/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include/freertos_sdk_config.h -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_RP2040_USB_DEVICE_UFRAME_FIX=1 -DPICO_TARGET_NAME=\"rp2040-freertos-template\" -DPICO_USE_BLOCKED_RAM=0

CXX_INCLUDES = -IF:\Pico_Project\rp2040-freertos-template\src -IF:\pico\pico-sdk\src\common\pico_stdlib\include -IF:\pico\pico-sdk\src\rp2_common\hardware_gpio\include -IF:\pico\pico-sdk\src\common\pico_base\include -IF:\Pico_Project\rp2040-freertos-template\build\generated\pico_base -IF:\pico\pico-sdk\src\boards\include -IF:\pico\pico-sdk\src\rp2_common\pico_platform\include -IF:\pico\pico-sdk\src\rp2040\hardware_regs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_base\include -IF:\pico\pico-sdk\src\rp2040\hardware_structs\include -IF:\pico\pico-sdk\src\rp2_common\hardware_claim\include -IF:\pico\pico-sdk\src\rp2_common\hardware_sync\include -IF:\pico\pico-sdk\src\rp2_common\hardware_irq\include -IF:\pico\pico-sdk\src\common\pico_sync\include -IF:\pico\pico-sdk\src\common\pico_time\include -IF:\pico\pico-sdk\src\rp2_common\hardware_timer\include -IF:\pico\pico-sdk\src\common\pico_util\include -IF:\pico\pico-sdk\src\rp2_common\hardware_uart\include -IF:\pico\pico-sdk\src\rp2_common\hardware_resets\include -IF:\pico\pico-sdk\src\rp2_common\hardware_clocks\include -IF:\pico\pico-sdk\src\rp2_common\hardware_pll\include -IF:\pico\pico-sdk\src\rp2_common\hardware_vreg\include -IF:\pico\pico-sdk\src\rp2_common\hardware_watchdog\include -IF:\pico\pico-sdk\src\rp2_common\hardware_xosc\include -IF:\pico\pico-sdk\src\rp2_common\hardware_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_runtime\include -IF:\pico\pico-sdk\src\rp2_common\pico_printf\include -IF:\pico\pico-sdk\src\common\pico_bit_ops\include -IF:\pico\pico-sdk\src\common\pico_divider\include -IF:\pico\pico-sdk\src\rp2_common\pico_double\include -IF:\pico\pico-sdk\src\rp2_common\pico_float\include -IF:\pico\pico-sdk\src\rp2_common\pico_malloc\include -IF:\pico\pico-sdk\src\rp2_common\pico_bootrom\include -IF:\pico\pico-sdk\src\common\pico_binary_info\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio\include -IF:\pico\pico-sdk\src\rp2_common\pico_stdio_usb\include -IF:\pico\pico-sdk\src\rp2_common\pico_unique_id\include -IF:\pico\pico-sdk\src\rp2_common\hardware_flash\include -IF:\pico\pico-sdk\src\common\pico_usb_reset_interface\include -IF:\pico\pico-sdk\src\rp2_common\pico_int64_ops\include -IF:\pico\pico-sdk\src\rp2_common\pico_mem_ops\include -IF:\pico\pico-sdk\src\rp2_common\boot_stage2\include -IF:\pico\pico-sdk\lib\tinyusb\src -IF:\pico\pico-sdk\lib\tinyusb\src\common -IF:\pico\pico-sdk\lib\tinyusb\hw -IF:\pico\pico-sdk\src\rp2_common\pico_fix\rp2040_usb_device_enumeration\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\portable\ThirdParty\GCC\RP2040\include -IF:\Pico_Project\rp2040-freertos-template\lib\FreeRTOS-Kernel\include -IF:\pico\pico-sdk\src\rp2_common\hardware_exception\include -IF:\pico\pico-sdk\src\rp2_common\pico_multicore\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_arch\include -IF:\pico\pico-sdk\lib\cyw43-driver\src -IF:\pico\pico-sdk\lib\cyw43-driver\firmware -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\cybt_shared_bus -IF:\pico\pico-sdk\src\rp2_common\hardware_pio\include -IF:\pico\pico-sdk\src\rp2_common\hardware_dma\include -IF:\pico\pico-sdk\src\rp2_common\pico_cyw43_driver\include -IF:\pico\pico-sdk\src\rp2_common\pico_async_context\include -IF:\Pico_Project\rp2040-freertos-template\build\pico-sdk\src\rp2_common\pico_cyw43_driver

CXX_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit

