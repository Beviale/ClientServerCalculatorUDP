################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Esonero\ 2\ Server.c 

C_DEPS += \
./src/Esonero\ 2\ Server.d 

OBJS += \
./src/Esonero\ 2\ Server.o 


# Each subdirectory must supply rules for building sources it contributes
src/Esonero\ 2\ Server.o: ../src/Esonero\ 2\ Server.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"C:\Users\bevia\OneDrive\Documenti\Università\2 anno\Reti di calcolatori\Eclipse\Librerie UDP" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Esonero 2 Server.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Esonero\ 2\ Server.d ./src/Esonero\ 2\ Server.o

.PHONY: clean-src

