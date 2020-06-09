################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/sound/PWM.cpp 

OBJS += \
./couriercxx/sound/PWM.o 

CPP_DEPS += \
./couriercxx/sound/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/sound/%.o: ../couriercxx/sound/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


