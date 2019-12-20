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
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DDEBUG -I"C:\mingw\mingw64\home\libpqxx\include" -I"C:\mingw\mingw64\home\libevent2\build\include" -I"C:\mingw\mingw64\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


