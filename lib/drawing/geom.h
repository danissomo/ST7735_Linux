#include <stdint.h>
#include <stdbool.h>
typedef struct {
    uint8_t x;
    uint8_t y;
} point;

int draw_line(uint16_t * frame_buffer, point fb_size,  point p1, point p2, uint16_t color);
int draw_rect(uint16_t * frame_buffer, point fb_size , point place, point size, uint16_t color, bool border);
int draw_circle(uint16_t * frame_buffer, point fb_size,  point place, uint8_t radius, uint16_t color, uint16_t bg , bool transparent);
int draw_img(uint16_t * frame_buffer, point fb_size,uint16_t img,  point place, point size, uint16_t bg, bool transparent);