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

 ******************************************************************************
 */

#ifndef LCD12864RSPI_H
#define LCD12864RSPI_H

#include "Arduino.h"

class LCD12864RSPI
{
    typedef unsigned char uchar;

    public:
    LCD12864RSPI(int RS_pin, int RW_pin, int EN_pin);

    void Initialise(void);
    void Clear(void);
    void DisplayString(int X,int Y,uchar *ptr,int dat);
    void DisplaySig(int M,int N,int sig);
    void DrawFullScreen(uchar *p);
    void img1(uchar img[]);
    void img2(uchar img[]);

    private:
    int RS;
    int EN;
    int RW;

    int delaytime;
    int DEFAULTTIME;

    void delayns(void);
    void WriteByte(int dat);
    void WriteCommand(int CMD);
    void WriteData(int CMD);

};

#endif
