################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/net/Net.cpp \
../couriercxx/net/Sniffer.cpp 

OBJS += \
./couriercxx/net/Net.o \
./couriercxx/net/Sniffer.o 

CPP_DEPS += \
./couriercxx/net/Net.d \
./couriercxx/net/Sniffer.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/net/%.o: ../couriercxx/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


