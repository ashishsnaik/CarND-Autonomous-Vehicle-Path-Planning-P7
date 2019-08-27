################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eigen-3.3/demos/opengl/camera.cpp \
../src/Eigen-3.3/demos/opengl/gpuhelper.cpp \
../src/Eigen-3.3/demos/opengl/icosphere.cpp \
../src/Eigen-3.3/demos/opengl/quaternion_demo.cpp \
../src/Eigen-3.3/demos/opengl/trackball.cpp 

OBJS += \
./src/Eigen-3.3/demos/opengl/camera.o \
./src/Eigen-3.3/demos/opengl/gpuhelper.o \
./src/Eigen-3.3/demos/opengl/icosphere.o \
./src/Eigen-3.3/demos/opengl/quaternion_demo.o \
./src/Eigen-3.3/demos/opengl/trackball.o 

CPP_DEPS += \
./src/Eigen-3.3/demos/opengl/camera.d \
./src/Eigen-3.3/demos/opengl/gpuhelper.d \
./src/Eigen-3.3/demos/opengl/icosphere.d \
./src/Eigen-3.3/demos/opengl/quaternion_demo.d \
./src/Eigen-3.3/demos/opengl/trackball.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/demos/opengl/%.o: ../src/Eigen-3.3/demos/opengl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


