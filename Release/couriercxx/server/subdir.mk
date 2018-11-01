################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/server/Request.cpp \
../couriercxx/server/Server.cpp 

OBJS += \
./couriercxx/server/Request.o \
./couriercxx/server/Server.o 

CPP_DEPS += \
./couriercxx/server/Request.d \
./couriercxx/server/Server.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/server/%.o: ../couriercxx/server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


