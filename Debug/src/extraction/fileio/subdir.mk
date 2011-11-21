################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/extraction/fileio/FileHandler.cpp 

OBJS += \
./src/extraction/fileio/FileHandler.o 

CPP_DEPS += \
./src/extraction/fileio/FileHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/extraction/fileio/%.o: ../src/extraction/fileio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/suz/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


