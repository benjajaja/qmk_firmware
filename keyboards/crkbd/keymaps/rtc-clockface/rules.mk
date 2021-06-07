# OLED_DRIVER_ENABLE = yes
# EXTRAKEY_ENABLE = yes
# MOUSEKEY_ENABLE = no
RGB_MATRIX_ENABLE = yes
# POINTING_DEVICE_ENABLE = yes

# SRC += rtc.c oled_clockface.c

PIMORONI_TRACKBALL_ENABLE = no
BOOTLOADER = atmel-dfu # elite-c

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    ENCODER_ENABLE = yes
    OPT_DEFS += -DENCODER_ENABLE
    OLED_DRIVER_ENABLE = yes
    POINTING_DEVICE_ENABLE = yes
    MOUSEKEY_ENABLE = yes
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    SRC += pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c
    LTO_ENABLE = yes
    HAPTIC_ENABLE += DRV2605L
else
    MOUSEKEY_ENABLE = yes
    RTC_ENABLE = yes
    OPT_DEFS += -DRTC_ENABLE
    OLED_DRIVER_ENABLE = yes
    SRC += rtc.c oled_clockface.c
endif
CFLAGS += -flto
