/*
sgc Class for Arduino and LGT AVR



26.06.2026 V 0.81SEU8X8I2cAdress implemented
20.06.2026 V 0.81 SETACTIVE for DIsplay Adressing
29.04.2026 V.0.80 receive Funktion rework
28.04.2026 V.0.79 Funktion #define GET_COM_ERR 53 implemented
*/

#ifndef SGC_H
#define SGC_H
#endif

#ifndef SoftwareSerial_h
#include <SoftwareSerial.h>
#endif
#include <avr/power.h>



/* #######################################################################################################################
activate this define to include Hardware serial and Serial.print()
*/ 

#define debug 1
#define watchErr 0
#define withHardwareSerial 0
#define serDebug 1

// ########################################################################################################################

// defines the standard COLS and ROWS - must set accurate to your Displaytype!
#define U8X8COLS  16
#define U8X8ROWS  8
/////////////////////////////////////////////////////////////////////////////

/* ########################################################################################################################
FLGAS for Functions set to 0 lets you more memory free
*/

#define PATTERN_FUNCTIONS 1           //Set to 1 if you want use he Pattern Function
#define GRAPHIC_FUNCTIONS 0           // Set to 1 if you want use Graphic Functions like Rectange, line etc.
#define SPRITE_FUNCTIONS 1

// ########################################################################################################################

#if debug
  #ifndef HardwareSerial_h
   #include <HardwareSerial.h>
  #endif
#endif
/*
P-Codes for Commands don't change -  must match with the Codes in SD Graphis
// #########################################################################
*/

#define SHOW_SCREEN 1
#define CLEAR_SCREEN 2
#define SET_CURSOR 3
#define PRINT 4
#define PRINT_AT 5
#define CLEAR_LINE 6
#define CLEAR_LINES_UPPER 7
#define CLEAR_LINES_LOWER 8
#define HOME 9
#define SET_WPAGE 10   
#define DRAW_TILE 11
#define DRAW_SD_TILE 12
#define SD_DRAW_SCREEN 13
#define SET_FLIPMODE 14
#define SET_CONTRAST 15
#define SET_INVERSEFONT 16
#define SET_POWERSAVE 17
#define SHOW_SCREENS 18
#define SET_SPAGE 19
#define SET_TPAGE 20
#define SET_PIN 21
#define SET_PINMODE 22
#define SET_ANALOGWRITE 23
#define I2C_WRITE 24
#define CLEAR_KEY 25
#define SD_STRING_X 26
#define SHOW_SCREENS_PART 27
#define SD_STRING_Y 28
#define SD_P_STRING 29
#define SD_GFX_DRAW_LINE 30
#define SD_GFX_DRAW_VERTIKAL_LINE 31
#define SD_GFX_DRAW_RECTANGLE 32
#define SD_GFX_DRAW_FILLED_RECTANGLE 33
#define SD_GFX_DRAW_CIRCLE 34
#define OVERLAY_BEGIN 35  
#define OV_ADD 36
#define SD_PATTERN_GET 37   // free not implemened -> transfered in load with attribute
#define SD_PATTERN_PUT 38
#define SD_PATTERN_LOAD 39
#define SD_PATTERN_CLEAR 40
#define SET_SPRITE 41
#define SET_SPRITE_POSITION 42
#define SPRITE 43
#define SD_PATTERN_RECEIVE 44
#define SD_COLLISION 45
#define F_STRING 46
#define INIT_CARD 47 
#define SD_DRAW_SCREENS 48  
#define OV_REP 49
#define OV_MOV 50
#define PLAY_SCREENS 51
#define SETACTIVE 52
#define GET_COM_ERR 53
#define SET_U8X8_I2CADRESS 54


// Used defines 
#define _UINT8 2
#define _UINT16 3
#define _INT 4
#define _UINT 5
#define _LONG 6
#define _ULONG 7
#define _FLOAT 8
#define _DOUBLE 9
// Keywords to use with overlay(KEYWORD);
#define OV_COMMAND 
#define OV_ACTIVE 1
#define OV_ENABLED 1
#define OV_DISABLED 0

#define OV_FLAG_ENABLED    (1 << 0)
#define OV_FLAG_TOGGLE     (1 << 1)
#define OV_FLAG_RUNONCE    (1 << 2)
#define OV_FLAG_REVERSE    (1 << 3)
#define OV_FLAG_INVERSE    (1 << 4)
#define OV_FLAG_VERTICAL   (1 << 5)
#define OV_FLAG_ROTATE     (1 << 6)
#define OV_FLAG_FLIPTILE   (1 << 7)
/*
addOverlay(x, y glyph, OV_FLAG_ENABLED | OV_FLAG_RUNONCE | OV_FLAG_INVERSE, 20);
*/

#define SCREEN_FULL    0
#define SCREEN_BOTTOM  1
#define SCREEN_TOP     2

#define ENABLED 1
#define DISABLE 0

#define PATTERN_NOGET 0
#define PATTERN_GET 1
#define PATTERN_ONLY 2
#define PATTERNBYTES 16
#define PATTERN _UINT8_ 
// Parameter for drawscreen
#define MASK_DRAW_FOREGROUND   0
#define MASK_DRAW_BACKGROUND   1
#define MASK_INVERT_FOREGROUND 2
#define MASK_INVERT_BACKGROUND 3
// Paameter für Drawscreen
#define WITHLOAD 1
#define WITHOUTLOAD 0
// Paramter for sdPrintH/V
#define V_NORMAL 0
#define V_ROT90 1
#define V_ROT180 2


#if PATTERN_FUNCTIONS
    static uint8_t screenBitmap[16];   // 1 Bit for every tile!
#endif

#if watchErr
    uint8_t transmitErr = 0;
#endif

union receivebuf {
  char _buf[16];
  int   _INT_[4];
  uint8_t _UINT8_[16];
  uint16_t _UNT16_[4];
};
// int variables
uint8_t paramBytes = 1;
uint8_t lastCommand =0;
uint8_t key=0;

SoftwareSerial mySerial(2,3); // RX, TX // create a SoftwareSerial object

class sgcclass {
  public:
    // Constructor
    sgcclass() {
     }

    // Initialize the hardware
    void begin(unsigned long baudrate) {
       mySerial.begin(baudrate);
    }


  void digitalWrite(uint8_t pin,uint8_t status) {
       uint8_t a[2];
       a[0] = pin;
       a[1] = status;
       transmit(2,SET_PIN,a);
  }

  void i2cWrite(uint8_t address,uint8_t value) {
       uint8_t a[2];
       a[0] = address;
       a[1] = value;
       transmit(2,I2C_WRITE,(uint8_t*)a); 
  }

   void setPinMode(uint8_t pin,uint8_t status) {
       uint8_t a[2];
       a[0] = pin;
       a[1] = status;
       transmit(2,SET_PINMODE,a); 
  }

     void analogWrite(uint8_t pin,uint8_t status) {
       uint8_t a[2];
       a[0] = pin;
       a[1] = status;
       transmit(2,SET_ANALOGWRITE,a); 
  }
 
 
 void transmit(uint8_t len, uint8_t commandToken, uint8_t b[], bool fromProgmem=false) {
   #if serDebug
        Serial.println("");
        Serial.println(F("->MAIN TRANSMIT - "));
        Serial.print(commandToken);
        Serial.print(F(" len: "));
        Serial.println(len);
  #endif
    lastCommand = commandToken;           // remember lastCommand for GetParams()
    if (!isConsumed) {
        getParams();
      } else {
        Serial.println(F("isConsumed!"));
      }

        mySerial.write(255);
        mySerial.write(len);
        mySerial.write(commandToken);

    if (b==nullptr) {         // All done only  a commandToken!
        Serial.print(F("->command-only frame - "));
        isConsumed=false;
        return;
    }
  

    uint8_t checksum = 0;

      for (uint8_t i = 0; i < len; i++)
      {
          uint8_t v = fromProgmem ? pgm_read_byte(b + i) : b[i];

          mySerial.write(v);
          checksum += v;
   
          //Serial.print("SND->");
          //Serial.print(v);
      }

          mySerial.write(checksum);    // last Byte = checksum!
          //Serial.print(F(" write Checksum:"));
          //Serial.println(checksum);
          //Serial.print(F(" chk:"));
          //Serial.println(checksum);
   
    isConsumed = false;
}



     void transmit(uint8_t len, uint8_t commandToken, uint8_t b) {
        uint8_t s[1];
        s[0] = b;
          #if debug 
            Serial.print(F("->TRANSMIT 1 - "));
            Serial.println(commandToken);
          #endif
        transmit(len,commandToken,s,false);        
    }

   
    void transmit(uint8_t commandToken) {
      #if debug 
        Serial.print(F("->TRANSMIT 2 - "));
        Serial.println(commandToken);
      #endif      
        transmit(0,commandToken,nullptr,false);        
    }

    

 // Funktion zur Berechnung der Checksumme
uint8_t transmitChecksum(uint8_t data[], uint8_t length) {
  uint8_t checksum = 0;
  for (uint8_t i = 0; i < length; i++) {
    checksum += data[i]; // Automatischer Überlauf bei 255
    mySerial.write(checksum);
    Serial.println(F("write Checksum:"));
    Serial.println(checksum);
  }
  return checksum;
}
   
  
    /*
    reads a defined number of Bytes from Host
    */

bool getParams() {
    
       #if debug 
          Serial.print(F("-GETP "));
          Serial.print(paramBytes);
       #endif

          //uint8_t bRead = 0;
          timeout = 2000000L;
            //unsigned long startTime = millis();
            while (mySerial.available()<paramBytes) {
                 timeout--;
                 if (timeout==0) {
                   #if debug 
                       Serial.println(F("timeout"));
                   #endif
                  
                  return 1;
                 }
            }    
                //mySerial.readBytes( receiveBuf._UINT8_,paramBytes); 
                // Now all Parambytes Bytes received
                 
                 for  (int i= 0;i<paramBytes;i++) {
                  receiveBuf._UINT8_[i] = (uint8_t) mySerial.read();
                  #if debug 
                        Serial.print(F("->"));
                        Serial.println(receiveBuf._UINT8_[i]);
                  #endif
                }

                switch (lastCommand) {
                  case PLAY_SCREENS:
                  break;
                  case PRINT_AT:
                  break;
                  case CLEAR_KEY:
                      key=0;
                  break;
                  case SD_PATTERN_LOAD:
                  break;
                  default:
                    if (receiveBuf._UINT8_[0]>1) {
                      key = receiveBuf._UINT8_[0];
                      //Serial.print(F("Key:"));
                      //Serial.println(key);
                    }
                  break;
                }
              
              paramBytes = 1; //<-reset to default
              isConsumed = true;
     
              #if debug 
                 //unsigned long writingTime = (millis() - startTime);
                 //Serial.print(F("(w-ms):"));
                 //Serial.println(writingTime);
              #endif
                if (mySerial.available()>0) {
                  #if debug 
                     Serial.print(F("-> clean Buffer:"));
                     Serial.println(mySerial.available());
                    for (int i = 0; i<mySerial.available();i++) {
                         Serial.println(F(" b: "));
                         Serial.println(mySerial.read());
                    }                          
                    #endif
                }
               
          
          return 1;
    }

    uint8_t getKeyPressed() {
      uint8_t retKey = key;
      key=0;
      Serial.print(F("-> Key consumed!"));
       return retKey;
    }

    bool isKeyPressed() {
      if (key>0) { 
          return true;
      }
      return false;
    }

     // transmit F( //////////////////////////////////////////////////////
    void transmit(uint8_t commandToken, const __FlashStringHelper *ifsh) {
    PGM_P p = reinterpret_cast<PGM_P>(ifsh);

    uint8_t len = 0;

    while (pgm_read_byte(p + len))
        len++;
        #if debug
          Serial.print(F("-> string len:"));
          Serial.println(len);
        #endif

    transmit(len, commandToken, (uint8_t*)p, true);
    }
    // transmit normal ///////////////////////////////////////////////

    void transmit(uint8_t commandToken, const char *b) {
    uint8_t len = 0;

    while (b[len]) len++;

    transmit(len, commandToken, (uint8_t*)b, false);
}

     void initCard() {
        transmit(INIT_CARD); 
     }
    

    // //////////////////////////////////////////////////////////////

    void print(const char* b) {
         transmit(PRINT, b);
    }
      
    void print(const __FlashStringHelper *ifsh) {
         transmit(PRINT, ifsh);
    }
    // //////////////////////////////////////////////////////////////


    void sdPrintp(const char* b) {
       transmit(SD_P_STRING, b);
    }

    void sdPrintp(const __FlashStringHelper *ifsh) {
       transmit(SD_P_STRING, ifsh);
    }

   void sdPrint(const char* s)  {
    uint8_t buf[32];

    uint8_t len = parseFastFont(s, buf);

    transmit(len, F_STRING, buf, false);
}

void sdPrint(const __FlashStringHelper *ifsh) {
    char tmp[32];

    PGM_P p = reinterpret_cast<PGM_P>(ifsh);

    uint8_t i = 0;
    while (pgm_read_byte(p+i))
    {
        tmp[i] = pgm_read_byte(p+i);
        i++;
    }
    tmp[i] = 0;

    uint8_t buf[32];
    uint8_t len = parseFastFont(tmp, buf);

    transmit(len, F_STRING, buf, false);
}
   
    uint8_t parseFastFont(const char* in, uint8_t* out) {
      
    uint8_t i = 0;
    uint8_t o = 0;

    while (in[i])
    {

        if (in[i] == '{')
        {
            if (isdigit(in[i+1]) &&
                isdigit(in[i+2]) &&
                isdigit(in[i+3]) &&
                in[i+4] == '}')
            {

                uint8_t v =
                    (in[i+1]-'0')*100 +
                    (in[i+2]-'0')*10 +
                    (in[i+3]-'0');

                out[o++] = v;
                i += 5;
                continue;
            }
        }

        out[o++] = in[i++];
    }

    return o;
}


void printAt(uint8_t x, uint8_t y, const char *b)
{
    uint8_t xy;
    setXY(xy, x, y);

    uint8_t len = 0;
    while (b[len]) len++;

    uint8_t a[len + 1];   // xy + text
    a[0] = xy;

    for (uint8_t i = 0; i < len; i++)
        a[i + 1] = b[i];

    transmit(len + 1, PRINT_AT, a, false);

    paramBytes = 1;
}

void printAt(uint8_t x, uint8_t y, const __FlashStringHelper *ifsh)
{
    PGM_P p = reinterpret_cast<PGM_P>(ifsh);

    uint8_t xy;
    setXY(xy, x, y);

    uint8_t len = 0;
    while (pgm_read_byte(p + len))
        len++;

    uint8_t a[len + 1];
    a[0] = xy;

    for (uint8_t i = 0; i < len; i++)
        a[i + 1] = pgm_read_byte(p + i);

    transmit(len + 1, PRINT_AT, a, false);
    paramBytes = 1;
}


      // print_Tile at
    void sdTileAt(uint8_t x,uint8_t y,uint8_t tileNo) {
       uint8_t a[2];
       setXY(a[0],x,y);
       a[1] = tileNo;
       transmit(sizeof(a),DRAW_SD_TILE, a);
    }
    /*
       // print_at
    void printAt(uint8_t x,uint8_t y,const char b[] ) {
        transmit(strlen(b),x,y,PRINT_AT, (uint8_t *)b);
    }
    */
      void home() {
         transmit(HOME); 
    }

      void clearKey() {
         transmit(CLEAR_KEY); 
    }

      void setU8x8I2cAdress(uint8_t i2cAdress) {
         transmit(SET_U8X8_I2CADRESS); 
    }

      void clearScreen() {
         transmit(CLEAR_SCREEN); 
    }
    void showScreen(uint8_t screenNo) {
        uint8_t s[1];
        s[0] = screenNo;
        transmit(1,SHOW_SCREEN,s);   
    }
   

  #if watchErr
    void getComErr() {
         transmit(GET_COM_ERR); 
         getParams();
         transmitErr = transmitErr + receiveBuf._UINT8_[0];   // count errors
    }
  #endif

    /*
   drawScreen gets the Pattern of a screen into the internal screenBitmap of SDGCARD
    parameters: screenNo , drawOptions, withLoad
    drawOptions:
    screenNo,
    [MASK_DRAW_FOREGROUND]
    [MASK_DRAW_BACKGROUND]
    [MASK_INVERT_FOREGROUND]
    [MASK_INVERT_BACKGROUND],

    [WITHOUTLOAD]
    [WITHLOAD]

    e.g. drawScreen(0,MASK_DRAW_FOREGROUND,WITHOUTLOAD);
    Loads screen 0, shows it on Display under considerationg the loaded screenBitmap

     e.g. drawScreen(0,MASK_DRAW_FOREGROUND,WITHLOAD);
    Loads screen 0, shows it on Display under considerationg the loaded screenBitmap
     AND overrides the actual screenBitmap with its own Pattern -> notice receivePattern() for local use
     
    
   can be used for Collisions
    */
    
    void drawScreen(uint8_t screenNo,uint8_t drawOption, uint8_t withLoad) {
       //Serial.print("  withLoad:");
       //Serial.println(withLoad);
        uint8_t b[3];
        b[0] = screenNo;
        b[1] =drawOption;
        b[2] = withLoad;        
      transmit(sizeof(b),SD_DRAW_SCREEN,b);
    }

     void drawScreens(uint8_t screenNo,uint8_t toScreenNo, uint8_t frameDelay, uint8_t mode) {
       //Serial.print("  withLoad:");
       //Serial.println(withLoad);
        uint8_t b[4];
        b[0] = screenNo;
        b[1] = toScreenNo;
        b[2] = frameDelay; 
        b[3] = mode;        
      transmit(sizeof(b),SD_DRAW_SCREENS,b);
    }
 
 

    void sdWordH(uint8_t stringNo) {
      transmit(1,SD_STRING_X,stringNo);
    }

    void sdWordV(uint8_t stringNo, uint8_t opCode) {
      //transmit(1,SD_STRING_Y,stringNo);
       uint8_t b[2];
        b[0] = stringNo;
        b[1] = opCode;
      transmit(sizeof(b)+1, SD_STRING_Y, (uint8_t*)b, false);
    }

    void setContrast(uint8_t c) {
      transmit(1,SET_CONTRAST,c);
    }

     void setFlipMode(uint8_t mode) {
      transmit(1,SET_FLIPMODE,mode); 
    }

     void setInverseFont(uint8_t mode) {
      transmit(1,SET_INVERSEFONT,mode); 
    }

     void setScreenPageNo(uint8_t mode) {
      transmit(1,SET_SPAGE,mode); 
    }

     void setTilePageNo(uint8_t mode) {
      transmit(1,SET_TPAGE,mode); 
    }

     void setWordPageNo(uint8_t mode) {
      transmit(1,SET_WPAGE,mode); 
    }



/*
PATTERN SECTION  compile if PATTERN_FUNCTIONS = 1 ##################################################################################################
*/

#if PATTERN_FUNCTIONS 

    void clearPattern() {
      transmit(SD_PATTERN_CLEAR); 
    }

    /*
    loads the pattern from a given screen in SD CARD Memory -> refer to Collision!
    -> possible patternFunction = PATTERN_NOGET or PATTERN_GET

    PATTERN_NOGET will hold the Patterns only in SDGCARD - can be used for setSpritePosition(x,y)
    PATTERN_GET   hold the Pattern in SDGCARD AND send back 16 Bytes to Host -> screenBitMap
    received Bytes will be stored in screenBitmap
   
    loadPattern(0,PATTERN_GET);
   
    */

    void loadPattern(uint8_t screen, uint8_t patternFunction) {
        uint8_t b[2];
        b[0] = screen;
        b[1] = patternFunction;
      
        if (patternFunction == PATTERN_GET) {
            getParams();            // consume ParamByte(s) from last command if not consumed
            paramBytes = 16;        // -> Back 16 Bytes Pattern - each Bit represents a tile on the screen
        }

        transmit(sizeof(b),SD_PATTERN_LOAD,b); 

        if (patternFunction == PATTERN_GET) {
            getParams();                // wait for Bytes
            memcpy(screenBitmap,receiveBuf._UINT8_,PATTERNBYTES);
            //debugDrawScreenBitmap();
        }
    }
    /*
    only transfer from sreenBitmap from SDGCard to client no Screenload before -> Map don't represent a load Screen
    when ist manipulated  -> usefull for manuell manipulating Areas
    */    

    void receivePattern() {
            getParams();            // consume ParamByte(s) from last command if not consumed
            paramBytes = 16;        // -> Back 16 Bytes Pattern - each Bit represents a tile on the screen
            transmit(SD_PATTERN_RECEIVE); 
            getParams();
            memcpy(screenBitmap,receiveBuf._UINT8_,PATTERNBYTES);
#if debug            
            //debugDrawScreenBitmap();
#endif             
    }

    /*
        Writes screenBitmap bak to SDGCards memory

    */ 
    void sendPattern() {
           if(sizeof(screenBitmap)>PATTERNBYTES) return;
           transmit(sizeof(screenBitmap),SD_PATTERN_PUT,screenBitmap); 
    }

    bool sdCollision(uint8_t x,uint8_t y) {
        uint8_t b[1];
        setXY(b[0],x,y);
        transmit(sizeof(b),SD_COLLISION,b);
        getParams(); // receive byte
        if(receiveBuf._UINT8_ [0] == 0) return false;       
        return true;
    }

/*
to use with your OWN PATTERNARRAY - make sure that #define U8X8COLS and define U8X8ROWS is matching your displaysize!

e.g. bool 

*/   

  bool isPositionOccupied(uint8_t x, uint8_t y)
{
    if (x >= U8X8COLS || y >= U8X8ROWS)
        return false;

    uint16_t tileIndex = (uint16_t)y * U8X8COLS + x;

    uint8_t byteIndex = tileIndex >> 3;
    uint8_t bitPos    = tileIndex & 7;

    return (screenBitmap[byteIndex] & (1 << bitPos)) != 0;
}

  void setPosition(uint8_t x, uint8_t y, bool value)
{
    if (x >= U8X8COLS || y >= U8X8ROWS)
        return;

    uint16_t idx = (uint16_t)y * U8X8COLS + x;

    uint8_t *ptr = &screenBitmap[idx >> 3];
    uint8_t mask = 1 << (idx & 7);

    if (value)
        *ptr |= mask;
    else
        *ptr &= ~mask;

        //debugDrawScreenBitmap();
}


#if debug // only if debug compile this function

void debugDrawScreenBitmap()
{
    const uint8_t rows = U8X8ROWS;      // z.B. 8
    const uint8_t cols = U8X8COLS;      // z.B. 16

    for (uint8_t y = 0; y < rows; y++) {
        for (uint8_t x = 0; x < cols; x++) {

            uint16_t tileIndex = (uint16_t)y * cols + x;

            uint8_t byteIndex = tileIndex >> 3;
            uint8_t bitPos    = tileIndex & 7;

            bool occupied = screenBitmap[byteIndex] & (1 << bitPos);

            if (occupied) {
                Serial.print("1");
            } 
            else {
               Serial.print (".");
            }
        }
        Serial.println("-");
    }
   
}
#endif

#endif

/*
end of Patternfunctions #####################################################################################################################################
*/
     void setCursor(uint8_t x,uint8_t y) {
        uint8_t b[1]; setXY(b[0],x,y);
        transmit(1,SET_CURSOR,b);
    }

     void setActive(uint8_t displayNum) {
        uint8_t b[1];
        b[0]=displayNum;
        transmit(1,SETACTIVE,b);
        isConsumed=true;   // es kommt nichts zurück!
    }

    void showScreens(uint8_t beginScreenNo,uint8_t endScreenNo, uint8_t frameDelay) {
       uint8_t a[3];
       a[0] = beginScreenNo;
       a[1] = endScreenNo;
       a[2] = frameDelay;
       transmit(3,SHOW_SCREENS, a);
    }

    /*
      Difference to ShowScreens = any new Command will interrupt the playing!
      Can be used for animated Busy Screens
    */
     
      void playScreens(uint8_t beginScreenNo,uint8_t endScreenNo, uint8_t frameDelay) {
       uint8_t a[3];
       a[0] = beginScreenNo;
       a[1] = endScreenNo;
       a[2] = frameDelay;
       transmit(3,PLAY_SCREENS, a);
       isConsumed=true;     // mark there are no parambytes, means new command will be send immidiatly wthou ACKN from G-Card 
    }

    /*
    Draws a part of a screen. Part can be : SCREEN_FULL , SCREEN_BOTTOM  , SCREEN_TOP 
    The offset defines the offset from the ScreenBorder in both directions 
    e.g. If the screen is 16 x 8 a Offset 1 means the only the inset without Border ist loaded
    */

    void showScreensPart(uint8_t beginScreenNo,uint8_t endScreenNo, uint8_t frameDelay, uint8_t xoffset, uint8_t yoffset, uint8_t part) {
       uint8_t a[6];
       a[0] = beginScreenNo;
       a[1] = endScreenNo;
       a[2] = frameDelay;
       a[3] = xoffset;
       a[4] = yoffset;
       a[5] = part;
       transmit(6,SHOW_SCREENS_PART, a);
    }

#if GRAPHIC_FUNCTIONS

 void  drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
       uint8_t a[4];
       a[0] = x0;
       a[1] = y0;
       a[2] = x1;
       a[3] = y1;
       transmit(4,SD_GFX_DRAW_LINE, a); 
    }   
void  drawVerticalLine (uint8_t x0, uint8_t y0, uint8_t x1) {
       uint8_t a[3];
       a[0] = x0;
       a[1] = y0;
       a[2] = x1; 
       transmit(3,SD_GFX_DRAW_VERTIKAL_LINE, a);
    }    

    void  drawRectangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
       uint8_t a[4];
       a[0] = x0;
       a[1] = y0;
       a[2] = x1;
       a[3] = y1;
       transmit(4,SD_GFX_DRAW_RECTANGLE, a);
    }  

   void  drawFilledRectangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
       uint8_t a[4];
       a[0] = x0;
       a[1] = y0;
       a[2] = x1;
       a[3] = y1;
       transmit(4,SD_GFX_DRAW_FILLED_RECTANGLE, a);
    }  

void  drawCircle (uint8_t x0, uint8_t y0, uint8_t r) {
       uint8_t a[3];
       a[0] = x0;
       a[1] = y0;
       a[2] = r;
       transmit(3,SD_GFX_DRAW_CIRCLE, a);
    }  

#endif
 /*
  Adds aoverlay command to the overlay stream
  Example: addOverlay(x, y glyph, OV_FLAG_ENABLED | OV_FLAG_RUNONCE | OV_FLAG_INVERSE, len, time);   4 = Len 
 */
    
 void  addOverlay (uint8_t x, uint8_t y, uint8_t glyphIndex, uint8_t flags, uint8_t len, uint8_t time) {
       uint8_t a[5];
       setXY(a[0],x,y);
       a[1] = glyphIndex;
       a[2] =flags;
       a[3] =time;
       setXY(a[4],len,0);
       transmit(sizeof(a),OV_ADD, a); 
    } 

 void  replaceOverlay (uint8_t index, uint8_t x, uint8_t y, uint8_t glyphIndex, uint8_t flags, uint8_t len, uint8_t time) {
       uint8_t a[6];
       a[0] = index;
       setXY(a[1],x,y);
       a[2] = glyphIndex;
       a[3] =flags;
       a[4] =time;
       setXY(a[5],len,0);
       transmit(sizeof(a),OV_REP, a); 
    }     

void  moveOverlay (uint8_t index, uint8_t x, uint8_t y) {
       uint8_t a[2];
       a[0] = index;
       setXY(a[1],x,y);
       transmit(sizeof(a),OV_MOV, a); 
    }     

    /* 
      Possible Keywords
      OV_BEGIN 
      OV_HOR_X 
      OV_HOR_Y 
      OV_VERT_X
      OV_VERT_Y 
    */

    
void overlayBegin() {
  transmit(OVERLAY_BEGIN); 
  }  

/*
Setup a 'Sprite'. It's one or more charcter from the U8x8 Fontset!
x,y     specifies the init Position where the Glyph ist displayed.
asc     is the Glyphs ASCII Code in the current Font (e.g. 65 = 'A')
len     specifies the numbers of Glyphs ar printed form the Beginning of asc (e.g. 3 means 'A','B','C' ist printed)
msDelay the time between the change of display Glyphs


e.g.    setSprite(4,0,65,3,10);

creates a sprite which begins at 65 ('A') with the len 3. So at Position 4,0 the Glyph 'A','B','C' is printed with
a Delay of 100 ms. The value you set will be multiplied by 10 !,so the smallest delay between to Glyphs = (1*10) 10 and the largest ms = 2550 (255 * 10)
So only one Glyph is printed in one Time at the Position which results in a animated Character. repeat 1 means a 'one Shot' ->'A' -> 'B' -> 'C' -> 'A' 

*/

#if SPRITE_FUNCTIONS

void setSprite(uint8_t x, uint8_t y,uint8_t tileIndex, uint8_t count, uint8_t msDelay) {
   uint8_t a[4];
       setXY(a[0],x,y);
       a[1] = tileIndex;
       a[2] = count;
       a[3] = msDelay;
     
       transmit(sizeof(a),SET_SPRITE,a);
}



void setSpritePosition(uint8_t x,uint8_t y) {
     uint8_t a[1];
       setXY(a[0],x,y);
       transmit(1,SET_SPRITE_POSITION,a);
}

/* depricated
void sprite(uint8_t e) {
    uint8_t a[1];
    a[1]= e;
    transmit(1,SPRITE,a);
}
*/
#endif
/*
get/set xyByte Helper funktionen /////////////////////////////////////
used to compress locations (x/y) in One byte
*/
void setX(uint8_t &b, uint8_t x) {
    b = (b & 0xF0) | (x & 0x0F);
}
void setY(uint8_t &b, uint8_t y) {
    b = (b & 0x0F) | ((y & 0x0F) << 4);
}
void setXY(uint8_t &b, uint8_t x, uint8_t y) {
    b = (x & 0x0F) | ((y & 0x0F) << 4);
}

uint8_t getX(uint8_t b) {
    return b & 0x0F;
}

uint8_t getY(uint8_t b) {
    return (b >> 4) & 0x0F;
}      
   /*
   Caution, not the ArduinoPins (Default 1 = D6,2 = D7,3 = D8, 4 = D9, 5 = A0, 6 = A1, 7= A2, 8 = A3)
   */
    uint8_t getValueFromPin() {
          return receiveBuf._UINT8_[0];
    }

 
  private:
    unsigned long timeout = 5000;
    bool isConsumed;
  public:
    receivebuf receiveBuf;
  
};
