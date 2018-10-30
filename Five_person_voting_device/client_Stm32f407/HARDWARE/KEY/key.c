#include "key.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"

void KEY_Init(void) //初始化矩阵键盘要使用的GPIO口。
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);

	//initlized GPIO of COL	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_11 | GPIO_Pin_2 | GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_9; 
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_13;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//initlized GPIO of ROW
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_13;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_13 | GPIO_Pin_15 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_4 | GPIO_Pin_2;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}

int KEYA_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	A_COL_1 = A_COL_2 = A_COL_3 = 1;
	
	if((A_ROW_1==0) && (A_ROW_2==0) && (A_ROW_3==0) && (A_ROW_4==0)) 
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((A_ROW_1==0) && (A_ROW_2==0) && (A_ROW_3==0) && (A_ROW_4==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	A_COL_1 = 1;A_COL_2 = 0;A_COL_3 = 0;
	if(A_ROW_1){      
		KeyVal=11;
	}else if(A_ROW_2){
		KeyVal=9;
	}else if(A_ROW_3){
		KeyVal=6;	
	}else if(A_ROW_4){
		KeyVal=3;
	}
		
	A_COL_1 = 0;A_COL_2 = 1;A_COL_3 = 0;
	if(A_ROW_1){      
		KeyVal=0;
	}else if(A_ROW_2){
		KeyVal=8;
	}else if(A_ROW_3){
		KeyVal=5;	
	}else if(A_ROW_4){
		KeyVal=2;
	}
		
	A_COL_1 = 0;A_COL_2 = 0;A_COL_3 = 1;
	if(A_ROW_1){      
		KeyVal=10;
	}else if(A_ROW_2){
		KeyVal=7;
	}else if(A_ROW_3){
		KeyVal=4;	
	}else if(A_ROW_4){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

int KEYB_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	B_COL_1 = B_COL_2 = B_COL_3 = 1;
	
	if((B_ROW_1==0) && (B_ROW_2==0) && (B_ROW_3==0) && (B_ROW_4==0)) 
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((B_ROW_1==0) && (B_ROW_2==0) && (B_ROW_3==0) && (B_ROW_4==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	B_COL_1 = 1;B_COL_2 = 0;B_COL_3 = 0;
	if(B_ROW_1){      
		KeyVal=11;
	}else if(B_ROW_2){
		KeyVal=9;
	}else if(B_ROW_3){
		KeyVal=6;	
	}else if(B_ROW_4){
		KeyVal=3;
	}
		
	B_COL_1 = 0;B_COL_2 = 1;B_COL_3 = 0;
	if(B_ROW_1){      
		KeyVal=0;
	}else if(B_ROW_2){
		KeyVal=8;
	}else if(B_ROW_3){
		KeyVal=5;	
	}else if(B_ROW_4){
		KeyVal=2;
	}
		
	B_COL_1 = 0;B_COL_2 = 0;B_COL_3 = 1;
	if(B_ROW_1){      
		KeyVal=10;
	}else if(B_ROW_2){
		KeyVal=7;
	}else if(B_ROW_3){
		KeyVal=4;	
	}else if(B_ROW_4){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

int KEYC_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	C_COL_1 = C_COL_2 = C_COL_3 = 1;
	
	if((C_ROW_1==0) && (C_ROW_2==0) && (C_ROW_3==0) && (C_ROW_4==0)) 
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((C_ROW_1==0) && (C_ROW_2==0) && (C_ROW_3==0) && (C_ROW_4==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	C_COL_1 = 1;C_COL_2 = 0;C_COL_3 = 0;
	if(C_ROW_1){      
		KeyVal=11;
	}else if(C_ROW_2){
		KeyVal=9;
	}else if(C_ROW_3){
		KeyVal=6;	
	}else if(C_ROW_4){
		KeyVal=3;
	}
		
	C_COL_1 = 0;C_COL_2 = 1;C_COL_3 = 0;
	if(C_ROW_1){      
		KeyVal=0;
	}else if(C_ROW_2){
		KeyVal=8;
	}else if(C_ROW_3){
		KeyVal=5;	
	}else if(C_ROW_4){
		KeyVal=2;
	}
		
	C_COL_1 = 0;C_COL_2 = 0;C_COL_3 = 1;
	if(C_ROW_1){      
		KeyVal=10;
	}else if(C_ROW_2){
		KeyVal=7;
	}else if(C_ROW_3){
		KeyVal=4;	
	}else if(C_ROW_4){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

int KEYD_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	D_COL_1 = D_COL_2 = D_COL_3 = 1;
	
	if((D_ROW_1==0) && (D_ROW_2==0) && (D_ROW_3==0) && (D_ROW_4==0)) 
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((D_ROW_1==0) && (D_ROW_2==0) && (D_ROW_3==0) && (D_ROW_4==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	D_COL_1 = 1;D_COL_2 = 0;D_COL_3 = 0;
	if(D_ROW_1){      
		KeyVal=11;
	}else if(D_ROW_2){
		KeyVal=9;
	}else if(D_ROW_3){
		KeyVal=6;	
	}else if(D_ROW_4){
		KeyVal=3;
	}
		
	D_COL_1 = 0;D_COL_2 = 1;D_COL_3 = 0;
	if(D_ROW_1){      
		KeyVal=0;
	}else if(D_ROW_2){
		KeyVal=8;
	}else if(D_ROW_3){
		KeyVal=5;	
	}else if(D_ROW_4){
		KeyVal=2;
	}
		
	D_COL_1 = 0;D_COL_2 = 0;D_COL_3 = 1;
	if(D_ROW_1){      
		KeyVal=10;
	}else if(D_ROW_2){
		KeyVal=7;
	}else if(D_ROW_3){
		KeyVal=4;	
	}else if(D_ROW_4){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

int KEYE_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	E_COL_1 = E_COL_2 = E_COL_3 = 1;
	
	if((E_ROW_1==0) && (E_ROW_2==0) && (E_ROW_3==0) && (E_ROW_4==0)) 
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((E_ROW_1==0) && (E_ROW_2==0) && (E_ROW_3==0) && (E_ROW_4==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	E_COL_1 = 1;E_COL_2 = 0;E_COL_3 = 0;
	if(E_ROW_1){      
		KeyVal=11;
	}else if(E_ROW_2){
		KeyVal=9;
	}else if(E_ROW_3){
		KeyVal=6;	
	}else if(E_ROW_4){
		KeyVal=3;
	}
		
	E_COL_1 = 0;E_COL_2 = 1;E_COL_3 = 0;
	if(E_ROW_1){      
		KeyVal=0;
	}else if(E_ROW_2){
		KeyVal=8;
	}else if(E_ROW_3){
		KeyVal=5;	
	}else if(E_ROW_4){
		KeyVal=2;
	}
		
	E_COL_1 = 0;E_COL_2 = 0;E_COL_3 = 1;
	if(E_ROW_1){      
		KeyVal=10;
	}else if(E_ROW_2){
		KeyVal=7;
	}else if(E_ROW_3){
		KeyVal=4;	
	}else if(E_ROW_4){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	
