################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/network/Net.cpp \
../couriercxx/network/Sniffer.cpp 

OBJS += \
./couriercxx/network/Net.o \
./couriercxx/network/Sniffer.o 

CPP_DEPS += \
./couriercxx/network/Net.d \
./couriercxx/network/Sniffer.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/network/%.o: ../couriercxx/network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DDEBUG -I"C:\mingw\mingw32\home\libpqxx\include" -I"C:\mingw\mingw32\home\libevent2\build\include" -I"C:\mingw\mingw32\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


