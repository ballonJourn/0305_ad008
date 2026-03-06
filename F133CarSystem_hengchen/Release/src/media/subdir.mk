################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/media/wav_utils.c \
../src/media/webrtc_echo.c 

CPP_SRCS += \
../src/media/audio_context.cpp \
../src/media/audio_linein.cpp \
../src/media/audio_recorder.cpp \
../src/media/audio_stream.cpp \
../src/media/media_context.cpp \
../src/media/media_parser.cpp \
../src/media/music_player.cpp 

OBJS += \
./src/media/audio_context.o \
./src/media/audio_linein.o \
./src/media/audio_recorder.o \
./src/media/audio_stream.o \
./src/media/media_context.o \
./src/media/media_parser.o \
./src/media/music_player.o \
./src/media/wav_utils.o \
./src/media/webrtc_echo.o 

C_DEPS += \
./src/media/wav_utils.d \
./src/media/webrtc_echo.d 

CPP_DEPS += \
./src/media/audio_context.d \
./src/media/audio_linein.d \
./src/media/audio_recorder.d \
./src/media/audio_stream.d \
./src/media/media_context.d \
./src/media/media_parser.d \
./src/media/music_player.d 


# Each subdirectory must supply rules for building sources it contributes
src/media/%.o: ../src/media/%.cpp
	@echo.exe 'Compile $(subst ../,,$<)'
	@riscv64-unknown-linux-musl-gcc -std=c++11 -I"D:\flythings\imageout\f133_0203\F133-B\F133CarSystem_hengchen\src" -O3 -Wall -c -fmessage-length=0 -pipe -Wformat -Werror=format-security -fstack-protector -fno-caller-saves -fexceptions -fPIC -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\easyui\2.3.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\log\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zkhardware\1.1.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zknet\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\openssl\1.1.1-g\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\ntp\1.0.1\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\base-utility\10.3.0\include" -I"..\src" -I"..\src\dependencies\include" -D__PLATFORM_F133__=1 -DUSE_ANDROID_LOG=1 -D_FORTIFY_SOURCE=1 -D_RELEASE=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
src/media/%.o: ../src/media/%.c
	@echo.exe 'Compile $(subst ../,,$<)'
	@riscv64-unknown-linux-musl-gcc -I"D:\flythings\imageout\f133_0203\F133-B\F133CarSystem_hengchen\src" -O3 -Wall -c -fmessage-length=0 -pipe -Wformat -Werror=format-security -fstack-protector -fno-caller-saves -fPIC -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\easyui\2.3.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\log\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zkhardware\1.1.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zknet\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\openssl\1.1.1-g\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\ntp\1.0.1\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\base-utility\10.3.0\include" -I"..\src" -I"..\src\dependencies\include" -D__PLATFORM_F133__=1 -DUSE_ANDROID_LOG=1 -D_FORTIFY_SOURCE=1 -D_RELEASE=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

