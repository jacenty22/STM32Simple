################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/STM32Simple/CommonSrc/DS18B20_One_Wire.c \
D:/Github/STM32Simple/CommonSrc/HAL_Functions.c \
D:/Github/STM32Simple/CommonSrc/LCD_I2C.c \
D:/Github/STM32Simple/CommonSrc/main_loop.c \
D:/Github/STM32Simple/CommonSrc/temperature.c \
D:/Github/STM32Simple/CommonSrc/timer.c 

OBJS += \
./CommonSrc/DS18B20_One_Wire.o \
./CommonSrc/HAL_Functions.o \
./CommonSrc/LCD_I2C.o \
./CommonSrc/main_loop.o \
./CommonSrc/temperature.o \
./CommonSrc/timer.o 

C_DEPS += \
./CommonSrc/DS18B20_One_Wire.d \
./CommonSrc/HAL_Functions.d \
./CommonSrc/LCD_I2C.d \
./CommonSrc/main_loop.d \
./CommonSrc/temperature.d \
./CommonSrc/timer.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSrc/DS18B20_One_Wire.o: D:/Github/STM32Simple/CommonSrc/DS18B20_One_Wire.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/DS18B20_One_Wire.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/HAL_Functions.o: D:/Github/STM32Simple/CommonSrc/HAL_Functions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/HAL_Functions.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/LCD_I2C.o: D:/Github/STM32Simple/CommonSrc/LCD_I2C.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/LCD_I2C.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/main_loop.o: D:/Github/STM32Simple/CommonSrc/main_loop.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/main_loop.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/temperature.o: D:/Github/STM32Simple/CommonSrc/temperature.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/temperature.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonSrc/timer.o: D:/Github/STM32Simple/CommonSrc/timer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../../../CommonSrc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../../../CommonInc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CommonSrc/timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

