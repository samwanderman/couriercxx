################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/event/event/EventTimeout.cpp 

OBJS += \
./couriercxx/event/event/EventTimeout.o 

CPP_DEPS += \
./couriercxx/event/event/EventTimeout.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/event/event/%.o: ../couriercxx/event/event/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


