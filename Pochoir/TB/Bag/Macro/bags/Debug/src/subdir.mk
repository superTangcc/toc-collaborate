################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/bag.cpp \
../src/pennant.cpp \
../src/test_bag.cpp \
../src/test_main.cpp \
../src/test_pennant.cpp 

OBJS += \
./src/bag.o \
./src/pennant.o \
./src/test_bag.o \
./src/test_main.o \
./src/test_pennant.o 

CPP_DEPS += \
./src/bag.d \
./src/pennant.d \
./src/test_bag.d \
./src/test_main.d \
./src/test_pennant.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/brix/workspace/bags/include" -I/opt/gtest-1.6.0/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


