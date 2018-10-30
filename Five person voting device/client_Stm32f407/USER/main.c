#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"

void LCDShowResult(u8 A_num,u8 B_num,u8 C_num,u8 D_num,u8 E_num);
int fun_judge(u8 X_flag,u8 X_num,u32 score);

int main(void)
{ 
	u8 t;
	u8 len;	
	int flag = -1;
	u8 A_num,B_num,C_num,D_num,E_num=0;
	u8 A_flag,B_flag,C_flag,D_flag,E_flag = 0;//按键标志位 0:simple; 1:delete; 2:no touch
	u8 A_show[3],B_show[3],C_show[3],D_show[3],E_show[3] = {0};	
	u32 A_score,B_score,C_score,D_score,E_score;
	u32 num;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(9600);		//初始化串口波特率为115200
	
	LED_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	KEY_Init();			//初始化键盘
	
	POINT_COLOR=RED;	  
	LCD_ShowString(30,40,210,24,24,"Wait");
	A_score=B_score=C_score=D_score=E_score=0;
	num=0;
	
	while(1)
	{	
		if(USART_RX_STA&0x8000)
        {                                           
			len=USART_RX_STA&0x3fff;

			if(USART_RX_BUF[0]=='a')
			{
				LED1=!LED1;
				delay_ms(100);
				flag = -flag;
			}
            for(t=0;t<len;t++)
            {
				//USART_SendData(USART1, USART_RX_BUF[t]);    
				USART_RX_BUF[t] = 0;
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}			
			USART_RX_STA=0;
		}
		
				
				if(flag == -1) 
				{	
					delay_ms(150);
					LCD_Clear(WHITE);
					POINT_COLOR=RED;	  
					LCD_ShowString(30,40,210,24,24,"Wait");
					num = (A_score+B_score+C_score+D_score+E_score)/5;
					printf("%d \n",num);
				} 
				else{
					delay_ms(150);
					A_flag=B_flag=C_flag=D_flag=E_flag=0;
					A_num=B_num=C_num=D_num=E_num=0;
					switch(KEYA_Scan())
					{
						case -1: A_flag = 2; break;
						case 0: A_num = 0; break;
						case 1: A_num = 1; break;
						case 2: A_num = 2; break;
						case 3: A_num = 3; break;
						case 4: A_num = 4; break;
						case 5: A_num = 5; break;
						case 6: A_num = 6; break;
						case 7: A_num = 7; break;
						case 8: A_num = 8; break;
						case 9: A_num = 9; break;
						case 10: A_flag = 1;break;
						case 11: A_flag = 1; break;
					}
					switch(KEYB_Scan())
					{
						case -1: B_flag = 2; break;
						case 0: B_num = 0; break;
						case 1: B_num = 1; break;
						case 2: B_num = 2; break;
						case 3: B_num = 3; break;
						case 4: B_num = 4; break;
						case 5: B_num = 5; break;
						case 6: B_num = 6; break;
						case 7: B_num = 7; break;
						case 8: B_num = 8; break;
						case 9: B_num = 9; break;
						case 10: B_flag = 1; break;
						case 11: B_flag = 1; break;
					}
					switch(KEYC_Scan())
					{
						case -1: C_flag = 2; break;
						case 0: C_num = 0; break;
						case 1: C_num = 1; break;
						case 2: C_num = 2; break;
						case 3: C_num = 3; break;
						case 4: C_num = 4; break;
						case 5: C_num = 5; break;
						case 6: C_num = 6; break;
						case 7: C_num = 7; break;
						case 8: C_num = 8; break;
						case 9: C_num = 9; break;
						case 10: C_flag = 1; break;
						case 11: C_flag = 1; break;
					}
					switch(KEYD_Scan())
					{
						case -1: D_flag = 2; break;
						case 0: D_num = 0; break;
						case 1: D_num = 1; break;
						case 2: D_num = 2; break;
						case 3: D_num = 3; break;
						case 4: D_num = 4; break;
						case 5: D_num = 5; break;
						case 6: D_num = 6; break;
						case 7: D_num = 7; break;
						case 8: D_num = 8; break;
						case 9: D_num = 9; break;
						case 10: D_flag = 1; break;
						case 11: D_flag = 1; break;
					}
					switch(KEYE_Scan())
					{
						case -1: E_flag = 2; break;
						case 0: E_num = 0; break;
						case 1: E_num = 1; break;
						case 2: E_num = 2; break;
						case 3: E_num = 3; break;
						case 4: E_num = 4; break;
						case 5: E_num = 5; break;
						case 6: E_num = 6; break;
						case 7: E_num = 7; break;
						case 8: E_num = 8; break;
						case 9: E_num = 9; break;
						case 10: E_flag = 1; break;
						case 11: E_flag = 1; break;
					}
					
					A_score = fun_judge(A_flag,A_num,A_score);
					B_score = fun_judge(B_flag,B_num,B_score);
					C_score = fun_judge(C_flag,C_num,C_score);
					D_score = fun_judge(D_flag,D_num,D_score);
					E_score = fun_judge(E_flag,E_num,E_score);
					
				//		printf("A_score:%d \n",A_score);
				//		printf("B_score:%d \n",B_score);	
				//		printf("C_score:%d \n",C_score);
				//		printf("D_score:%d \n",D_score);
				//		printf("E_score:%d \n",E_score);		
							
					LCDShowResult(A_score,B_score,C_score,D_score,E_score);
				}
				
		

	}
}



void LCDShowResult(u8 A_num,u8 B_num,u8 C_num,u8 D_num,u8 E_num){
	POINT_COLOR=RED;	  
	LCD_ShowString(30,40,210,24,24,"Start：");	
	LCD_ShowString(30,70,200,16,16,"A:");
	LCD_ShowNum(60,70,A_num,3,16);
	LCD_ShowString(30,90,200,16,16,"B:");
	LCD_ShowNum(60,90,B_num,3,16);
 	LCD_ShowString(30,110,200,16,16,"C:");
	LCD_ShowNum(60,110,C_num,3,16);
	LCD_ShowString(30,130,200,16,16,"D:");
	LCD_ShowNum(60,130,D_num,3,16);
	LCD_ShowString(30,150,200,16,16,"E:");	
	LCD_ShowNum(60,150,E_num,3,16);
}

int fun_judge(u8 X_flag,u8 X_num,u32 score){
	u32 X_show[3] = {0};
	X_show[0] = score/100%10;
	X_show[1] = score/10%10;
	X_show[2] = score/1%10;
	
	if(X_flag == 0){
		X_show[0] = X_show[1];
		X_show[1] = X_show[2];
		X_show[2] = X_num;
	}
	else if(X_flag == 1){
		X_show[0] = 0;
		X_show[1] = X_show[0];
		X_show[2] = X_show[1];		
	}
	else{
		score = score;
	}
	
	score = X_show[0]*100 + X_show[1]*10 +X_show[2];
	if(score > 100){
		score = 100;
	}
	
	return score;
}