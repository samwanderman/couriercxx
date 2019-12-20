################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connection/Connection.cpp \
../couriercxx/connection/Info.cpp \
../couriercxx/connection/SerialPortBaseDatasource.cpp \
../couriercxx/connection/SerialPortBusDatasource.cpp \
../couriercxx/connection/SerialPortBusEventDrivenDatasource.cpp 

OBJS += \
./couriercxx/connection/Connection.o \
./couriercxx/connection/Info.o \
./couriercxx/connection/SerialPortBaseDatasource.o \
./couriercxx/connection/SerialPortBusDatasource.o \
./couriercxx/connection/SerialPortBusEventDrivenDatasource.o 

CPP_DEPS += \
./couriercxx/connection/Connection.d \
./couriercxx/connection/Info.d \
./couriercxx/connection/SerialPortBaseDatasource.d \
./couriercxx/connection/SerialPortBusDatasource.d \
./couriercxx/connection/SerialPortBusEventDrivenDatasource.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connection/%.o: ../couriercxx/connection/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DDEBUG -I"C:\mingw\mingw64\home\libpqxx\include" -I"C:\mingw\mingw64\home\libevent2\build\include" -I"C:\mingw\mingw64\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


