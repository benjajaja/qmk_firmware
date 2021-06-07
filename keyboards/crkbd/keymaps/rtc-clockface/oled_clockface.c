#include QMK_KEYBOARD_H

#ifdef OLED_DRIVER_ENABLE
void hand_pos(uint8_t minute, uint8_t *x, uint8_t *y, uint8_t half_step) {
  if (minute < 7) {
    *x = 15 + minute * 2 + half_step;
    *y = 1;
  } else if (minute == 7) {
    *x = 28 + half_step;
    *y = 1;
  } else if (minute == 8) {
    *x = 29;
    *y = 1 + half_step;

  } else if (minute < 22) {
    *x = 29;
    *y = 1 + (minute - 8) * 2 + half_step;
  } else if (minute == 22) {
    *x = 29;
    *y = 28 + half_step;
  } else if (minute == 23) {
    *x = 29 - half_step;
    *y = 29;

  } else if (minute < 37) {
    *x = 29 - (minute - 23) * 2 - half_step;
    *y = 29;
  } else if (minute == 37) {
    *x = 2 - half_step;
    *y = 29;
  } else if (minute == 38) {
    *x = 1;
    *y = 29 - half_step;

  } else if (minute < 52) {
    *x = 1;
    *y = 29 - (minute - 38) * 2 - half_step;
  } else if (minute == 52) {
    *x = 1;
    *y = 2 - half_step;
  } else if (minute == 53) {
    *x = 1 + half_step;
    *y = 1;

  } else {
    *x = 1 + (minute - 53) * 2 + half_step;
    *y = 1;
  }
}


void oled_render_face(void) {
  static uint8_t x = 0;
  static uint8_t y = 0;

  static uint8_t q = 0;
  static uint8_t outer_step = 0;

  for (q = 0; q < 4; q++) {
    switch (q) {
      case 0:
        x = -1;
        y = -1;
        break;
      case 1:
        x = 1;
        y = -1;
        break;
      case 2:
        x = -1;
        y = 1;
        break;
      case 3:
        x = 1;
        y = 1;
        break;
    }
    for (outer_step = 0; outer_step < 16; outer_step += 2) {
      oled_write_pixel(15 + x * outer_step, 15 + y * 15, true);
      oled_write_pixel(15 + x * 15, 15 + y * outer_step, true);
    }
  }

  static uint8_t hour_steps = 0;
  static uint8_t hour_steps_x = 0;
  static uint8_t hour_steps_y = 0;
  for (hour_steps = 0; hour_steps < 60; hour_steps += 5) {
    hand_pos(hour_steps, &hour_steps_x, &hour_steps_y, 0);
    oled_write_pixel(hour_steps_x, hour_steps_y, true);
  }
}

void line(int8_t x0, int8_t y0, int8_t x1, int8_t y1, uint8_t length, bool draw) {
  static uint8_t dx = 0;
  static uint8_t dy = 0;
  static int8_t sx = 0;
  static int8_t sy = 0;
  static int8_t err = 0;
  static int8_t e2 = 0;
  static uint8_t stepcount = 0;

  dx = abs(x1 - x0);
  dy = abs(y1 - y0);
  sx = x0 < x1 ? 1 : -1;
  sy = y0 < y1 ? 1 : -1;
  err = (dx > dy ? dx : -dy) / 2;
  stepcount = 0;

  while (x0 != x1 || y0 != y1) {
    if (length != 0 && stepcount > length) {
      break;
    }
    oled_write_pixel(x0, y0, draw);
    stepcount++;
    e2 = err;
    if (e2 > -dx) { err -= dy; x0 += sx; }
    if (e2 <  dy) { err += dx; y0 += sy; }
  }
}

void oled_render_hand(uint8_t minute, int8_t length, bool half_step) {
  static uint8_t x = 0;
  static uint8_t y = 0;

  hand_pos(minute, &x, &y, half_step ? 1 : 0);
  if (length > 0) {
    line(15, 15, x, y, length, true);
  } else if (length < 0) {
    line(x, y, 15, 15, abs(length), true);
  }
}

void oled_render_hand_second(uint8_t minute, bool half_step) {
  oled_render_hand(minute, -4, half_step);
}
void oled_render_hand_minute(uint8_t minute) {
  oled_render_hand(minute, 12, false);
}
void oled_render_hand_hour(uint8_t minute) {
  oled_render_hand(minute, 7, false);
}
#endif
