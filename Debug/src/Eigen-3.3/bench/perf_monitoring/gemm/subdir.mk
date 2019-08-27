################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/bench/perf_monitoring/gemm/gemm.cpp \
../src/Eigen-3.3/bench/perf_monitoring/gemm/lazy_gemm.cpp 

OBJS += \
./src/Eigen-3.3/bench/perf_monitoring/gemm/gemm.o \
./src/Eigen-3.3/bench/perf_monitoring/gemm/lazy_gemm.o 

CPP_DEPS += \
./src/Eigen-3.3/bench/perf_monitoring/gemm/gemm.d \
./src/Eigen-3.3/bench/perf_monitoring/gemm/lazy_gemm.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/bench/perf_monitoring/gemm/%.o: ../src/Eigen-3.3/bench/perf_monitoring/gemm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


