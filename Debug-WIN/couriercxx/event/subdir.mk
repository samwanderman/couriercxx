################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../couriercxx/event/Dispatcher.cpp \
../couriercxx/event/DispatcherBase.cpp \
../couriercxx/event/IEvent.cpp \
../couriercxx/event/IListener.cpp \
../couriercxx/event/WrappedListener.cpp 

OBJS += \
./couriercxx/event/Dispatcher.o \
./couriercxx/event/DispatcherBase.o \
./couriercxx/event/IEvent.o \
./couriercxx/event/IListener.o \
./couriercxx/event/WrappedListener.o 

CPP_DEPS += \
./couriercxx/event/Dispatcher.d \
./couriercxx/event/DispatcherBase.d \
./couriercxx/event/IEvent.d \
./couriercxx/event/IListener.d \
./couriercxx/event/WrappedListener.d 


# Each subdirectory must supply rules for building sources it contributes
couriercxx/event/%.o: ../couriercxx/event/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DDEBUG -I"C:\mingw\mingw32\home\libpqxx\include" -I"C:\mingw\mingw32\home\libevent2\build\include" -I"C:\mingw\mingw32\home\libevent2\include" -O0 -g3 -Wall -c -fmessage-length=0 -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


