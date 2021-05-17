OLED_DRIVER_ENABLE  = yes
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
RGB_MATRIX_ENABLE = yes

SRC += rtc.c oled_clockface.c
CFLAGS += -flto
