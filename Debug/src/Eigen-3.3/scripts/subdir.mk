################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/scripts/eigen_gen_credits.cpp 

OBJS += \
./src/Eigen-3.3/scripts/eigen_gen_credits.o 

CPP_DEPS += \
./src/Eigen-3.3/scripts/eigen_gen_credits.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/scripts/%.o: ../src/Eigen-3.3/scripts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


