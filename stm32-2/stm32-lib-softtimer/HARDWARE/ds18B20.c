#include "ds18b20.h"
#include "delay.h"

#include "stm32f10x_gpio.h"

#define EnableINT()
#define DisableINT()
#define DS_PORT GPIOB
#define DS_DQIO GPIO_Pin_14
#define DS_RCC_PORT RCC_APB2Periph_GPIOB
#define DS_PRECISION 0x7f //精度配置寄存器 1f=9位; 3f=10位; 5f=11位; 7f=12位;
#define DS_AlarmTH 0x64
#define DS_AlarmTL 0x8a
#define DS_CONVERT_TICK 1000
#define ResetDQ() GPIO_ResetBits(DS_PORT, DS_DQIO)
#define SetDQ() GPIO_SetBits(DS_PORT, DS_DQIO)
#define GetDQ() GPIO_ReadInputDataBit(DS_PORT, DS_DQIO)

#define SkipROM 0xCC         //跳过ROM
#define SearchROM 0xF0       //搜索ROM
#define ReadROM 0x33         //读ROM
#define MatchROM 0x55        //匹配ROM
#define AlarmROM 0xEC        //告警ROM
#define StartConvert 0x44    //开始温度转换，在温度转换期间总线上输出0，转换结束后输出1
#define ReadScratchpad 0xBE  //读暂存器的9个字节
#define WriteScratchpad 0x4E //写暂存器的温度告警TH和TL
#define CopyScratchpad 0x48  //将暂存器的温度告警复制到EEPROM，在复制期间总线上输出0，复制完后输出1
#define RecallEEPROM 0xB8    //将EEPROM的温度告警复制到暂存器中，复制期间输出0，复制完成后输出1
#define ReadPower 0xB4       //读电源的供电方式：0为寄生电源供电；1为外部电源供电

static unsigned char TempX_TAB[16] = {0x00, 0x01, 0x01, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x08, 0x09, 0x09};

// void delay_us(u32 Nus)
// {
//
//   SysTick->LOAD = Nus * 9;
//                         //时间加载
//   SysTick->CTRL |= 0x01;
//                               //开始倒数
//   while (!(SysTick->CTRL & (1 << 16)));
//        //等待时间到达
//   SysTick->CTRL = 0X00000000;
//                     //关闭计数器
//   SysTick->VAL = 0X00000000;
//                       //清空计数器
// }
//
unsigned char ResetDS18B20(void)
{
    unsigned char resport;
    unsigned int ii = 0 ;
    SetDQ();
    delay_us(50);

    ResetDQ();
    delay_us(500);
    //500us （该时间的时间范围可以从480到960微秒）
    SetDQ();
    delay_us(40);
    //40us
    //resport = GetDQ();
    while (GetDQ() && ii++<500000 )
        ;
    delay_us(500);
    //500us
    SetDQ();
    return resport;
}
void DS18B20WriteByte(unsigned char Dat)
{
    unsigned char i;
    for (i = 8; i > 0; i--)

    {
        ResetDQ();
        //在15u内送数到数据线上，DS18B20在15-60u读数
        delay_us(5);
        //5us
        if (Dat & 0x01)
            SetDQ();
        else
            ResetDQ();
        delay_us(65);
        //65us
        SetDQ();
        delay_us(2);
        //连续两位间应大于1us
        Dat >>= 1;
    }
}

unsigned char DS18B20ReadByte(void)
{
    unsigned char i, Dat;
    SetDQ();
    delay_us(5);
    for (i = 8; i > 0; i--)

    {
        Dat >>= 1;
        ResetDQ();
        //从读时序开始到采样信号线必须在15u内，且采样尽量安排在15u的最后
        delay_us(5);
        //5us
        SetDQ();
        delay_us(5);
        //5us
        if (GetDQ())
            Dat |= 0x80;
        else
            Dat &= 0x7f;

        delay_us(65);
        //65us
        SetDQ();
    }
    return Dat;
}

void ReadRom(unsigned char *Read_Addr)
{
    unsigned char i;
    DS18B20WriteByte(ReadROM);

    for (i = 8; i > 0; i--)

    {
        *Read_Addr = DS18B20ReadByte();
        Read_Addr++;
    }
}

void DS18B20Init(unsigned char Precision, unsigned char AlarmTH, unsigned char AlarmTL)
{
    unsigned int ii = 0 ;
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(WriteScratchpad);
    DS18B20WriteByte(AlarmTL);
    DS18B20WriteByte(AlarmTH);
    DS18B20WriteByte(Precision);
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(CopyScratchpad);
    EnableINT();
    while (!GetDQ() && ii++<500000)
        ;
    //等待复制完成  ///////////
}

void DS18B20StartConvert(void)
{
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(StartConvert);

    EnableINT();
}

void DS18B20_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(DS_RCC_PORT, ENABLE);
    GPIO_InitStructure.GPIO_Pin = DS_DQIO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    //开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //2M时钟速度
    GPIO_Init(DS_PORT, &GPIO_InitStructure);
}

void ds18b20_start(void)
{
    DS18B20_Configuration();
    DS18B20Init(DS_PRECISION, DS_AlarmTH, DS_AlarmTL);
    DS18B20StartConvert();
}

unsigned short ds18b20_read(void)
{
    unsigned char TemperatureL, TemperatureH;
    unsigned int Temperature;
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(ReadScratchpad);
    TemperatureL = DS18B20ReadByte();
    TemperatureH = DS18B20ReadByte();

    ResetDS18B20();
    EnableINT();
    if (TemperatureH & 0x80)

    {
        TemperatureH = (~TemperatureH) | 0x08;
        TemperatureL = ~TemperatureL + 1;
        if (TemperatureL == 0)
            TemperatureH += 1;
    }
    TemperatureH = (TemperatureH << 4) + ((TemperatureL & 0xf0) >> 4);
    TemperatureL = TempX_TAB[TemperatureL & 0x0f];
    //bit0-bit7为小数位，bit8-bit14为整数位，bit15为正负位
    Temperature = TemperatureH;
    Temperature = (Temperature << 8) | TemperatureL;

    DS18B20StartConvert();
    // return Temperature;

    return  TemperatureH ;
}

// #include "ds18b20.h"
// #include "delay.h"

// //复位DS18B20
// void DS18B20_Rst(void)
// {
// 	DS18B20_IO_OUT(); //SET PA0 OUTPUT
//     DS18B20_DQ_OUT=0; //拉低DQ
//     delay_us(750);    //拉低750us
//     DS18B20_DQ_OUT=1; //DQ=1
// 	delay_us(15);     //15US
// }
// //等待DS18B20的回应
// //返回1:未检测到DS18B20的存在
// //返回0:存在
// u8 DS18B20_Check(void)
// {
// 	u8 retry=0;
// 	DS18B20_IO_IN();//SET PA0 INPUT
//     while (DS18B20_DQ_IN&&retry<200)
// 	{
// 		retry++;
// 		delay_us(1);
// 	};
// 	if(retry>=200)return 1;
// 	else retry=0;
//     while (!DS18B20_DQ_IN&&retry<240)
// 	{
// 		retry++;
// 		delay_us(1);
// 	};
// 	if(retry>=240)return 1;
// 	return 0;
// }
// //从DS18B20读取一个位
// //返回值：1/0
// u8 DS18B20_Read_Bit(void) 			 // read one bit
// {
//     u8 data;
// 	DS18B20_IO_OUT();//SET PA0 OUTPUT
//     DS18B20_DQ_OUT=0;
// 	delay_us(2);
//     DS18B20_DQ_OUT=1;
// 	DS18B20_IO_IN();//SET PA0 INPUT
// 	delay_us(12);
// 	if(DS18B20_DQ_IN)data=1;
//     else data=0;
//     delay_us(50);
//     return data;
// }
// //从DS18B20读取一个字节
// //返回值：读到的数据
// u8 DS18B20_Read_Byte(void)    // read one byte
// {
//     u8 i,j,dat;
//     dat=0;
// 	for (i=1;i<=8;i++)
// 	{
//         j=DS18B20_Read_Bit();
//         dat=(j<<7)|(dat>>1);
//     }
//     return dat;
// }
// //写一个字节到DS18B20
// //dat：要写入的字节
// void DS18B20_Write_Byte(u8 dat)
//  {
//     u8 j;
//     u8 testb;
// 	DS18B20_IO_OUT();//SET PA0 OUTPUT;
//     for (j=1;j<=8;j++)
// 	{
//         testb=dat&0x01;
//         dat=dat>>1;
//         if (testb)
//         {
//             DS18B20_DQ_OUT=0;// Write 1
//             delay_us(2);
//             DS18B20_DQ_OUT=1;
//             delay_us(60);
//         }
//         else
//         {
//             DS18B20_DQ_OUT=0;// Write 0
//             delay_us(60);
//             DS18B20_DQ_OUT=1;
//             delay_us(2);
//         }
//     }
// }
// //开始温度转换
// void DS18B20_Start(void)// ds1820 start convert
// {
//     DS18B20_Rst();
// 	DS18B20_Check();
//     DS18B20_Write_Byte(0xcc);// skip rom
//     DS18B20_Write_Byte(0x44);// convert
// }
// //初始化DS18B20的IO口 DQ 同时检测DS的存在
// //返回1:不存在
// //返回0:存在
// u8 DS18B20_Init(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
// 	//RCC->APB2ENR|=1<<2;    //使能PORTA口时钟
// 	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	 //使能PORTA口时钟

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  //SPI CS
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	/* Deselect the PA0 Select high */
// 	GPIO_SetBits(GPIOA,GPIO_Pin_0);
// 	DS18B20_Rst();
// 	return DS18B20_Check();
// }
// //从ds18b20得到温度值
// //精度：0.1C
// //返回值：温度值 （-550~1250）
// short DS18B20_Get_Temp(void)
// {
//     u8 temp;
//     u8 TL,TH;
// 	short tem;
//     DS18B20_Start ();                    // ds1820 start convert
//     DS18B20_Rst();
//     DS18B20_Check();
//     DS18B20_Write_Byte(0xcc);// skip rom
//     DS18B20_Write_Byte(0xbe);// convert
//     TL=DS18B20_Read_Byte(); // LSB
//     TH=DS18B20_Read_Byte(); // MSB

//     if(TH>7)
//     {
//         TH=~TH;
//         TL=~TL;
//         temp=0;//温度为负
//     }else temp=1;//温度为正
//     tem=TH; //获得高八位
//     tem<<=8;
//     tem+=TL;//获得底八位
//     tem=(float)tem*0.625;//转换
// 	if(temp)return tem; //返回温度值
// 	else return -tem;
// }
