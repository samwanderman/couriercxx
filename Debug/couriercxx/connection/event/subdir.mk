################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/connection/event/EventConnection.cpp \
../couriercxx/connection/event/EventRead.cpp \
../couriercxx/connection/event/EventStatus.cpp \
../couriercxx/connection/event/EventWrite.cpp 

OBJS += \
./couriercxx/connection/event/EventConnection.o \
./couriercxx/connection/event/EventRead.o \
./couriercxx/connection/event/EventStatus.o \
./couriercxx/connection/event/EventWrite.o 

CPP_DEPS += \
./couriercxx/connection/event/EventConnection.d \
./couriercxx/connection/event/EventRead.d \
./couriercxx/connection/event/EventStatus.d \
./couriercxx/connection/event/EventWrite.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/connection/event/%.o: ../couriercxx/connection/event/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


