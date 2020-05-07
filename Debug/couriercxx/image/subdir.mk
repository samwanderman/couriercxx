################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/image/BMP.cpp \
../couriercxx/image/JPG.cpp 

OBJS += \
./couriercxx/image/BMP.o \
./couriercxx/image/JPG.o 

CPP_DEPS += \
./couriercxx/image/BMP.d \
./couriercxx/image/JPG.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/image/%.o: ../couriercxx/image/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


