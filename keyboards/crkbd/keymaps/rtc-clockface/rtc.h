#include <stdbool.h>

#ifndef RTC_ADDRESS
#define RTC_ADDRESS (0x52 << 1)
#endif
#define RTC_I2C_TIMEOUT 100
#define RTC_DATETIME_REGISTER 0x00

bool readRTCtime(uint8_t *second,
                    uint8_t *minute,
                    uint8_t *hour,
                    uint8_t *dayOfWeek,
                    uint8_t *dayOfMonth,
                    uint8_t *month,
                    uint8_t *year
);

bool writeRTCtime_field(uint8_t offset, uint8_t value);

bool readRTCcontrol_status(uint8_t *control, uint8_t *status, uint8_t *aging);

bool readRTCReg(uint8_t reg, uint8_t *data);
bool writeRTCReg(uint8_t reg, uint8_t data);
// bool writeRTCReg(uint8_t reg, uint8_t offset, uint8_t value);
