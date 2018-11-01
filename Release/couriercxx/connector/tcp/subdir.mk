################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/tcp/TCPPortBase.cpp 

OBJS += \
./couriercxx/connector/tcp/TCPPortBase.o 

CPP_DEPS += \
./couriercxx/connector/tcp/TCPPortBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/tcp/%.o: ../couriercxx/connector/tcp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


