################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/parser/BaseParser.cpp \
../src/parser/BoostParser.cpp \
../src/parser/BoostWikiParser.cpp 

OBJS += \
./src/parser/BaseParser.o \
./src/parser/BoostParser.o \
./src/parser/BoostWikiParser.o 

CPP_DEPS += \
./src/parser/BaseParser.d \
./src/parser/BoostParser.d \
./src/parser/BoostWikiParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/parser/%.o: ../src/parser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/suz/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


