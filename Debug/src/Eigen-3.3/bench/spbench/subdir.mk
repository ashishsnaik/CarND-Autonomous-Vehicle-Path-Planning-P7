################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/bench/spbench/sp_solver.cpp \
../src/Eigen-3.3/bench/spbench/spbenchsolver.cpp \
../src/Eigen-3.3/bench/spbench/test_sparseLU.cpp 

OBJS += \
./src/Eigen-3.3/bench/spbench/sp_solver.o \
./src/Eigen-3.3/bench/spbench/spbenchsolver.o \
./src/Eigen-3.3/bench/spbench/test_sparseLU.o 

CPP_DEPS += \
./src/Eigen-3.3/bench/spbench/sp_solver.d \
./src/Eigen-3.3/bench/spbench/spbenchsolver.d \
./src/Eigen-3.3/bench/spbench/test_sparseLU.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/bench/spbench/%.o: ../src/Eigen-3.3/bench/spbench/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


