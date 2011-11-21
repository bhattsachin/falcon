################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controller/ParsingController.cpp \
../src/controller/ParsingIndexingBoostController.cpp \
../src/controller/ParsingIndexingController.cpp \
../src/controller/WikiController.cpp 

OBJS += \
./src/controller/ParsingController.o \
./src/controller/ParsingIndexingBoostController.o \
./src/controller/ParsingIndexingController.o \
./src/controller/WikiController.o 

CPP_DEPS += \
./src/controller/ParsingController.d \
./src/controller/ParsingIndexingBoostController.d \
./src/controller/ParsingIndexingController.d \
./src/controller/WikiController.d 


# Each subdirectory must supply rules for building sources it contributes
src/controller/%.o: ../src/controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/suz/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


