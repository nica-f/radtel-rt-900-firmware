# Target name
TARGET = firmware

# Toolchain definitions
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
RM_DIR_CMD = rmdir /s /q

# Build directory
BUILD_DIR = build
# Convert BUILD_DIR to Windows path for cmd.exe commands
WIN_BUILD_DIR = $(subst /,\,$(BUILD_DIR))

# Git hash
GIT_HASH_TMP := $(shell git rev-parse --short HEAD 2>/dev/null)
ifeq ($(GIT_HASH_TMP),)
  GIT_VERSION := "NOGIT"
else
  GIT_VERSION := $(GIT_HASH_TMP)
endif

# C flags
CFLAGS = -Os -Wall -Werror -mcpu=cortex-m1 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=c11 -MMD -MP -flto
CFLAGS += -DGIT_VERSION="\"$(GIT_VERSION)\""
CFLAGS += -DUSE_FULL_ASSERT=1 # Enable full assertions
CFLAGS += -DUSE_STDPERIPH_DRIVER # Include standard peripheral drivers
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-maybe-uninitialized
CFLAGS += -Wno-format # Disable format warnings (like %d vs %lu)
CFLAGS += -Wno-switch # Disable warnings for missing enum cases in switch statements
CFLAGS += -Wno-attributes # Disable warnings for ignored attributes (like __attribute__((at(...))))
CFLAGS += -Wno-pointer-sign # Disable warnings for pointer signedness mismatches
CFLAGS += -Wno-unused-but-set-variable # Disable warnings for variables set but not used
CFLAGS += -D__nop=__NOP # Map non-standard __nop to CMSIS standard __NOP

# Debug flag (set to 1 for debug build, e.g., make DEBUG=1)
DEBUG ?= 0
ifeq ($(DEBUG),1)
  CFLAGS += -g
  ASFLAGS += -g
  LDFLAGS += -g
else
  # Potentially remove -g from CFLAGS if it was added unconditionally before,
  # or ensure it's only added if DEBUG=1.
  # For now, -g is removed from the base CFLAGS and only added if DEBUG=1.
endif

# Assembler flags (GCC will pass relevant CFLAGS to assembler for .s files)
ASFLAGS = -mcpu=cortex-m1 -x assembler-with-cpp # Preprocess assembly files
ifeq ($(DEBUG),1)
  ASFLAGS += -g
endif

# Linker flags
LDFLAGS = -mcpu=cortex-m1 -nostartfiles -Wl,-T,firmware.ld -flto
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
LDFLAGS += -specs=nano.specs -specs=nosys.specs # For smaller binary size
ifeq ($(DEBUG),1)
  LDFLAGS += -g
endif

# LIBS placeholder
LIBS =

# Include directories
INCLUDES = \
    -IApp \
    -IBSP \
    -ICommon \
    -ICore \
    -ICPS \
    -IDriver \
    -IGui \
    -IInterface \
    -ILibraries \
    -ILibraries/CMSIS/Include \
    -ILibraries/StdPeriph_Driver/inc \
    -IVoice \
    -I.

# Source files
C_SOURCES = \
    Libraries/StdPeriph_Driver/src/bt32f0x_adc.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_comp.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_crc.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_dbgmcu.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_divqsrt.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_dma.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_exti.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_flash.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_gpio.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_i2c.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_iwdg.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_misc.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_opa.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_pwr.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_rcc.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_rtc.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_spi.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_syscfg.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_tim.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_usart.c \
    Libraries/StdPeriph_Driver/src/bt32f0x_wwdg.c \
    Libraries/StdPeriph_Driver/src/system_bt32f0x.c \
    App/main.c \
    BSP/Board.c \
    BSP/BoardFun.c \
    BSP/bt32f0x_it.c \
    Driver/crc.c \
    Driver/DevBK4819.c \
    Driver/DevBK4819Data.c \
    Driver/FlashFont.c \
    Driver/key_ptt.c \
    Driver/keyboard.c \
    Driver/NorFlash.c \
    Driver/RadioDataReset.c \
    Driver/RadioDataStorage.c \
    Driver/Rda5807.c \
    Driver/st7735s.c \
    Driver/Systick.c \
    App/AppAlarm.c \
    App/AppDtmf.c \
    App/AppFm.c \
    App/AppMain.c \
    App/AppMenu.c \
    App/AppMoni.c \
    App/AppScan.c \
    App/AppScanQT.c \
    App/AppSearch.c \
    App/AppTask.c \
    App/AppWeather.c \
    App/Battery.c \
    App/DualStandby.c \
    Common/BitMap.c \
    Common/Delay.c \
    Common/Globe.c \
    Common/assert_failed_stub.c \
    Core/Functions.c \
    Core/Radio.c \
    Core/RadioTask.c \
    CPS/ProgromFlash.c \
    Gui/DisplayBattery.c \
    Gui/DisplayDtmf.c \
    Gui/DisplayFm.c \
    Gui/DisplayInputbox.c \
    Gui/DisplayMain.c \
    Gui/DisplayMenu.c \
    Gui/DisplayPowerOn.c \
    Gui/DisplayScanQT.c \
    Gui/DisplaySearch.c \
    Gui/DisplayWeather.c \
    Gui/LcdFillDot.c \
    Interface/i2c.c \
    Voice/Beep.c \
    Voice/VoiceBroadcast.c

S_SOURCES = \
    Libraries/CMSIS/Device/startup_bt32f0x.s

# Object files paths (remain the same, with Unix-style paths for GCC)
C_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
S_OBJS = $(patsubst %.s, $(BUILD_DIR)/%.o, $(S_SOURCES))
OBJS = $(C_OBJS) $(S_OBJS)

# Dependency files paths
DEPS = $(OBJS:.o=.d)

# Default target
all: $(BUILD_DIR)/$(TARGET).bin
	@echo "Build complete."
	@echo "Cleaning up $(TARGET).elf and $(TARGET).map..."
	-cmd /c if exist "$(WIN_BUILD_DIR)\$(TARGET).elf" del "$(WIN_BUILD_DIR)\$(TARGET).elf"
	-cmd /c if exist "$(WIN_BUILD_DIR)\$(TARGET).map" del "$(WIN_BUILD_DIR)\$(TARGET).map"

# Target to create all necessary directories using cmd.exe syntax
create_dirs_target:
	@echo Creating directories...
	cmd /c if not exist "$(WIN_BUILD_DIR)" mkdir "$(WIN_BUILD_DIR)"
	cmd /c if not exist "$(WIN_BUILD_DIR)\App" mkdir "$(WIN_BUILD_DIR)\App"
	cmd /c if not exist "$(WIN_BUILD_DIR)\BSP" mkdir "$(WIN_BUILD_DIR)\BSP"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Common" mkdir "$(WIN_BUILD_DIR)\Common"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Core" mkdir "$(WIN_BUILD_DIR)\Core"
	cmd /c if not exist "$(WIN_BUILD_DIR)\CPS" mkdir "$(WIN_BUILD_DIR)\CPS"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Driver" mkdir "$(WIN_BUILD_DIR)\Driver"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Gui" mkdir "$(WIN_BUILD_DIR)\Gui"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Interface" mkdir "$(WIN_BUILD_DIR)\Interface"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Libraries" mkdir "$(WIN_BUILD_DIR)\Libraries"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Libraries\CMSIS" mkdir "$(WIN_BUILD_DIR)\Libraries\CMSIS"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Libraries\CMSIS\Device" mkdir "$(WIN_BUILD_DIR)\Libraries\CMSIS\Device"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Libraries\StdPeriph_Driver" mkdir "$(WIN_BUILD_DIR)\Libraries\StdPeriph_Driver"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Libraries\StdPeriph_Driver\src" mkdir "$(WIN_BUILD_DIR)\Libraries\StdPeriph_Driver\src"
	cmd /c if not exist "$(WIN_BUILD_DIR)\Voice" mkdir "$(WIN_BUILD_DIR)\Voice"

# Compile C sources to object files
$(BUILD_DIR)/%.o: %.c Makefile | create_dirs_target
	@echo "CC $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Assemble S sources to object files
$(BUILD_DIR)/%.o: %.s Makefile | create_dirs_target
	@echo "AS $<"
	@$(CC) $(ASFLAGS) $(INCLUDES) -c $< -o $@

# Link object files to create ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) firmware.ld Makefile
	@echo "LD $@"
	@$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "---------------------"
	@echo "SIZE of $(TARGET).elf:"
	@$(SIZE) $@
	@echo "---------------------"

# Create binary file from ELF file
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf Makefile
	@echo "OBJCOPY $@"
	@$(OBJCOPY) -O binary $< $@

# Clean build artifacts
clean:
	@echo "CLEAN"
	@REM Ensure WIN_BUILD_DIR is used here if it contains backslashes, though for 'build' it's not strictly necessary.
	-cmd /c if exist "$(WIN_BUILD_DIR)" $(RM_DIR_CMD) "$(WIN_BUILD_DIR)"

# Include dependency files
-include $(DEPS)

# Phony targets
.PHONY: all clean create_dirs_target
