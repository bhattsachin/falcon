################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/parser/lang/en/LangUtil.cpp \
../src/parser/lang/en/PlainTextParser.cpp \
../src/parser/lang/en/SemWikiParser.cpp \
../src/parser/lang/en/WikiParser.cpp 

OBJS += \
./src/parser/lang/en/LangUtil.o \
./src/parser/lang/en/PlainTextParser.o \
./src/parser/lang/en/SemWikiParser.o \
./src/parser/lang/en/WikiParser.o 

CPP_DEPS += \
./src/parser/lang/en/LangUtil.d \
./src/parser/lang/en/PlainTextParser.d \
./src/parser/lang/en/SemWikiParser.d \
./src/parser/lang/en/WikiParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/parser/lang/en/%.o: ../src/parser/lang/en/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


