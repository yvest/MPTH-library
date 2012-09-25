#ifndef MPTH_h
#define MPTH_h

#include <inttypes.h>
#include "Print.h"
//#include "Adafruit_MCP23008.h"
//#include <Wire.h>

#define MPTH_LCD_CMD 0x05
#define MPTH_LCD_CMDCLEAR     0x01
#define MPTH_LCD_CMDHOME      0x02
#define MPTH_MOVECUR 0x08
#define MPTH_BACKLIGHT 0x01


class MPTH : public Print {
public:

  MPTH(uint8_t i2cAddr, uint8_t CmdChar, uint8_t NumLines, uint8_t NumChar);
  void begin(void);

  void clear();
  void home();

  void noDisplay();
  void display();

  void noBlink();
  void blink();

  void noCursor();
  void cursor();
  
 void scrollDisplayLeft();
 void scrollDisplayRight();
 void leftToRight();
 void rightToLeft();
 
 void autoscroll();
 void noAutoscroll();
  
  // only if using backpack
  void setBacklight(uint8_t status); 

//  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
#if ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif
  void command(uint8_t, uint8_t);
private:

  uint8_t _displayfunction; // auto-scroll
  uint8_t _numlines, _currline, _numchar, _currchar;
  uint8_t _displaymode; // Display enable, cursor enable, cursor blink
  uint8_t _displaycontrol; //Display shift, Direction of shift

  uint8_t _i2cAddr;
  uint8_t _CmdChar;
};

#endif
