#include "prompt.h"
#include <avr/pgmspace.h>

char prompt_buffer[PROMPT_LINES][PROMPT_WIDTH];
char prompt_command_buffer[PROMPT_WIDTH];

const char PROGMEM keycode_to_ascii[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

uint8_t prompt_cursor = 0;
uint8_t prompt_buffer_line = 0;
uint8_t prompt_screen_line = 0;
uint8_t prompt_scroll = 0;
static uint16_t prompt_timer = 0;
static uint16_t prompt_timeout_timer = 0;
uint16_t prompt_clock_timer = 0;
char prompt_clock_user_hours = 0;
char prompt_clock_user_minutes = 0;
char prompt_clock_user_seconds = 0;
enum prompt_info {
  INFO_TIME,
#ifdef WPM_ENABLE
  INFO_WPM,
#endif
#ifdef RGB_MATRIX_ENABLE
  INFO_ANIMATION,
  INFO_SPEED,
  INFO_HSV,
#endif
  INFO_LAYERS,
};
#define INFO_SIZE INFO_LAYERS
uint8_t prompt_info_cursor = INFO_TIME;

enum prompt_command_state {
  CMD_STATE_OFF,
  CMD_STATE_ENTER,
  CMD_STATE_READY
};

#define ERR_NO_EMPTY_LINE 255
uint8_t prompt_find_empty(void) {
  static uint8_t line;
  static uint8_t i;
  line = prompt_buffer_line;
  for (i = 0; i < PROMPT_LINES; i++) {
    if (prompt_buffer[line][0] == 0) {
      return line;
    }
    line++;
    if (line >= PROMPT_LINES) {
      line = 0;
    }
  }
  return 255;
}


void prompt_add_P(const char *data) {
  // find spot
  static uint8_t line;
  line = prompt_find_empty();
  if (line == 255) {
#ifdef CONSOLE_ENABLE
    uprintf("no space to add string");
#endif
    // no space
    return;
  }
  strcpy_P(prompt_buffer[line], data);
}

void prompt_add_f(const char *format, ...) {
  va_list args;
  va_start (args, format);
  // find spot
  uint8_t line = prompt_find_empty();
  if (line == 255) {
#ifdef CONSOLE_ENABLE
    uprintf("no space to add string");
#endif
    // no space
    return;
  }
  vsprintf(prompt_buffer[line], format, args);
  va_end (args);
}

static uint32_t clock_seconds = 0;
static uint32_t clock_minutes = 0;
static uint32_t clock_hours = 0;
/* static uint32_t remainder_ms = 0; */
void prompt_add_time(void) {
  clock_seconds = timer_elapsed32(prompt_clock_timer) / 1000;
  clock_minutes = clock_seconds / 60;
  clock_hours = clock_minutes / 60;
  prompt_add_f(
      "%02lu:%02lu:%02lu",
      (clock_hours + prompt_clock_user_hours) % 24,
      (clock_minutes + prompt_clock_user_minutes) % 60,
      (clock_seconds + prompt_clock_user_seconds) % 60
  );
}

void prompt_start_command() {
  memset(prompt_command_buffer, 0, sizeof(prompt_command_buffer));
  prompt_command = CMD_STATE_ENTER;
}

void prompt_add_char(uint16_t keycode, bool shift) {
  static uint8_t len;
  len = strlen(prompt_command_buffer);
  static char char_to_add = 0;
  if (keycode < 58) {
    char_to_add = pgm_read_byte_near(keycode_to_ascii + keycode);
  }
  if (char_to_add == 0) {
    char_to_add = '?';
  }

  prompt_command_buffer[len] = char_to_add;
  oled_set_cursor(len, prompt_screen_line);
  oled_write_char(char_to_add, false);
  oled_write_char(' ', true);
#ifdef CONSOLE_ENABLE
  uprintf("keycode: %u\n", keycode);
#endif
}

#define START_LINE_OFFSET 0

void prompt_init(uint8_t layer_count) {
  prompt_command = CMD_STATE_OFF;
  prompt_info_layer_activations = 0;
  for (uint8_t i = 0; i < PROMPT_LINES; i++) {
    prompt_buffer[i][0] = 0;
  }

  prompt_add_f("crkbd: %d layers", layer_count);

  prompt_cursor = 0;
  prompt_scroll = 0;
  prompt_buffer_line = 0;
  prompt_screen_line = 0;
  prompt_clock_timer = timer_read32();
  prompt_timer = timer_read();
  prompt_timeout_timer = timer_read();
  oled_set_start_line(START_LINE_OFFSET);

  memset(prompt_command_buffer, 0, sizeof(prompt_command_buffer));
}

char current;
uint16_t elapsed;
char trailing_cursor = 0;
void prompt_render(void) {
  if (prompt_command == CMD_STATE_READY) {
    return;
  }
  elapsed = timer_elapsed(prompt_timer);
  current = prompt_buffer[prompt_buffer_line][prompt_cursor];
  if (current != 0 || (current == 0 && prompt_command == CMD_STATE_ENTER)) {
    if (elapsed > 20 && prompt_screen_line == 4) {
      if (prompt_scroll == 0) {
        oled_set_cursor(0, prompt_screen_line);
        oled_write_P(PSTR("                     "), false);
      }
      prompt_scroll++;
      if (prompt_scroll > 7) {
        prompt_scroll = 0;
        oled_set_start_line(START_LINE_OFFSET);
        oled_pan_vertical(false);
        prompt_screen_line = 3;

        current = prompt_buffer[prompt_buffer_line][prompt_cursor];
        if (current == 0 && prompt_command == CMD_STATE_ENTER) {
          // command line is printed and scrolled
          oled_set_cursor(trailing_cursor, prompt_screen_line - 1);
          oled_write_char(' ', false);
          oled_set_cursor(0, prompt_screen_line);
          oled_write_char(' ', true);
          prompt_command = CMD_STATE_READY;
          prompt_buffer[prompt_buffer_line][0] = 0;
          prompt_buffer_line++;
        }

      } else {
        oled_set_start_line(START_LINE_OFFSET + prompt_scroll);
      }
      prompt_timer = timer_read();

    } else if (elapsed > 25) {
      if (prompt_cursor == 0 && prompt_screen_line > 0) {
        // new line: remove traling cursor
        oled_set_cursor(trailing_cursor, prompt_screen_line - 1);
        oled_write_char(' ', false);
      }

      // write char without highlight
      oled_set_cursor(prompt_cursor, prompt_screen_line);
      oled_write_char(current, false);

      prompt_cursor++;
      /* oled_set_cursor(prompt_cursor, prompt_screen_line); */
      current = prompt_buffer[prompt_buffer_line][prompt_cursor];
      if (current != 0) {
        // Cursor with char highlighted
        oled_write_char(current, true);
      } else {
        // EOL, write cursor highlight
        oled_write_char(' ', true);

        prompt_buffer[prompt_buffer_line][0] = 0;
        prompt_buffer_line++;
        if (prompt_buffer_line == PROMPT_LINES) {
          prompt_buffer_line = 0;
        }

        trailing_cursor = prompt_cursor;
        prompt_cursor = 0;
        prompt_screen_line++;
      }
      prompt_timer = timer_read();
    }

  } else if (prompt_command == CMD_STATE_OFF && timer_elapsed(prompt_timeout_timer) > 1200) {
    prompt_info_cursor++;
    if (prompt_info_cursor > INFO_SIZE) {
      prompt_info_cursor = 0;
    }
    switch (prompt_info_cursor) {
      case INFO_TIME:
        prompt_add_time();
        break;
      case INFO_LAYERS:
        prompt_add_f("%d layer toggles", prompt_info_layer_activations);
        break;
#ifdef WPM_ENABLE
      case INFO_WPM:
        prompt_add_f("%d wpm", get_current_wpm());
        break;
#endif
#ifdef RGB_MATRIX_ENABLE
      case INFO_ANIMATION:
        prompt_add_f("animation: #%d", rgb_matrix_get_mode());
        break;
      case INFO_SPEED:
        prompt_add_f("anim. speed: %d", rgb_matrix_get_speed());
        break;
      case INFO_HSV:
        prompt_add_f("h:%d s:%d v:%d", rgb_matrix_get_hue(), rgb_matrix_get_sat(),
            rgb_matrix_get_val());
        break;
#endif
    }
    prompt_timeout_timer = timer_read();
  }
}


void prompt_timeout_reset() {
  prompt_timeout_timer = timer_read();
}

void prompt_timer_reset() {
  prompt_timer = timer_read();
}

#define CMD_ERR 0
#define CMD_TIME 1
const char PROGMEM cmd_time[] = "time";
void process_prompt_command(void) {
  static uint8_t len;
  len = strlen(prompt_command_buffer);
  oled_set_cursor(len + 1, prompt_screen_line);
  oled_write_char(' ', false);
  static uint8_t erase_buffer_line;
  if (prompt_screen_line > 0) {
    erase_buffer_line = prompt_buffer_line - 1;
  } else {
    erase_buffer_line = PROMPT_LINES - 1;
  }
  prompt_buffer[erase_buffer_line][0] = 0;
  prompt_screen_line++;
  prompt_cursor = 0;

  static uint8_t space = 0;
  for (space = 1; space < strlen(prompt_command_buffer); space++) {
    if (prompt_command_buffer[space] == ' ') {
      break;
    }
  }
  static char first_part[PROMPT_WIDTH];
  strncpy(first_part, prompt_command_buffer, space - 1);
  if (strcmp(first_part, "time") == 0) {
    prompt_add_P(PSTR("set time XX:XX"));
  } else {
    prompt_add_P(PSTR("command error"));
  }

  prompt_timer_reset();
  prompt_timeout_reset();

  prompt_command = CMD_STATE_OFF;
}

