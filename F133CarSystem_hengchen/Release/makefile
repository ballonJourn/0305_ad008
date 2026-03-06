################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/utils/subdir.mk
-include src/uart/subdir.mk
-include src/tire/subdir.mk
-include src/system/subdir.mk
-include src/net/subdir.mk
-include src/misc/subdir.mk
-include src/media/subdir.mk
-include src/logic/subdir.mk
-include src/link/subdir.mk
-include src/bt/subdir.mk
-include src/activity/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

SHELL = C:\Windows\System32\cmd.exe

# Manifest targets objects variables
# Manifest dependencies library
DEPENDENCIES_LINK_FLAGS := \
	-Wl,--start-group \
	-l:liblylinkui.so -l:libwebrtc.so -l:libzkmedia.a \
	-l:libeasyui.so \
	-l:liblog.so \
	-l:libzkhardware.so \
	-l:libzknet.so \
	-l:libssl.a -l:libcrypto.a \
	-l:libntp.a \
	-l:libbase-utility.a \
	-pthread \
	-lm \
	-ldl \
	-lstdc++ \
	-Wl,--end-group \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\easyui\2.3.0\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\log\1.0.0\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zkhardware\1.1.0\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\zknet\1.0.0\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\openssl\1.1.1-g\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\ntp\1.0.1\lib" \
	-L"D:\flythings\FlyThingsIDE\bin\.dep\public\f133\base-utility\10.3.0\lib" \
	-L"..\src\dependencies\lib"

# Add inputs and outputs from these tool invocations to the build variables 

# 所有目标
all: libzkgui.so

# 工具调用
libzkgui.so: $(OBJS) $(USER_OBJS)
	@echo.exe 'Linking $@'
	@riscv64-unknown-linux-musl-gcc -s -Wl,-z,now -Wl,-z,relro -Wl,-z,defs -Wl,--warn-common -Wl,-z,combreloc -Wl,--warn-once -shared -o "libzkgui.so" $(OBJS) $(USER_OBJS) $(LIBS) $(DEPENDENCIES_LINK_FLAGS) -Wl,-Bsymbolic 

# 其他目标
clean:
	-@$(RM) $(LIBRARIES)$(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(ARCHIVES)$(C_DEPS)$(CPP_DEPS) libzkgui.so
	-@echo.exe ' '

.PHONY: all clean dependents

-include ../makefile.targets
