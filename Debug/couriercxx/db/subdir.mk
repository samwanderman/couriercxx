################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/db/PostgresConnector.cpp 

OBJS += \
./couriercxx/db/PostgresConnector.o 

CPP_DEPS += \
./couriercxx/db/PostgresConnector.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/db/%.o: ../couriercxx/db/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


