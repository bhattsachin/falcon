################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/indexer/Index.cpp \
../src/indexer/Indexer.cpp 

OBJS += \
./src/indexer/Index.o \
./src/indexer/Indexer.o 

CPP_DEPS += \
./src/indexer/Index.d \
./src/indexer/Indexer.d 


# Each subdirectory must supply rules for building sources it contributes
src/indexer/%.o: ../src/indexer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


