################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utils/SlideManager.cpp \
../src/utils/SlidingManager.cpp 

OBJS += \
./src/utils/SlideManager.o \
./src/utils/SlidingManager.o 

CPP_DEPS += \
./src/utils/SlideManager.d \
./src/utils/SlidingManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cpp
	@echo.exe 'Compile $(subst ../,,$<)'
	@riscv64-unknown-linux-musl-gcc -std=c++11 -I"D:\flythings\imageout\f133_0203\F133-B\F133CarSystem_hengchen\src" -O3 -Wall -c -fmessage-length=0 -pipe -Wformat -Werror=format-security -fstack-protector -fno-caller-saves -fexceptions -fPIC -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\easyui\2.3.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\log\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zkhardware\1.1.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zknet\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\openssl\1.1.1-g\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\ntp\1.0.1\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\base-utility\10.3.0\include" -I"..\src" -I"..\src\dependencies\include" -D__PLATFORM_F133__=1 -DUSE_ANDROID_LOG=1 -D_FORTIFY_SOURCE=1 -D_RELEASE=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

