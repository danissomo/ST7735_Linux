#include "orangepiwin.h"
#include "st7735/st7735.h"
#include "stdio.h"
#include "unistd.h"
#include "st7735/testimg.h"
int main(){
    srand(time(0));
   
    ST7735_Init();
    ST7735_FillScreen(ST7735_BLACK);
    for (int i = 0; ; i++){
        char f[10];
        sprintf(f, "frame %d", i);
        ST7735_WriteString(0,0,f, Font_7x10, ST7735_BLACK, ST7735_WHITE);
        ST7735_FillRectangle((uint16_t)rand()%ST7735_WIDTH, (uint16_t)rand() % ST7735_HEIGHT, 
                            (uint16_t)rand()%ST7735_HEIGHT,(uint16_t)rand()% ST7735_HEIGHT,
                            (uint16_t)rand()
        );
        //sleep(1);
    }
    
   
    ST7735_FillScreen(ST7735_WHITE);
   //ST7735_WriteString(0, 0, "fuck orangepi", Font_11x18, ST7735_YELLOW, ST7735_WHITE);
   ST7735_DrawImage(0, 0, 128,128,
                     (uint16_t*)test_img_128x128);
}