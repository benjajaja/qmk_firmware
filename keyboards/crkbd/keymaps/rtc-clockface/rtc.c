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
bool readRTCtime(uint8_t *second,
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

  *second     = ((time[0] & 0x70) >> 4) * 10 + (time[0] & 0x0f);
  *minute     = ((time[1] & 0x70) >> 4) * 10 + (time[1] & 0x0f);
  *hour       = ((time[2] & 0x40) >> 4) ? /* 12 hour mode */ ((time[2] & 0x20) ? 12 : 0) + ((time[2] & 0x10) ? 10 : 0) + (time[2] & 0x0f)
                                        : /* 24 hour mode */ ((time[2] & 0x20) ? 20 : 0) + ((time[2] & 0x10) ? 10 : 0) + (time[2] & 0x0f);
  *dayOfWeek  =                                (time[3] & 0x07);
  *dayOfMonth = ((time[4] & 0x30) >> 4) * 10 + (time[4] & 0x0f);
  *month      = ((time[5] & 0x10) >> 4) * 10 + (time[5] & 0x0f);
  *year       = ((time[6] & 0xf0) >> 4) * 10 + (time[6] & 0x0f);
    // + ((time[5] & 0x80) ? 2000 : 1900);
  return true;
}

bool readRTCcontrol_status(uint8_t *control, uint8_t *status, uint8_t *aging) {
  if (i2c_readReg(RTC_ADDRESS, 0x0e, control, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  if (i2c_readReg(RTC_ADDRESS, 0x0f, status, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  if (i2c_readReg(RTC_ADDRESS, 0x10, aging, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

static uint8_t time_write[] = {0,0,0,0,0,0,0};
bool writeRTCtime(uint8_t second,
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

  if (i2c_writeReg(RTC_ADDRESS, RTC_DATETIME_REGISTER, time_write, sizeof(time_write) / sizeof(time_write[0]), RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

// offset is one of time_cursor_fields
bool writeRTCtime_field(uint8_t offset, uint8_t value) {
  uint8_t bcd_value = decToBcd(value);
  if (i2c_writeReg(RTC_ADDRESS, 6 - offset, &bcd_value, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

bool readRTCReg(uint8_t reg, uint8_t *data) {
  if (i2c_readReg(RTC_ADDRESS, reg, data, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}
bool writeRTCReg(uint8_t reg, uint8_t data) {
  if (i2c_writeReg(RTC_ADDRESS, reg, &data, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
    return false;
  }
  return true;
}

/* bool writeRTCosf(void) { */
  /* static uint8_t status = 0; */
  /* if (i2c_readReg(RTC_ADDRESS, 0x0f, &status, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) { */
    /* return false; */
  /* } */
  /* status = status & 0x7f; */
/*  */
  /* if (i2c_writeReg(RTC_ADDRESS, 0x0f, &status, 1, RTC_I2C_TIMEOUT) != I2C_STATUS_SUCCESS) { */
    /* return false; */
  /* } */
  /* return true; */
/* } */


