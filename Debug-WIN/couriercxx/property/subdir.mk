################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/property/IProperty.cpp \
../couriercxx/property/Property.cpp \
../couriercxx/property/PropertyDatabase.cpp \
../couriercxx/property/PropertyFile.cpp 

OBJS += \
./couriercxx/property/IProperty.o \
./couriercxx/property/Property.o \
./couriercxx/property/PropertyDatabase.o \
./couriercxx/property/PropertyFile.o 

CPP_DEPS += \
./couriercxx/property/IProperty.d \
./couriercxx/property/Property.d \
./couriercxx/property/PropertyDatabase.d \
./couriercxx/property/PropertyFile.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/property/%.o: ../couriercxx/property/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DDEBUG -I"C:\mingw\mingw32\home\libpqxx\include" -I"C:\mingw\mingw32\home\libevent2\build\include" -I"C:\mingw\mingw32\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


