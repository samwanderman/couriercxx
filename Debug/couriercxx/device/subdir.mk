################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/device/IDevice.cpp 

OBJS += \
./couriercxx/device/IDevice.o 

CPP_DEPS += \
./couriercxx/device/IDevice.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/device/%.o: ../couriercxx/device/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


