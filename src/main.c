#include "orangepiwin.h"
#include "st7735/st7735.h"
#include "stdio.h"
#include "unistd.h"
#include "st7735/testimg.h"
#include "drawing/geom.h"
#include <string.h>
int main(){
    srand(time(0));
    uint16_t frame_buffer[ST7735_WIDTH * ST7735_HEIGHT];
    memset(frame_buffer, 0, sizeof(frame_buffer));
    ST7735_Init();
    ST7735_FillScreen(0x0000);
    // for (int i = 0; ; i++){
    //     char f[10];
    //     sprintf(f, "frame %d", i);
    //     ST7735_WriteString(0,0,f, Font_7x10, ST7735_BLACK, ST7735_WHITE);
    //     ST7735_FillRectangle((uint16_t)rand()%ST7735_WIDTH, (uint16_t)rand() % ST7735_HEIGHT, 
    //                         (uint16_t)rand()%ST7735_HEIGHT,(uint16_t)rand()% ST7735_HEIGHT,
    //                         (uint16_t)rand()
    //     );
    //     //sleep(1);
    // }

   
    //ST7735_FillScreen(ST7735_WHITE);
   //ST7735_WriteString(0, 0, "fuck orangepi", Font_11x18, ST7735_YELLOW, ST7735_WHITE);
    ST7735_DrawImage(0, 0, 128,128, (uint16_t*)test_img_128x128);
    getc(stdin);
    // while (1){
    //     point p1 =  {0, 60}, p2 = {159, 0}, fbsize = { ST7735_WIDTH, ST7735_HEIGHT };
    //     for (size_t i =0; i < ST7735_HEIGHT ; i+=2){
    //         p2.y = i;
    //         draw_line (frame_buffer, fbsize, p1, p2, 0xE607);
    //         ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, frame_buffer);   
    //         //ST7735_FillRectangle(p1.x, p1.y, p2.x, p2.y, 0xE607);
    //         memset(frame_buffer, 0, sizeof(frame_buffer));
    //     } 

    // }
    while(1){
        char string[100];
        fgets(string, 100, stdin);
        string[100] = '\0';
        printf("%s", string);
        ST7735_WriteString(0, 0, string, Font_7x10, ST7735_WHITE, ST7735_BLACK);
    }
    
    
    
    
}