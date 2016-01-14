################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fpu/fpu.cpp 

OBJS += \
./src/fpu/fpu.o 

CPP_DEPS += \
./src/fpu/fpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/fpu/%.o: ../src/fpu/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM g++ compiler'
	arm-xilinx-eabi-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -std=c++11 -I../../fpu_v1_1_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


