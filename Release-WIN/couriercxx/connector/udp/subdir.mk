################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/udp/UDPPortBase.cpp 

OBJS += \
./couriercxx/connector/udp/UDPPortBase.o 

CPP_DEPS += \
./couriercxx/connector/udp/UDPPortBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/udp/%.o: ../couriercxx/connector/udp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

