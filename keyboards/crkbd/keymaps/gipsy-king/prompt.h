#include QMK_KEYBOARD_H
#define PROMPT_WIDTH 21
#define PROMPT_LINES 6
#define is_prompt_half !is_master


uint8_t prompt_command;
uint16_t prompt_info_layer_activations;

void prompt_init(uint8_t layer_count);
void prompt_render(void);
void prompt_add_P(const char *data);
void prompt_add_char(uint16_t keycode, bool shift);
void prompt_timeout_reset(void);
void prompt_timer_reset(void);
void prompt_start_command(void);
void process_prompt_command(void);
