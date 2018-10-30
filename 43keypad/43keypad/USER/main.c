#include "stm32f10x.h"
#include "usart.h"
#include "key.h"
#include "delay.h"

int main(void)
{	
	KEY_Init();
	uart_init(9600);
	delay_init();
	
	while(1)
	{
		delay_ms(150);
		switch(KEY_Scan())
		{
			case 0: printf("0\n"); break;
			case 1: printf("1\n"); break;
			case 2: printf("2\n"); break;
			case 3: printf("3\n"); break;
			case 4: printf("4\n"); break;
			case 5: printf("5\n"); break;
			case 6: printf("6\n"); break;
			case 7: printf("7\n"); break;
			case 8: printf("8\n"); break;
			case 9: printf("9\n"); break;
			case 10: printf("*\n"); break;
			case 11: printf("#\n"); break;
		}
	}
}

