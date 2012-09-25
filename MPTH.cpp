#include "MPTH.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>  

MPTH::MPTH(uint8_t i2cAddr, uint8_t CmdChar, uint8_t NumLines, uint8_t NumChar) {
    _i2cAddr = i2cAddr >> 1;
    _CmdChar = CmdChar;
    _numlines = NumLines;
    _numchar = NumChar;
    _displaymode = 0x0C;
    _displaycontrol = 0x14;
    _displayfunction = 0x6;
    _currline = 0;
    _currchar = 0;
}

void MPTH::begin(void) {
 Wire.begin(); 
 clear();
 command(MPTH_LCD_CMD, _displaymode);
 command(MPTH_LCD_CMD, _displayfunction);
 command(MPTH_LCD_CMD, _displaycontrol);
}

inline void MPTH::command(uint8_t cmd, uint8_t value) {
  byte MPsend[3];
  MPsend[0] = _CmdChar;
  MPsend[1] = cmd;
  MPsend[2] = value;
  Wire.beginTransmission(_i2cAddr);                  // Send Slave (device) address
  Wire.write(MPsend, 3);                                  // Send the data
  Wire.endTransmission();
}

#if ARDUINO >= 100
inline size_t MPTH::write(uint8_t value) {
  if (value == '\n') {
    _currline++;
    if (_currline >= _numlines) {
      home();
      }
    else {
      setCursor(_currline, 0);
    }   
  }
  else {
    Wire.beginTransmission(_i2cAddr);                  // Send Slave (device) address
    Wire.write(value);                                  // Send the data
    Wire.endTransmission();
    //_currchar++;
    if (_currchar >= _numchar) {
      _currchar = 0;
      _currline++;
      if (_currline >= _numlines) {
        _currline = 0;
        }
    }
  }
  return 1;
}
#else
inline void MPTH::write(uint8_t value) {

}
#endif

void MPTH::clear()
{
  command(MPTH_LCD_CMD, MPTH_LCD_CMDCLEAR);  // clear display, set cursor position to zero
  _currline = 0;
  _currchar = 0;
}

void MPTH::home()
{
  command(MPTH_LCD_CMD, MPTH_LCD_CMDHOME);  // set cursor position to zero
  _currline = 0;
  _currchar = 0;
}

void MPTH::setCursor(uint8_t x, uint8_t y){
 byte pos;
 pos = (x * _numchar) + y;
 command(MPTH_MOVECUR,pos);
 _currline = x;
 _currchar = y;
}

void MPTH::noDisplay()
{
  _displaymode = _displaymode & 0x0b;
  command(MPTH_LCD_CMD, _displaymode);  
}
void MPTH::display()
{ 
  _displaymode = _displaymode | 0x04;
  command(MPTH_LCD_CMD, _displaymode);  
}

void MPTH::noBlink()
{
  _displaymode = _displaymode & 0x0e;
  command(MPTH_LCD_CMD, _displaymode);  
}
void MPTH::blink()
{ 
  _displaymode = _displaymode | 0x01;
  command(MPTH_LCD_CMD, _displaymode);  
}

void MPTH::noCursor()
{
  _displaymode = _displaymode & 0x0d;
  command(MPTH_LCD_CMD, _displaymode);  
}
void MPTH::cursor()
{ 
  _displaymode = _displaymode | 0x02;
  command(MPTH_LCD_CMD, _displaymode);  
}

void MPTH::setBacklight(uint8_t status) {
  command(MPTH_BACKLIGHT, status);
}

void MPTH::scrollDisplayLeft(){
/* Place holder. This function doesn't work with MPTH */
 // command(MPTH_LCD_CMD, status);
}

void MPTH::scrollDisplayRight(){
  /* Place holder. This function doesn't work with MPTH */
  //command(MPTH_LCD_CMD, status);
}

void MPTH::leftToRight(){
  /* Place holder. This function doesn't work with MPTH */
  /*
  _displaycontrol = _displaycontrol | 0x04;
  command(MPTH_LCD_CMD, _displaycontrol);
  */
}

void MPTH::rightToLeft(){
  /* Place holder. This function doesn't work with MPTH */
  /*
  _displaycontrol = _displaycontrol & 0x1B;
  command(MPTH_LCD_CMD, _displaycontrol);
  */
} 

void MPTH::autoscroll() {
  _displayfunction = _displayfunction | 0x01;
  command(MPTH_LCD_CMD, _displayfunction);
}
void MPTH::noAutoscroll() {
  _displayfunction = _displayfunction & 0x06;
  command(MPTH_LCD_CMD, _displayfunction);
}

