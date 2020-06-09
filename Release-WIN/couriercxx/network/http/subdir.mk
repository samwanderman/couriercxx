################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/network/http/Client.cpp \
../couriercxx/network/http/Request.cpp \
../couriercxx/network/http/Server.cpp 

OBJS += \
./couriercxx/network/http/Client.o \
./couriercxx/network/http/Request.o \
./couriercxx/network/http/Server.o 

CPP_DEPS += \
./couriercxx/network/http/Client.d \
./couriercxx/network/http/Request.d \
./couriercxx/network/http/Server.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/network/http/%.o: ../couriercxx/network/http/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


