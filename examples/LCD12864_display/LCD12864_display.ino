/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
    LCD12864 SPI 通讯方式

    LCD  IntoRobot Atom
    PIN1         = GND
    PIN2         = 5V
    RS(CS)     = D0;
    RW(SID)   = D2;
    EN(CLK)    = D1;
    PIN15 PSB = GND;
*/

#include <LCD12864RSPI.h>
#include "IntoRobot_bmp.h"

#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show1[]="ST7920 LCD12864 ";
unsigned char show2[]="welcome";
unsigned char show3[]="您好！欢迎！！！";
unsigned char show4[]="by IntoRobot";

LCD12864RSPI LCDA(D0, D2, D1);

void setup()
{
    LCDA.Initialise();
    delay(100);
}

void loop()
{
    LCDA.Clear();
    delay(100);
    LCDA.DrawFullScreen(logo);
    delay(5000);

    LCDA.Clear();
    delay(100);
    LCDA.DisplayString(0,0,show1,AR_SIZE(show1));
    delay(10);
    LCDA.DisplayString(1,0,show2,AR_SIZE(show2));
    delay(10);
    LCDA.DisplayString(2,0,show3,AR_SIZE(show3));
    delay(10);
    LCDA.DisplayString(3,0,show4,AR_SIZE(show4));
    delay(5000);
}
