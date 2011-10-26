################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utilities/ConfigFile.cpp \
../src/utilities/ConfigHelper.cpp \
../src/utilities/DictionaryUtil.cpp \
../src/utilities/FileUtil.cpp \
../src/utilities/IDGenerator.cpp \
../src/utilities/Util.cpp 

OBJS += \
./src/utilities/ConfigFile.o \
./src/utilities/ConfigHelper.o \
./src/utilities/DictionaryUtil.o \
./src/utilities/FileUtil.o \
./src/utilities/IDGenerator.o \
./src/utilities/Util.o 

CPP_DEPS += \
./src/utilities/ConfigFile.d \
./src/utilities/ConfigHelper.d \
./src/utilities/DictionaryUtil.d \
./src/utilities/FileUtil.d \
./src/utilities/IDGenerator.d \
./src/utilities/Util.d 


# Each subdirectory must supply rules for building sources it contributes
src/utilities/%.o: ../src/utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


