################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/blas/complex_double.cpp \
../src/Eigen-3.3/blas/complex_single.cpp \
../src/Eigen-3.3/blas/double.cpp \
../src/Eigen-3.3/blas/single.cpp \
../src/Eigen-3.3/blas/xerbla.cpp 

OBJS += \
./src/Eigen-3.3/blas/complex_double.o \
./src/Eigen-3.3/blas/complex_single.o \
./src/Eigen-3.3/blas/double.o \
./src/Eigen-3.3/blas/single.o \
./src/Eigen-3.3/blas/xerbla.o 

CPP_DEPS += \
./src/Eigen-3.3/blas/complex_double.d \
./src/Eigen-3.3/blas/complex_single.d \
./src/Eigen-3.3/blas/double.d \
./src/Eigen-3.3/blas/single.d \
./src/Eigen-3.3/blas/xerbla.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/blas/%.o: ../src/Eigen-3.3/blas/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


