################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/bag.cpp \
../src/main.cpp \
../src/pennant.cpp 

OBJS += \
./src/bag.o \
./src/main.o \
./src/pennant.o 

CPP_DEPS += \
./src/bag.d \
./src/main.d \
./src/pennant.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/brix/workspace/bags/include" -I/opt/gtest-1.6.0/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


