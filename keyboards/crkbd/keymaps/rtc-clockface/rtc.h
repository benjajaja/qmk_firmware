#include <stdbool.h>

#define RTC_ADDRESS (0x68 << 1)
#define RTC_I2C_TIMEOUT 100
#define RTC_DATETIME_REGISTER 0x00
#define RTC_DATETIME_LENGTH 7
#define RTC_TEMPERATURE_REGISTER 0x11
#define RTC_TEMPERATURE_LENGTH 2

bool readDS3231time(uint8_t *second,
                    uint8_t *minute,
                    uint8_t *hour,
                    uint8_t *dayOfWeek,
                    uint8_t *dayOfMonth,
                    uint8_t *month,
                    uint8_t *year
);

bool writeDS3231time_field(uint8_t offset, uint8_t value);

bool readDS3231control_status(uint8_t *control, uint8_t *status, uint8_t *aging);

bool writeDS3231osf(void);
