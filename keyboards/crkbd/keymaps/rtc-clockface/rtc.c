#include "rtc.h"
#include "i2c_master.h"

uint8_t decToBcd(uint8_t val) {
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val) {
  return( (val/16*10) + (val%16) );
}

static uint8_t time[] = {0,0,0,0,0,0,0};
bool readDS3231time(uint8_t *second,
                    uint8_t *minute,
                    uint8_t *hour,
                    uint8_t *dayOfWeek,
                    uint8_t *dayOfMonth,
                    uint8_t *month,
                    uint8_t *year
) {
  if (i2c_readReg(RTC_ADDRESS, RTC_DATETIME_REGISTER, time, RTC_DATETIME_LENGTH, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }

  *second = bcdToDec(time[0] & 0x7f);
  *minute = bcdToDec(time[1]);
  *hour = bcdToDec(time[2] & 0x3f);
  *dayOfWeek = bcdToDec(time[3]);
  *dayOfMonth = bcdToDec(time[4]);
  *month = bcdToDec(time[5]);
  *year = bcdToDec(time[6]);
  return true;
}

static uint8_t time_write[] = {0,0,0,0,0,0,0};
bool writeDS3231time(uint8_t second,
                     uint8_t minute,
                     uint8_t hour,
                     uint8_t dayOfWeek,
                     uint8_t dayOfMonth,
                     uint8_t month,
                     uint8_t year
) {
  time_write[0] = second;
  time_write[1] = minute;
  time_write[2] = hour;
  time_write[3] = dayOfWeek;
  time_write[4] = dayOfMonth;
  time_write[5] = month;
  time_write[6] = year;

  if (i2c_writeReg(RTC_ADDRESS, RTC_DATETIME_REGISTER, time_write, RTC_DATETIME_LENGTH, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

/* static uint8_t time_fields[] = {0,0,0,0,0,0,0}; */
bool writeDS3231time_field(uint8_t offset, uint8_t value) {
  uint8_t bcd_value = decToBcd(value);
  if (i2c_writeReg(RTC_ADDRESS, 6 - offset, &bcd_value, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

