################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/util/ByteOrder.cpp \
../couriercxx/util/Clock.cpp \
../couriercxx/util/Hardware.cpp \
../couriercxx/util/IO.cpp \
../couriercxx/util/SignalWatcher.cpp \
../couriercxx/util/String.cpp \
../couriercxx/util/System.cpp 

OBJS += \
./couriercxx/util/ByteOrder.o \
./couriercxx/util/Clock.o \
./couriercxx/util/Hardware.o \
./couriercxx/util/IO.o \
./couriercxx/util/SignalWatcher.o \
./couriercxx/util/String.o \
./couriercxx/util/System.o 

CPP_DEPS += \
./couriercxx/util/ByteOrder.d \
./couriercxx/util/Clock.d \
./couriercxx/util/Hardware.d \
./couriercxx/util/IO.d \
./couriercxx/util/SignalWatcher.d \
./couriercxx/util/String.d \
./couriercxx/util/System.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/util/%.o: ../couriercxx/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


