################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/gpio/GPIOPortBase.cpp 

OBJS += \
./couriercxx/connector/gpio/GPIOPortBase.o 

CPP_DEPS += \
./couriercxx/connector/gpio/GPIOPortBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/gpio/%.o: ../couriercxx/connector/gpio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


