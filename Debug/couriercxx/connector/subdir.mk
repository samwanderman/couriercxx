################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/IConnectorBase.cpp 

OBJS += \
./couriercxx/connector/IConnectorBase.o 

CPP_DEPS += \
./couriercxx/connector/IConnectorBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/%.o: ../couriercxx/connector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


