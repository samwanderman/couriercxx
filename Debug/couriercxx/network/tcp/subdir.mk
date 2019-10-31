################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/network/tcp/Client.cpp \
../couriercxx/network/tcp/Server.cpp 

OBJS += \
./couriercxx/network/tcp/Client.o \
./couriercxx/network/tcp/Server.o 

CPP_DEPS += \
./couriercxx/network/tcp/Client.d \
./couriercxx/network/tcp/Server.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/network/tcp/%.o: ../couriercxx/network/tcp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


