#ifdef OLED_DRIVER_ENABLE
void oled_render_face(void);
void oled_render_hand_second(uint8_t minute, bool half_step);
void oled_render_hand_minute(uint8_t minute);
void oled_render_hand_hour(uint8_t minute);
#endif
