#include "geom.h"
#include <stddef.h>
#include <math.h>
#include <stdio.h>
size_t _point_to_i(uint8_t xsize, uint8_t x, uint8_t y){
    return xsize*y + x ;
}
float _hit_persent(point p1, point p2, point p_check){
    return ((float)(p_check.x - p1.x))*(float)(p2.y - p1.y) - ((float)(p_check.y - p1.y))*(float)(p2.x - p1.x);
}
int draw_line(uint16_t * frame_buffer, point fb_size ,  point p1, point p2, uint16_t color){
    if(p1.x < p2.x){
        point tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    uint8_t Y = p1.y;
    uint8_t X = p1.x;
    point tmp;
    for(int count = fabs((int)p2.x- (int)p1.x); count > 0; count--){
        tmp.x =  X+1;
        tmp.y =Y+1 ;
        if ((int)p2.y > (int)p1.y && _hit_persent(p1, p2, tmp) < 0)
                Y++ ;
        else if ((int)p2.y < (int)p1.y && _hit_persent(p1, p2, tmp) > 0)
                Y--;
        // else if((int)p2.x < (int)p1.x && _hit_persent(p1, p2, tmp) > 0)
        //     Y++;
        tmp.x--;
        tmp.y--;
        X+=(int)p2.x > (int)p1.x ? 1: -1;
        frame_buffer[_point_to_i(fb_size.x, X, Y)] = color;
    }
    
}