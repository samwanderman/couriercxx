################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include couriercxx/util/subdir.mk
-include couriercxx/sound/subdir.mk
-include couriercxx/property/subdir.mk
-include couriercxx/network/udp/subdir.mk
-include couriercxx/network/tcp/subdir.mk
-include couriercxx/network/http/subdir.mk
-include couriercxx/network/subdir.mk
-include couriercxx/logger/subdir.mk
-include couriercxx/image/subdir.mk
-include couriercxx/event/event/subdir.mk
-include couriercxx/event/subdir.mk
-include couriercxx/device/bluetooth/subdir.mk
-include couriercxx/device/subdir.mk
-include couriercxx/db/subdir.mk
-include couriercxx/connector/udp/subdir.mk
-include couriercxx/connector/spi/subdir.mk
-include couriercxx/connector/serialport/subdir.mk
-include couriercxx/connector/scsi/subdir.mk
-include couriercxx/connector/i2c/subdir.mk
-include couriercxx/connector/gpio/subdir.mk
-include couriercxx/connector/bluetooth/subdir.mk
-include couriercxx/connector/subdir.mk
-include couriercxx/connection/event/subdir.mk
-include couriercxx/connection/subdir.mk
-include Release-WIN/couriercxx/util/subdir.mk
-include Release-WIN/couriercxx/sound/subdir.mk
-include Release-WIN/couriercxx/property/subdir.mk
-include Release-WIN/couriercxx/network/udp/subdir.mk
-include Release-WIN/couriercxx/network/tcp/subdir.mk
-include Release-WIN/couriercxx/network/http/subdir.mk
-include Release-WIN/couriercxx/network/subdir.mk
-include Release-WIN/couriercxx/logger/subdir.mk
-include Release-WIN/couriercxx/image/subdir.mk
-include Release-WIN/couriercxx/event/event/subdir.mk
-include Release-WIN/couriercxx/event/subdir.mk
-include Release-WIN/couriercxx/device/bluetooth/subdir.mk
-include Release-WIN/couriercxx/device/subdir.mk
-include Release-WIN/couriercxx/db/subdir.mk
-include Release-WIN/couriercxx/connector/udp/subdir.mk
-include Release-WIN/couriercxx/connector/spi/subdir.mk
-include Release-WIN/couriercxx/connector/serialport/subdir.mk
-include Release-WIN/couriercxx/connector/scsi/subdir.mk
-include Release-WIN/couriercxx/connector/i2c/subdir.mk
-include Release-WIN/couriercxx/connector/gpio/subdir.mk
-include Release-WIN/couriercxx/connector/bluetooth/subdir.mk
-include Release-WIN/couriercxx/connector/subdir.mk
-include Release-WIN/couriercxx/connection/event/subdir.mk
-include Release-WIN/couriercxx/connection/subdir.mk
-include Debug-WIN/couriercxx/util/subdir.mk
-include Debug-WIN/couriercxx/sound/subdir.mk
-include Debug-WIN/couriercxx/property/subdir.mk
-include Debug-WIN/couriercxx/network/udp/subdir.mk
-include Debug-WIN/couriercxx/network/tcp/subdir.mk
-include Debug-WIN/couriercxx/network/http/subdir.mk
-include Debug-WIN/couriercxx/network/subdir.mk
-include Debug-WIN/couriercxx/logger/subdir.mk
-include Debug-WIN/couriercxx/image/subdir.mk
-include Debug-WIN/couriercxx/event/event/subdir.mk
-include Debug-WIN/couriercxx/event/subdir.mk
-include Debug-WIN/couriercxx/device/bluetooth/subdir.mk
-include Debug-WIN/couriercxx/device/subdir.mk
-include Debug-WIN/couriercxx/db/subdir.mk
-include Debug-WIN/couriercxx/connector/udp/subdir.mk
-include Debug-WIN/couriercxx/connector/spi/subdir.mk
-include Debug-WIN/couriercxx/connector/serialport/subdir.mk
-include Debug-WIN/couriercxx/connector/scsi/subdir.mk
-include Debug-WIN/couriercxx/connector/i2c/subdir.mk
-include Debug-WIN/couriercxx/connector/gpio/subdir.mk
-include Debug-WIN/couriercxx/connector/bluetooth/subdir.mk
-include Debug-WIN/couriercxx/connector/subdir.mk
-include Debug-WIN/couriercxx/connection/event/subdir.mk
-include Debug-WIN/couriercxx/connection/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libCourierCXX.a

# Tool invocations
libCourierCXX.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Archiver'
	ar -r  "libCourierCXX.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(ARCHIVES)$(C_DEPS)$(CPP_DEPS) libCourierCXX.a
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
