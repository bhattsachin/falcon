################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/extraction/Crawler.cpp \
../src/extraction/DocumentQueue.cpp 

OBJS += \
./src/extraction/Crawler.o \
./src/extraction/DocumentQueue.o 

CPP_DEPS += \
./src/extraction/Crawler.d \
./src/extraction/DocumentQueue.d 


# Each subdirectory must supply rules for building sources it contributes
src/extraction/%.o: ../src/extraction/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/suz/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


