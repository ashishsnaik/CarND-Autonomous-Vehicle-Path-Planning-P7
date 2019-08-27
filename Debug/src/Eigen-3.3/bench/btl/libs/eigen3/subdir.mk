################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/bench/btl/libs/eigen3/btl_tiny_eigen3.cpp \
../src/Eigen-3.3/bench/btl/libs/eigen3/main_adv.cpp \
../src/Eigen-3.3/bench/btl/libs/eigen3/main_linear.cpp \
../src/Eigen-3.3/bench/btl/libs/eigen3/main_matmat.cpp \
../src/Eigen-3.3/bench/btl/libs/eigen3/main_vecmat.cpp 

OBJS += \
./src/Eigen-3.3/bench/btl/libs/eigen3/btl_tiny_eigen3.o \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_adv.o \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_linear.o \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_matmat.o \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_vecmat.o 

CPP_DEPS += \
./src/Eigen-3.3/bench/btl/libs/eigen3/btl_tiny_eigen3.d \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_adv.d \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_linear.d \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_matmat.d \
./src/Eigen-3.3/bench/btl/libs/eigen3/main_vecmat.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/bench/btl/libs/eigen3/%.o: ../src/Eigen-3.3/bench/btl/libs/eigen3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


