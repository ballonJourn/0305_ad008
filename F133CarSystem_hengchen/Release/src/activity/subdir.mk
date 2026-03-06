################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/activity/FMemitActivity.cpp \
../src/activity/PhotoAlbumActivity.cpp \
../src/activity/TestRecordActivity.cpp \
../src/activity/UserImeActivity.cpp \
../src/activity/btContactsActivity.cpp \
../src/activity/btDialActivity.cpp \
../src/activity/btIncomingActivity.cpp \
../src/activity/btMusicActivity.cpp \
../src/activity/btOutgoingActivity.cpp \
../src/activity/btRecordsActivity.cpp \
../src/activity/btsettingActivity.cpp \
../src/activity/callingActivity.cpp \
../src/activity/ctrlbarActivity.cpp \
../src/activity/floatwndActivity.cpp \
../src/activity/linkhelpActivity.cpp \
../src/activity/lylinkviewActivity.cpp \
../src/activity/mainActivity.cpp \
../src/activity/mcubtUpdActivity.cpp \
../src/activity/musicActivity.cpp \
../src/activity/navibar.cpp \
../src/activity/reverseActivity.cpp \
../src/activity/screenOffActivity.cpp \
../src/activity/setfactoryActivity.cpp \
../src/activity/setlinkActivity.cpp \
../src/activity/setreverseActivity.cpp \
../src/activity/setshowActivity.cpp \
../src/activity/settingsActivity.cpp \
../src/activity/setvoiceActivity.cpp \
../src/activity/soundEffectActivity.cpp \
../src/activity/soundFieldActivity.cpp \
../src/activity/statusbar.cpp \
../src/activity/tirePressureActivity.cpp \
../src/activity/topbarActivity.cpp \
../src/activity/videoActivity.cpp \
../src/activity/wifisettingActivity.cpp \
../src/activity/windowActivity.cpp 

OBJS += \
./src/activity/FMemitActivity.o \
./src/activity/PhotoAlbumActivity.o \
./src/activity/TestRecordActivity.o \
./src/activity/UserImeActivity.o \
./src/activity/btContactsActivity.o \
./src/activity/btDialActivity.o \
./src/activity/btIncomingActivity.o \
./src/activity/btMusicActivity.o \
./src/activity/btOutgoingActivity.o \
./src/activity/btRecordsActivity.o \
./src/activity/btsettingActivity.o \
./src/activity/callingActivity.o \
./src/activity/ctrlbarActivity.o \
./src/activity/floatwndActivity.o \
./src/activity/linkhelpActivity.o \
./src/activity/lylinkviewActivity.o \
./src/activity/mainActivity.o \
./src/activity/mcubtUpdActivity.o \
./src/activity/musicActivity.o \
./src/activity/navibar.o \
./src/activity/reverseActivity.o \
./src/activity/screenOffActivity.o \
./src/activity/setfactoryActivity.o \
./src/activity/setlinkActivity.o \
./src/activity/setreverseActivity.o \
./src/activity/setshowActivity.o \
./src/activity/settingsActivity.o \
./src/activity/setvoiceActivity.o \
./src/activity/soundEffectActivity.o \
./src/activity/soundFieldActivity.o \
./src/activity/statusbar.o \
./src/activity/tirePressureActivity.o \
./src/activity/topbarActivity.o \
./src/activity/videoActivity.o \
./src/activity/wifisettingActivity.o \
./src/activity/windowActivity.o 

CPP_DEPS += \
./src/activity/FMemitActivity.d \
./src/activity/PhotoAlbumActivity.d \
./src/activity/TestRecordActivity.d \
./src/activity/UserImeActivity.d \
./src/activity/btContactsActivity.d \
./src/activity/btDialActivity.d \
./src/activity/btIncomingActivity.d \
./src/activity/btMusicActivity.d \
./src/activity/btOutgoingActivity.d \
./src/activity/btRecordsActivity.d \
./src/activity/btsettingActivity.d \
./src/activity/callingActivity.d \
./src/activity/ctrlbarActivity.d \
./src/activity/floatwndActivity.d \
./src/activity/linkhelpActivity.d \
./src/activity/lylinkviewActivity.d \
./src/activity/mainActivity.d \
./src/activity/mcubtUpdActivity.d \
./src/activity/musicActivity.d \
./src/activity/navibar.d \
./src/activity/reverseActivity.d \
./src/activity/screenOffActivity.d \
./src/activity/setfactoryActivity.d \
./src/activity/setlinkActivity.d \
./src/activity/setreverseActivity.d \
./src/activity/setshowActivity.d \
./src/activity/settingsActivity.d \
./src/activity/setvoiceActivity.d \
./src/activity/soundEffectActivity.d \
./src/activity/soundFieldActivity.d \
./src/activity/statusbar.d \
./src/activity/tirePressureActivity.d \
./src/activity/topbarActivity.d \
./src/activity/videoActivity.d \
./src/activity/wifisettingActivity.d \
./src/activity/windowActivity.d 


# Each subdirectory must supply rules for building sources it contributes
src/activity/%.o: ../src/activity/%.cpp
	@echo.exe 'Compile $(subst ../,,$<)'
	@riscv64-unknown-linux-musl-gcc -std=c++11 -I"D:\flythings\imageout\f133_0203\F133-B\F133CarSystem_hengchen\src" -O3 -Wall -c -fmessage-length=0 -pipe -Wformat -Werror=format-security -fstack-protector -fno-caller-saves -fexceptions -fPIC -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\easyui\2.3.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\log\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zkhardware\1.1.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zknet\1.0.0\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\openssl\1.1.1-g\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\ntp\1.0.1\include" -I"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\base-utility\10.3.0\include" -I"..\src" -I"..\src\dependencies\include" -D__PLATFORM_F133__=1 -DUSE_ANDROID_LOG=1 -D_FORTIFY_SOURCE=1 -D_RELEASE=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

