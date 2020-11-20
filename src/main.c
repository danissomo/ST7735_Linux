#include "orangepiwin.h"
#include "st7735/st7735.h"
#include "stdio.h"
int main(){
    
   
    ST7735_Init();
    ST7735_FillScreen(ST7735_BLACK);
   //ST7735_FillScreen(ST7735_YELLOW);
   ST7735_WriteString(0, 0, "fuck orangepi", Font_11x18, ST7735_YELLOW, ST7735_BLACK);
    
}