################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../block.cpp \
../dirent.cpp \
../inode.cpp \
../main.cpp \
../user.cpp 

OBJS += \
./block.o \
./dirent.o \
./inode.o \
./main.o \
./user.o 

CPP_DEPS += \
./block.d \
./dirent.d \
./inode.d \
./main.d \
./user.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


