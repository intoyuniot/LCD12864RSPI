/*
 ******************************************************************************

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.

 This library is the LCD screen,SPI communication

 Adapted for IntoRobot by Robin, Sept 19, 2015
 ******************************************************************************
 */

#include "LCD12864RSPI.h"


//Specifications Pin
LCD12864RSPI::LCD12864RSPI(int RS_pin, int RW_pin, int EN_pin)
{
    this->DEFAULTTIME = 80; // 80 ms default time
    this->delaytime = DEFAULTTIME;
    RS=RS_pin;
    EN=EN_pin;
    RW=RW_pin;
}


void LCD12864RSPI::delayns(void)
{
    delayMicroseconds(delaytime);
}

//
void LCD12864RSPI::WriteByte(int dat)
{
    digitalWrite(RS, HIGH);
    delayns();
    shiftOut(RW, EN, MSBFIRST, dat);
    digitalWrite(RS, LOW);
}


void LCD12864RSPI::WriteCommand(int CMD)
{
    int H_data,L_data;
    H_data = CMD;
    H_data &= 0xf0;
    L_data = CMD;
    L_data &= 0x0f;
    L_data <<= 4;
    WriteByte(0xf8);          //RS=0,write data is cmd
    WriteByte(H_data);
    WriteByte(L_data);
}


void LCD12864RSPI::WriteData(int CMD)
{
    int H_data,L_data;
    H_data = CMD;
    H_data &= 0xf0;
    L_data = CMD;
    L_data &= 0x0f;
    L_data <<= 4;
    WriteByte(0xfa);         //RS=1, write data is data
    WriteByte(H_data);
    WriteByte(L_data);
}


void LCD12864RSPI::Initialise(void)
{
    pinMode(RS, OUTPUT);
    pinMode(EN, OUTPUT);
    pinMode(RW, OUTPUT);
    digitalWrite(RS, LOW);
    delayns();

    WriteCommand(0x30);        //function set command
    WriteCommand(0x0c);        //dispaly switch  command
    WriteCommand(0x01);        //clear screen  command
    WriteCommand(0x06);        //enter set point command
}


void LCD12864RSPI::Clear(void)
{
    WriteCommand(0x30);  //
    WriteCommand(0x01);  //clear screen command
}


void LCD12864RSPI::DisplayString(int X,int Y,uchar *ptr,int dat)
{
    int i;

    switch(X)
    {
        case 0:  Y|=0x80;break;

        case 1:  Y|=0x90;break;

        case 2:  Y|=0x88;break;

        case 3:  Y|=0x98;break;

        default: break;
    }

    WriteCommand(Y); //the start address

    for(i=0;i<dat;i++)
    {
        WriteData(ptr[i]);
    }
}


void LCD12864RSPI::DisplaySig(int M,int N,int sig)
{
    switch(M)
    {
        case 0:  N|=0x80;break;

        case 1:  N|=0x90;break;

        case 2:  N|=0x88;break;

        case 3:  N|=0x98;break;

        default: break;
    }
    WriteCommand(N);  // the start address
    WriteData(sig);   //output  single char
}


void LCD12864RSPI::DrawFullScreen(uchar *p)
{
    int ygroup,x,y,i;
    int temp;
    int tmp;

    for(ygroup=0;ygroup<64;ygroup++)
    {
        if(ygroup<32)
        {
            x=0x80;
            y=ygroup+0x80;
        }
        else
        {
            x=0x88;
            y=ygroup-32+0x80;
        }
        WriteCommand(0x34);
        WriteCommand(y);
        WriteCommand(x);
        WriteCommand(0x30);
        tmp=ygroup*16;
        for(i=0;i<16;i++)
        {
            temp=p[tmp++];
            WriteData(temp);
        }
    }
    WriteCommand(0x34);
    WriteCommand(0x36);
}


void LCD12864RSPI::img1(uchar img[])
{
    unsigned int i;
    unsigned char page,column;

    for(page=0xB0;page<0xB4;page++)
    {
        WriteCommand(page);  //set page address
        WriteCommand(0x10);  //set Column address MSB
        WriteCommand(0x04);  //set column address LSB

        i = (0xB3-page)*128;

        for(column=0;column<128;column++)
        {
            WriteData(~img[i+column]);
        }
    }
    WriteCommand(0x34);        //write the extend command
    WriteCommand(0x36);        //display image
}

void LCD12864RSPI::img2(uchar img[])
{
    unsigned int i;
    unsigned char page,column;

    for(page=0xB4;page<0xB8;page++)
    {
        WriteCommand(page);  //set page address
        WriteCommand(0x10);  //set Column address MSB
        WriteCommand(0x04);  //set column address LSB

        i = (0xB7-page)*128;

        for(column=0;column<128;column++)
        {
            WriteData(~img[i+column]);
        }
    }
    WriteCommand(0x34);       //write the extend command
    WriteCommand(0x36);       //display image
}
