################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/Github/STM32Simple/CommonSrc/DS18B20_One_Wire.cpp \
D:/Github/STM32Simple/CommonSrc/HAL_Functions.cpp \
D:/Github/STM32Simple/CommonSrc/LCD_I2C.cpp \
D:/Github/STM32Simple/CommonSrc/main_loop.cpp \
D:/Github/STM32Simple/CommonSrc/temperature.cpp \
D:/Github/STM32Simple/CommonSrc/timer.cpp 

OBJS += \
./CommonSrc/DS18B20_One_Wire.o \
./CommonSrc/HAL_Functions.o \
./CommonSrc/LCD_I2C.o \
./CommonSrc/main_loop.o \
./CommonSrc/temperature.o \
./CommonSrc/timer.o 

CPP_DEPS += \
./CommonSrc/DS18B20_One_Wire.d \
./CommonSrc/HAL_Functions.d \
./CommonSrc/LCD_I2C.d \
./CommonSrc/main_loop.d \
./CommonSrc/temperature.d \
./CommonSrc/timer.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSrc/DS18B20_One_Wire.o: D:/Github/STM32Simple/CommonSrc/DS18B20_One_Wire.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/DS18B20_One_Wire.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/HAL_Functions.o: D:/Github/STM32Simple/CommonSrc/HAL_Functions.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/HAL_Functions.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/LCD_I2C.o: D:/Github/STM32Simple/CommonSrc/LCD_I2C.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/LCD_I2C.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/main_loop.o: D:/Github/STM32Simple/CommonSrc/main_loop.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/main_loop.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/temperature.o: D:/Github/STM32Simple/CommonSrc/temperature.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/temperature.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/timer.o: D:/Github/STM32Simple/CommonSrc/timer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CommonSrc/timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

