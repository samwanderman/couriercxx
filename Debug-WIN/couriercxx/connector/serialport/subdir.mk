################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/serialport/SerialPortBase.cpp \
../couriercxx/connector/serialport/SerialPortBus.cpp 

OBJS += \
./couriercxx/connector/serialport/SerialPortBase.o \
./couriercxx/connector/serialport/SerialPortBus.o 

CPP_DEPS += \
./couriercxx/connector/serialport/SerialPortBase.d \
./couriercxx/connector/serialport/SerialPortBus.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/serialport/%.o: ../couriercxx/connector/serialport/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DDEBUG -I"C:\mingw\mingw32\home\libpqxx\include" -I"C:\mingw\mingw32\home\libevent2\build\include" -I"C:\mingw\mingw32\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


