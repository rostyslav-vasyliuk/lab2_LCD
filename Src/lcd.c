#include "lcd.h"

void LCD_Init(){
	HAL_Delay(50);
	LCD_write_byte(0x02);
	HAL_Delay(50);
  LCD_write_byte(0x28);
	HAL_Delay(50);
	LCD_write_byte(0x28);
	HAL_Delay(50);
	parametrsToggle(1,0,0);
	HAL_Delay(50);
	LCD_Clear();
	shiftToggle(1,0);
}

void LCD_write_byte(uint8_t cmd) {
    LCD_Send_Data(1, cmd);
}

void lcdChar(const char chr) {
    LCD_Send_Data(0, (uint8_t)chr);
}

void LCD_Parse_String(uint8_t* str){
	for(uint8_t i=0;str[i]!='\0';i++){
		lcdChar(str[i]);
	}
}

void setCursor(uint8_t col, uint8_t row)
{
	LCD_Send_Data(1,0x80 | (col | row*0x40));
}

void parametrsToggle(uint8_t display,uint8_t cursor,uint8_t blink){
	uint8_t comm = 0x08;

	if(display) {
		comm|=0x04;
	}

	if(cursor){
		comm|=0x02;
	}

	if(blink){
		comm|=0x01;
	}

	LCD_write_byte(comm);
}

void shiftToggle(uint8_t rightShift,uint8_t scrollInc){
	uint8_t comm = 0x04;
	
	if(rightShift){
		comm|=0x02;
	}
	if(scrollInc){
		comm|=0x01;
	}

	LCD_write_byte(comm);
}

void scrollRight(void){
	LCD_write_byte(0x10|0x08|0x00);
}

void scrollLeft(void){
	LCD_write_byte(0x10|0x08|0x04);
}

void LCD_Clear(void)
{
	LCD_write_byte(0x01);
	HAL_Delay(50);
}

void home(void)
{
	LCD_write_byte(0x02);
	HAL_Delay(50);
}

void LCD_Send_Data(uint8_t isCommand, uint8_t data) {
    if(isCommand==1) 
		{
			RS(RESET);
		} else {
			RS(SET);
		};

    HAL_Delay(50);

    if(((data >> 7) & 1)==1) DH7(SET) else DH7(RESET);
    if(((data >> 6) & 1)==1) DH6(SET) else DH6(RESET);
    if(((data >> 5) & 1)==1) DH5(SET) else DH5(RESET);
    if(((data >> 4) & 1)==1) DH4(SET) else DH4(RESET);

    EN(SET);
    HAL_Delay(50);
    EN(RESET);

    if(((data >> 3) & 1)==1) DH7(SET) else DH7(RESET);
    if(((data >> 2) & 1)==1) DH6(SET) else DH6(RESET);
    if(((data >> 1) & 1)==1) DH5(SET) else DH5(RESET);
    if(((data >> 0) & 1)==1) DH4(SET) else DH4(RESET);

    EN(SET);
    HAL_Delay(50);
    EN(RESET);
}
