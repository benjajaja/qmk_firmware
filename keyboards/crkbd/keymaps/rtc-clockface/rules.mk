# OLED_DRIVER_ENABLE = yes
# EXTRAKEY_ENABLE = yes
# MOUSEKEY_ENABLE = no
RGB_MATRIX_ENABLE = yes
POINTING_DEVICE_ENABLE = yes

# SRC += rtc.c oled_clockface.c

PIMORONI_TRACKBALL_ENABLE = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    # ENCODER_ENABLE := yes
    OLED_DRIVER_ENABLE := no
    POINTING_DEVICE_ENABLE := yes
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    SRC += pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c
endif
CFLAGS += -flto
