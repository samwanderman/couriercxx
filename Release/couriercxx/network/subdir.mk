################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/network/Net.cpp \
../couriercxx/network/Sniffer.cpp 

OBJS += \
./couriercxx/network/Net.o \
./couriercxx/network/Sniffer.o 

CPP_DEPS += \
./couriercxx/network/Net.d \
./couriercxx/network/Sniffer.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/network/%.o: ../couriercxx/network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


