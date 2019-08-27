################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../src/Eigen-3.3/bench/btl/data/mean.cxx \
../src/Eigen-3.3/bench/btl/data/regularize.cxx \
../src/Eigen-3.3/bench/btl/data/smooth.cxx 

CXX_DEPS += \
./src/Eigen-3.3/bench/btl/data/mean.d \
./src/Eigen-3.3/bench/btl/data/regularize.d \
./src/Eigen-3.3/bench/btl/data/smooth.d 

OBJS += \
./src/Eigen-3.3/bench/btl/data/mean.o \
./src/Eigen-3.3/bench/btl/data/regularize.o \
./src/Eigen-3.3/bench/btl/data/smooth.o 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/bench/btl/data/%.o: ../src/Eigen-3.3/bench/btl/data/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


