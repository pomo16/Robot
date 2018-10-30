#include "key.h"
#include "delay.h"

void KEY_Init(void) //初始化矩阵键盘要使用的GPIO口。
{

 	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //定义PB9到PB11为推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //定义PB12到PB15为下拉输入。
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    //因为上面定义引脚为输出时，已经打开整个GPIOA的时钟了，
	//所以此处不再需要函数RCC_APB2PeriphClockCmd()来打开时钟了。
    GPIO_Init(GPIOB,&GPIO_InitStructure);		
}

int KEY_Scan(void) //实现矩阵键盘。返回值为各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。
	PBout(9)=PBout(10)=PBout(11)=1;//先让PB9到PB11全部输出高。
	
	if((PBin(12)==0) && (PBin(13)==0) && (PBin(14)==0) && (PBin(15)==0))  //如果PB12到PB15全为0，则没有键按下。此时，返回值为-1.
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //延时5ms去抖动。
	    if((PBin(12)==0) && (PBin(13)==0) && (PBin(14)==0) && (PBin(15)==0))//如果延时5ms后，PB12到PB15又全为0，则，刚才引脚的电位变化是抖动产生的.
	    return -1;
	}

	PBout(9)=1;PBout(10)=0;PBout(11)=0;//让PB9到PB11输出二进制的100
	if(PBin(12)){       //对PB12到PB15的值进行判断，以输出不同的键值。
		KeyVal=11;
	}else if(PBin(13)){
		KeyVal=9;
	}else if(PBin(14)){
		KeyVal=6;	
	}else if(PBin(15)){
		KeyVal=3;
	}
		
	PBout(9)=0;PBout(10)=1;PBout(11)=0;//让PB9到PB11输出二进制的010
	if(PBin(12)){       //对PB12到PB15的值进行判断，以输出不同的键值。
		KeyVal=0;
	}else if(PBin(13)){
		KeyVal=8;
	}else if(PBin(14)){
		KeyVal=5;	
	}else if(PBin(15)){
		KeyVal=2;
	}
		
	PBout(9)=0;PBout(10)=0;PBout(11)=1;//让PB9到PB11输出二进制的001
	if(PBin(12)){       //对PB12到PB15的值进行判断，以输出不同的键值。
		KeyVal=10;
	}else if(PBin(13)){
		KeyVal=7;
	}else if(PBin(14)){
		KeyVal=4;	
	}else if(PBin(15)){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

