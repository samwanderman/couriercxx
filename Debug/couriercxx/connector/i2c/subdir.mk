################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/i2c/I2CPortBase.cpp 

OBJS += \
./couriercxx/connector/i2c/I2CPortBase.o 

CPP_DEPS += \
./couriercxx/connector/i2c/I2CPortBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/i2c/%.o: ../couriercxx/connector/i2c/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


