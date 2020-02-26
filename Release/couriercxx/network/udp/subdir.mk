################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/network/udp/Client.cpp \
../couriercxx/network/udp/Server.cpp 

OBJS += \
./couriercxx/network/udp/Client.o \
./couriercxx/network/udp/Server.o 

CPP_DEPS += \
./couriercxx/network/udp/Client.d \
./couriercxx/network/udp/Server.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/network/udp/%.o: ../couriercxx/network/udp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


