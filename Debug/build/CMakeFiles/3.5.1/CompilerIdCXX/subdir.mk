################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../build/CMakeFiles/3.5.1/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./build/CMakeFiles/3.5.1/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./build/CMakeFiles/3.5.1/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
build/CMakeFiles/3.5.1/CompilerIdCXX/%.o: ../build/CMakeFiles/3.5.1/CompilerIdCXX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


