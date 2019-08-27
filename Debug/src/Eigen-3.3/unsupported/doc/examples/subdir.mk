################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/unsupported/doc/examples/BVH_Example.cpp \
../src/Eigen-3.3/unsupported/doc/examples/EulerAngles.cpp \
../src/Eigen-3.3/unsupported/doc/examples/FFT.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixExponential.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixFunction.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixLogarithm.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixPower.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixPower_optimal.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixSine.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixSinh.cpp \
../src/Eigen-3.3/unsupported/doc/examples/MatrixSquareRoot.cpp \
../src/Eigen-3.3/unsupported/doc/examples/PolynomialSolver1.cpp \
../src/Eigen-3.3/unsupported/doc/examples/PolynomialUtils1.cpp 

OBJS += \
./src/Eigen-3.3/unsupported/doc/examples/BVH_Example.o \
./src/Eigen-3.3/unsupported/doc/examples/EulerAngles.o \
./src/Eigen-3.3/unsupported/doc/examples/FFT.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixExponential.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixFunction.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixLogarithm.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixPower.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixPower_optimal.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSine.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSinh.o \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSquareRoot.o \
./src/Eigen-3.3/unsupported/doc/examples/PolynomialSolver1.o \
./src/Eigen-3.3/unsupported/doc/examples/PolynomialUtils1.o 

CPP_DEPS += \
./src/Eigen-3.3/unsupported/doc/examples/BVH_Example.d \
./src/Eigen-3.3/unsupported/doc/examples/EulerAngles.d \
./src/Eigen-3.3/unsupported/doc/examples/FFT.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixExponential.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixFunction.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixLogarithm.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixPower.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixPower_optimal.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSine.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSinh.d \
./src/Eigen-3.3/unsupported/doc/examples/MatrixSquareRoot.d \
./src/Eigen-3.3/unsupported/doc/examples/PolynomialSolver1.d \
./src/Eigen-3.3/unsupported/doc/examples/PolynomialUtils1.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/unsupported/doc/examples/%.o: ../src/Eigen-3.3/unsupported/doc/examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


