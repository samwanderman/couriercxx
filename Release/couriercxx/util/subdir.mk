################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/util/Config.cpp \
../couriercxx/util/ConfigBase.cpp \
../couriercxx/util/Daemon.cpp \
../couriercxx/util/Hardware.cpp \
../couriercxx/util/IO.cpp \
../couriercxx/util/String.cpp \
../couriercxx/util/Time.cpp 

OBJS += \
./couriercxx/util/Config.o \
./couriercxx/util/ConfigBase.o \
./couriercxx/util/Daemon.o \
./couriercxx/util/Hardware.o \
./couriercxx/util/IO.o \
./couriercxx/util/String.o \
./couriercxx/util/Time.o 

CPP_DEPS += \
./couriercxx/util/Config.d \
./couriercxx/util/ConfigBase.d \
./couriercxx/util/Daemon.d \
./couriercxx/util/Hardware.d \
./couriercxx/util/IO.d \
./couriercxx/util/String.d \
./couriercxx/util/Time.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/util/%.o: ../couriercxx/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


