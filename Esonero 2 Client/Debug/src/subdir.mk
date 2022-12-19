################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Esonero\ 2\ Client.c 

C_DEPS += \
./src/Esonero\ 2\ Client.d 

OBJS += \
./src/Esonero\ 2\ Client.o 


# Each subdirectory must supply rules for building sources it contributes
src/Esonero\ 2\ Client.o: ../src/Esonero\ 2\ Client.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Esonero 2 Client.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Esonero\ 2\ Client.d ./src/Esonero\ 2\ Client.o

.PHONY: clean-src

