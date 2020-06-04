################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connector/scsi/SCSIPortBase.cpp 

OBJS += \
./couriercxx/connector/scsi/SCSIPortBase.o 

CPP_DEPS += \
./couriercxx/connector/scsi/SCSIPortBase.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connector/scsi/%.o: ../couriercxx/connector/scsi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


