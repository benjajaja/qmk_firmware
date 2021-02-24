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
  if (i2c_readReg(RTC_ADDRESS, 0x00, time, sizeof(time) / sizeof(time[0]), RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }

  *second     = (time[0] & 0x70) * 10 + (time[0] & 0x0f);
  *minute     = (time[1] & 0x70) * 10 + (time[1] & 0x0f);
  *hour       = (time[2] & 0x40) ? /* 12 hour mode */ ((time[2] & 0x20) ? 12 : 0) + ((time[2] & 0x10) ? 10 : 0) + (time[2] & 0x0f)
                                 : /* 24 hour mode */ ((time[2] & 0x20) ? 20 : 0) + ((time[2] & 0x10) ? 10 : 0) + (time[2] & 0x0f);
  *dayOfWeek  = (time[3] & 0x07);
  *dayOfMonth = (time[4] & 0x30) * 10 + (time[4] & 0x0f);
  *month      = (time[5] & 0x10) * 10 + (time[5] & 0x0f);
  *year       = (time[6] & 0xf0) * 10 + (time[6] & 0x0f) + ((time[5] & 0x80) ? 2000 : 1999);
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

  if (i2c_start(RTC_ADDRESS | I2C_WRITE, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  if (i2c_write(RTC_DATETIME_REGISTER, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  i2c_stop();

  if (i2c_transmit(RTC_ADDRESS, time_write, RTC_DATETIME_LENGTH, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

/* static uint8_t time_fields[] = {0,0,0,0,0,0,0}; */
bool writeDS3231time_field(uint8_t offset, uint8_t value) {
  if (i2c_start(RTC_ADDRESS | I2C_WRITE, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  if (i2c_write(RTC_DATETIME_REGISTER | offset, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }

  uint8_t bcd_value = decToBcd(value);
  if (i2c_writeReg(RTC_ADDRESS, 6 - offset, &bcd_value, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  i2c_stop();
  return true;
  /* if (!readDS3231time(&time_fields[0], */
                 /* &time_fields[1], */
                 /* &time_fields[2], */
                 /* &time_fields[3], */
                 /* &time_fields[4], */
                 /* &time_fields[5], */
                 /* &time_fields[6])) { */
    /* return false; */
  /* } */
  /* time_fields[6 - offset] = value; */
  /* return writeDS3231time(decToBcd(time_fields[0]), */
                         /* decToBcd(time_fields[1]), */
                         /* decToBcd(time_fields[2]), */
                         /* decToBcd(time_fields[3]), */
                         /* decToBcd(time_fields[4]), */
                         /* decToBcd(time_fields[5]), */
                         /* decToBcd(time_fields[6])); */
}

bool readDS3231temp(uint8_t *upper, uint8_t *lower) {
  static uint8_t temp[] = {0,0};

  if (i2c_start(RTC_ADDRESS | I2C_WRITE, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  if (i2c_write(RTC_TEMPERATURE_REGISTER, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  i2c_stop();
  if (i2c_receive(RTC_ADDRESS, temp, RTC_TEMPERATURE_LENGTH, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }

  *upper = bcdToDec(temp[0]);
  *lower = bcdToDec(temp[1]);
  while (*lower >= 10) {
    *lower = *lower / 10;
  }
  return true;
}
