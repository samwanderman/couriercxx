################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/device/bluetooth/BluetoothDevice.cpp 

OBJS += \
./couriercxx/device/bluetooth/BluetoothDevice.o 

CPP_DEPS += \
./couriercxx/device/bluetooth/BluetoothDevice.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/device/bluetooth/%.o: ../couriercxx/device/bluetooth/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


