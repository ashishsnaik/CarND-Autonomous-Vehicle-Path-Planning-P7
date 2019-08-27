################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Eigen-3.3/bench/tensors/benchmark_main.cc \
../src/Eigen-3.3/bench/tensors/contraction_benchmarks_cpu.cc \
../src/Eigen-3.3/bench/tensors/tensor_benchmarks_cpu.cc \
../src/Eigen-3.3/bench/tensors/tensor_benchmarks_sycl.cc 

CC_DEPS += \
./src/Eigen-3.3/bench/tensors/benchmark_main.d \
./src/Eigen-3.3/bench/tensors/contraction_benchmarks_cpu.d \
./src/Eigen-3.3/bench/tensors/tensor_benchmarks_cpu.d \
./src/Eigen-3.3/bench/tensors/tensor_benchmarks_sycl.d 

OBJS += \
./src/Eigen-3.3/bench/tensors/benchmark_main.o \
./src/Eigen-3.3/bench/tensors/contraction_benchmarks_cpu.o \
./src/Eigen-3.3/bench/tensors/tensor_benchmarks_cpu.o \
./src/Eigen-3.3/bench/tensors/tensor_benchmarks_sycl.o 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/bench/tensors/%.o: ../src/Eigen-3.3/bench/tensors/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


