################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Eigen-3.3/blas/f2c/chbmv.c \
../src/Eigen-3.3/blas/f2c/chpmv.c \
../src/Eigen-3.3/blas/f2c/complexdots.c \
../src/Eigen-3.3/blas/f2c/ctbmv.c \
../src/Eigen-3.3/blas/f2c/d_cnjg.c \
../src/Eigen-3.3/blas/f2c/drotm.c \
../src/Eigen-3.3/blas/f2c/drotmg.c \
../src/Eigen-3.3/blas/f2c/dsbmv.c \
../src/Eigen-3.3/blas/f2c/dspmv.c \
../src/Eigen-3.3/blas/f2c/dtbmv.c \
../src/Eigen-3.3/blas/f2c/lsame.c \
../src/Eigen-3.3/blas/f2c/r_cnjg.c \
../src/Eigen-3.3/blas/f2c/srotm.c \
../src/Eigen-3.3/blas/f2c/srotmg.c \
../src/Eigen-3.3/blas/f2c/ssbmv.c \
../src/Eigen-3.3/blas/f2c/sspmv.c \
../src/Eigen-3.3/blas/f2c/stbmv.c \
../src/Eigen-3.3/blas/f2c/zhbmv.c \
../src/Eigen-3.3/blas/f2c/zhpmv.c \
../src/Eigen-3.3/blas/f2c/ztbmv.c 

OBJS += \
./src/Eigen-3.3/blas/f2c/chbmv.o \
./src/Eigen-3.3/blas/f2c/chpmv.o \
./src/Eigen-3.3/blas/f2c/complexdots.o \
./src/Eigen-3.3/blas/f2c/ctbmv.o \
./src/Eigen-3.3/blas/f2c/d_cnjg.o \
./src/Eigen-3.3/blas/f2c/drotm.o \
./src/Eigen-3.3/blas/f2c/drotmg.o \
./src/Eigen-3.3/blas/f2c/dsbmv.o \
./src/Eigen-3.3/blas/f2c/dspmv.o \
./src/Eigen-3.3/blas/f2c/dtbmv.o \
./src/Eigen-3.3/blas/f2c/lsame.o \
./src/Eigen-3.3/blas/f2c/r_cnjg.o \
./src/Eigen-3.3/blas/f2c/srotm.o \
./src/Eigen-3.3/blas/f2c/srotmg.o \
./src/Eigen-3.3/blas/f2c/ssbmv.o \
./src/Eigen-3.3/blas/f2c/sspmv.o \
./src/Eigen-3.3/blas/f2c/stbmv.o \
./src/Eigen-3.3/blas/f2c/zhbmv.o \
./src/Eigen-3.3/blas/f2c/zhpmv.o \
./src/Eigen-3.3/blas/f2c/ztbmv.o 

C_DEPS += \
./src/Eigen-3.3/blas/f2c/chbmv.d \
./src/Eigen-3.3/blas/f2c/chpmv.d \
./src/Eigen-3.3/blas/f2c/complexdots.d \
./src/Eigen-3.3/blas/f2c/ctbmv.d \
./src/Eigen-3.3/blas/f2c/d_cnjg.d \
./src/Eigen-3.3/blas/f2c/drotm.d \
./src/Eigen-3.3/blas/f2c/drotmg.d \
./src/Eigen-3.3/blas/f2c/dsbmv.d \
./src/Eigen-3.3/blas/f2c/dspmv.d \
./src/Eigen-3.3/blas/f2c/dtbmv.d \
./src/Eigen-3.3/blas/f2c/lsame.d \
./src/Eigen-3.3/blas/f2c/r_cnjg.d \
./src/Eigen-3.3/blas/f2c/srotm.d \
./src/Eigen-3.3/blas/f2c/srotmg.d \
./src/Eigen-3.3/blas/f2c/ssbmv.d \
./src/Eigen-3.3/blas/f2c/sspmv.d \
./src/Eigen-3.3/blas/f2c/stbmv.d \
./src/Eigen-3.3/blas/f2c/zhbmv.d \
./src/Eigen-3.3/blas/f2c/zhpmv.d \
./src/Eigen-3.3/blas/f2c/ztbmv.d 


# Each subdirectory must supply rules for building sources it contributes
src/Eigen-3.3/blas/f2c/%.o: ../src/Eigen-3.3/blas/f2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


