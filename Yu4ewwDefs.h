#ifndef Yu4ewwDefs_h
#define Yu4ewwDefs_h
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "QuadEncoder.h"

#include "SPI.h"
#include "ILI9341_t3.h"
#include "font_Arial.h"
#define TFT_DC  9
#define TFT_CS 10
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

char Version[] = "T0.0, 07-01-2023";

//-----BUFFER-------------------------------------------
static const byte buffSize = 80;		// Buffer size
static char buffer[buffSize];

//---LOOP----------------------------------------
elapsedMillis loop_time;
static const int loop_period = 20;
static int loop_state = 0;
static const int loop_states = 5;

//----SERIAL----------------------------------------------
elapsedMillis SerialTime = 0;
static const int serialPeriod = 200;
static bool newData = false;

//----SERIAL 1--------------------------------------------
static const int Serial4Timeout = 20;
static bool newData4 = false;
static char txBuf4[32];
static char txBuf5[32];
static char Fa[9];
static bool newData5 = false;

//----IO PINS---------------------------------------------
static const int pttIn	 = 19;
static const int pinEnc0A = 3;
static const int pinEnc0B = 4;
static const int pinEnc1A = 5;
static const int pinEnc1B = 1;

static const int txdOut = 22;
static const int micPwr = 23;
static const int tftLight = 7;
static const int Outs = 8;
static const int outPin[Outs] = { 18, 15, 14, 41, 40, 39, 38, 37};

// -----BUTTONS--------------------------------------------
#define activeState 0
#define inactiveState 1
#define shortPress 0
#define longPress 1
#define nrInputs 8
#define nrMux 4
#define buttons 32

static const int buttonShortTime = 40;
static const int buttonLongTime = 500;
static int buttonPressTime[buttons] = {0};
elapsedMillis buttonTime0 = 0;
elapsedMillis buttonTime1 = 0;
elapsedMillis buttonTime2 = 0;
elapsedMillis buttonTime3 = 0;
elapsedMillis buttonTime4 = 0;
elapsedMillis buttonTime5 = 0;
elapsedMillis buttonTime6 = 0;
elapsedMillis buttonTime7 = 0;
elapsedMillis buttonTime8 = 0;
elapsedMillis buttonTime9 = 0;
elapsedMillis buttonTime10 = 0;
elapsedMillis buttonTime11 = 0;
elapsedMillis buttonTime12 = 0;
elapsedMillis buttonTime13 = 0;
elapsedMillis buttonTime14 = 0;
elapsedMillis buttonTime15 = 0;
elapsedMillis buttonTime16 = 0;
elapsedMillis buttonTime17 = 0;
elapsedMillis buttonTime18 = 0;
elapsedMillis buttonTime19 = 0;
elapsedMillis buttonTime20 = 0;
elapsedMillis buttonTime21 = 0;
elapsedMillis buttonTime22 = 0;
elapsedMillis buttonTime23 = 0;
elapsedMillis buttonTime24 = 0;
elapsedMillis buttonTime25 = 0;
elapsedMillis buttonTime26 = 0;
elapsedMillis buttonTime27 = 0;
elapsedMillis buttonTime28 = 0;
elapsedMillis buttonTime29 = 0;
elapsedMillis buttonTime30 = 0;
elapsedMillis buttonTime31 = 0;

static const int buttonIn[nrInputs] = { 29, 30, 31, 32, 25, 26, 27, 28 };
static const int Mux[nrMux] = { 36, 35, 34, 33 };
static int button = 0;
static const int ButtonNr[buttons]  =  {  0,  1,  2,  3,  4,  5,  6,  7,
																						8,  9, 10, 11, 12, 13, 14, 15,
																						16, 17, 18, 19, 20, 21, 22, 23,
																						24, 25, 26, 27, 28, 29, 30, 31 };	
static const String buttonName[buttons] = 
		{ "ANT1", "ANT2", "ANT3", "ANT4", "ANT5", "ANT6", "ANT7", "ANT8",
			"20  ", "15  ", "10  ", "6   ", "ENC1", "160 ", "80  ", "40  ",
			"BKIN", "X1  ", "RXAN", "TXAN", "ENC2", "SSB ", "CW  ", "DIG ", 
			"FIL+", "FIL-", "    ", "    ", "ATT+", "ATT-", "IPO+", "IPO-"};
static int buttonState[buttons]  		=  { 0 };
static const int maxPStates[buttons] =  {  1,  1,  1,  1,  1,  1,  1,  1,
																					  1,  1,  1,  1,  3,  1,  1,  1,
																					  1,  1,  1,  1,  5,  1,  1,  1,
																					  1,  1,  1,  1,  1,  1,  1,  1 };
static int presetState[buttons] = { 0 };
static int oldPresetState20 = 0;

// -------ENCODERS---------------------------------
QuadEncoder encT( 1, pinEnc0A, pinEnc0B );
static int enc0 = 0;
static int newEnc0 = 0;
static int enc0Max = 300;
static int enc0Min = -300;
QuadEncoder encB( 2, pinEnc1A, pinEnc1B );
static int enc1 = 0;
static int newEnc1 = 0;
static int enc1Max = 300;
static int enc1Min = -300;

//-----RADIO---------------------------------------------
static bool radioInitialized = false;
static int voxDelay = 0;
static bool voxDelayChanged = false;
static int scopeSpan = 0;
static bool scopeSpanChanged = false;
static int scopeSpanCw = 3;
static int scopeSpanSsb = 5;
static int scopeSpanDigi = 3;
static int scopeLevel = 0;
static bool scopeLevelChanged = false;
static int width = 0;
static bool widthChanged = false;
static int brakeDelay = 0;
static bool brakeDelayChanged = false;
static int idd = 0;
static int oldIdd = 0;
static bool iddChanged = false;
static int swr = 0;
static int oldSwr = 0;
static bool swrChanged = false;
static int power = 0;
static int oldPower = 0;
static bool powerChanged = false;
static int rFilter = 2;
static bool rFilterChanged = false;
static int att = 0;
static bool attChanged = false;
static int procLevel = 10;  
static bool procLevelChanged = false;
static int rfPower = 0;
static bool rfPowerChanged = false;
static int ipo = 0;
static bool ipoChanged = false;
static int monLevel = 10;
static bool monLevelChanged = false;
static char modeVal;
static bool modeValChanged = false;
static int cwSpeed = 15; 
static bool cwSpeedChanged = false; 
static int band = -1;
static bool bandChanged = false;
static int apf = 0;
static bool apfChanged = false;
static int brakeIn = 0;
static bool brakeInChanged = false;

// -------ANTENNAS---------------------------------
static int SelAnt = -1;
//static int RxAnt = 0;
//static int TxAnt = 0;
static const int Antennas = 8;
static int Out[Antennas] = {0};
static int newOut[Antennas] = {0};
static const int Bands = 7;
static bool antChanged = false;
static byte rxOuts = 0;
static byte txOuts = 0;
static byte newTxOuts = 0;

typedef struct Ant
{
	byte RxAnt   = 1;							// (0-8) 0 no Ant, 1-8 Ant1 - Ant8
	byte TxAnt   = 1;							// (0-8) 0 no Ant, 1-8 Ant1 - Ant8
	byte Out   = B00000001;			// (0-7) LSB 1, MSB 8
	byte TxBand = B01111111;			// (0-6) LSB 160 MSB-1 6
	String name;		// (0-7)
} Ant_t;
static Ant_t Ant[Antennas];		// (0-7)

static const String bandName[Bands] =  { "160", " 80", " 40", " 20", " 15", " 10", "  6" };


//-----EEPROM--------------------------------------------
static int eepromStart = 0;		// EEPROM START

//---DISPLAY COORDINATES---------------------------------------
#define x 0
#define y 1
#define w 2
#define h 3
#define xc 4
#define yc 5

#define x0 0
#define x1 80
#define x2 160
#define x3 240
#define x4 320
#define x5 198
#define y0 0
#define y1 30
#define y2 60
#define y3 110
#define y4 160
#define y5 210
#define y6 240
#define y7 120
#define y7a 55
#define y7b 80
#define y7c 145
#define y7d 170

#define svmarkers 11
byte s[svmarkers] = { 0, 58, 95, 107, 118, 128, 139, 157, 173, 180, 191}; // numbers correspond to power readout/2
#define swrScale 0.764
#define xsStart 3
#define xsEnd 195
#define ysLine 92
#define ysMarkerL 5
#define ysBar 72
#define ysBarL 20
#define ysText 100
#define ysText1 63
#define yswr0 40
#define yswr1 96

#define pvmarkers 11
byte p[pvmarkers] = { 0, 42, 64, 84, 96, 108, 118, 129, 139, 148, 157}; // numbers correspond to power readout* pwrScale
#define pwrScale 0.75
#define xpStart 3
#define xpEnd 195
#define ypLine 142
#define ypMarkerL 5
#define ypBar 122
#define ypBarL 20
#define ypText 150
#define ypText1 113
#define ypwr0 129
#define ypwr1 148

#define ivmarkers 10
byte id[ivmarkers] = { 0, 20, 40, 60, 80, 100, 120, 140, 160, 180 }; // numbers correspond to idd readout* iddScale
#define iddScale 0.75
#define xiStart 3
#define xiEnd 195
#define yiLine 192
#define yiMarkerL 5
#define yiBar 172
#define yiBarL 20
#define yiText 200
#define yiText1 163
#define yidd0 140
#define yidd1 160

#define aBgColor ILI9341_BLACK
#define borderColor ILI9341_DARKGREY
#define boxAColorBg ILI9341_BLACK
#define boxAColorRx ILI9341_DARKGREEN
#define boxAColorTx ILI9341_RED
#define boxAColorRxTx ILI9341_PURPLE
#define antTextColor ILI9341_WHITE
#define antTextSize 2
#define S1ColorBg ILI9341_BLACK
#define S1TextColor ILI9341_WHITE
#define S1TextSize 2
#define S1T1 10
#define S1D1 46
#define S1T2 82
#define S1D2 130
#define S1TXD 170
#define S1Txd1Color ILI9341_RED
#define S1Txd0Color ILI9341_GREEN
int S1TxdColor = S1Txd1Color; 
#define S2ColorBg ILI9341_BLACK
#define S2ColorSwr0 ILI9341_DARKGREEN
#define S2ColorSwr1 ILI9341_YELLOW
#define S2ColorSwr2 ILI9341_RED
#define S2TextColor ILI9341_WHITE
#define S2TextSize 1
#define S3ColorBg ILI9341_BLACK
#define S3ColorPwr0 ILI9341_DARKGREEN
#define S3ColorPwr1 ILI9341_YELLOW
#define S3ColorPwr2 ILI9341_RED
#define S3TextColor ILI9341_WHITE
#define S3TextSize 1
#define S4ColorBg ILI9341_BLACK
#define S4ColorIdd0 ILI9341_DARKGREEN
#define S4ColorIdd1 ILI9341_YELLOW
#define S4ColorIdd2 ILI9341_RED
#define S4TextColor ILI9341_WHITE
#define S4TextSize 1
#define E0ColorBg ILI9341_BLACK
#define E0TextColor ILI9341_WHITE
#define E0tTextSize 2
#define E0dTextSize 4
#define E1ColorBg ILI9341_BLACK
#define E1TextColor ILI9341_WHITE
#define E1tTextSize 2
#define E1dTextSize 4
//---- SET ANTx BOX COLOR---------
static int boxAColor[Antennas] = {0};
static int boxSwrColor[3] = {S2ColorSwr0, S2ColorSwr1, S2ColorSwr2};
static int boxPwrColor[3] = {S3ColorPwr0, S3ColorPwr1, S3ColorPwr2};
static int boxIddColor[3] = {S4ColorIdd0, S4ColorIdd1, S4ColorIdd2};

// -----SCREEN-----------------------------------------
static const String E0txt1[5] ={	"CW",
																"PROCESSOR",
																"MONITOR",
																"BRAKE",
																"VOX"	};
static const String E0txt2[5] ={	"SPEED",
																"LEVEL",
																"LEVEL",
																"DELAY",
																"DELAY"	};
static String E0Val;
static const String vdelay[34] = { "30","50","100","150","200","250","300","400","500","600",
																"700","800","900","1000","1100","1200","1300","1400","1500","1600",
																"1700","1800","1900","2000","2100","2200","2300","2400","2500","2600",
																"2700","2800","2900","3300"	};
static const String E1txt1[3] = {"SCOPE",
																"SCOPE",
																"RF"	};
static const String E1txt2[3] = {"LEVEL",
																"SPAN",
																"POWER"	};
static String E1Val;
static const String scopeSpanVal[10] = {"1K", "2K", "5K", "10K", "20K",
																			"50K", "100K", "200K", "500K", "1000K" };
static const String widthSsb[24] = { "def","300","400","600","850","1100","1200","1500","1650","1800",
																"1950","2100","2250","2400","2450","2500","2600","2700","2800","2900","3000","3200","3500","4000" };
static const String widthCw[19] = { "def","50","100","150","200","250","300","350","400","450",
																"500","600","800","1200","1400","1700","2000","2400","3000" };

//----RADIO PTT----------------------------------------
static int pttNew;
static int pttOld;
static const int pttTxDelay = 20;
static const int pttRxDelay = 10;
//static unsigned int changeDelay;
elapsedMillis changeDelay;
static bool delayWait = false;
static bool radioOnTx = false;

// -----FLAGS DEBUG------------------------------
typedef union debugFlags
{
	struct
	{
		unsigned but  		: 1; // Raw0
		unsigned enc  		: 1; // Raw1
		unsigned yaesuTx  : 1; // Raw1
		unsigned yaesuRx  : 1; // Raw1
		unsigned pcRx 	 	: 1; // Raw3
		unsigned disp	 		: 1; // Raw0 Az,i_Az
		unsigned eeprom 	: 1; // Raw1 status
		unsigned vel	: 1; // Raw1 velocity
	};
	unsigned int d_val;
} _debugFlags;
static _debugFlags dFlag;

// -----SCREEN FLAGS------------------------------
typedef union screenFlags
{
	struct
	{
		unsigned border	: 1; // Raw0
		unsigned ant  	: 1; // Raw1
		unsigned s1cw 	: 1; // Raw1
		unsigned s1rf 	: 1; // Raw1
		unsigned s1txd	: 1; // Raw1
		unsigned s2 		: 1; // Raw1
		unsigned s3  		: 1; // Raw3
		unsigned s4  		: 1; // Raw3
		unsigned clears	: 1; // Raw3
		unsigned enc0t 	: 1; // Raw0
		unsigned enc0d 	: 1; // Raw0
		unsigned enc1t 	: 1; // Raw1
		unsigned enc1d 	: 1; // Raw1
	};
	unsigned int s_val;
} _screenFlags;
static _screenFlags sFlag;

typedef union antennaFlags
{
	struct
	{
		unsigned ant1		: 1; // Raw0
		unsigned ant2		: 1; // Raw0
		unsigned ant3		: 1; // Raw0
		unsigned ant4		: 1; // Raw0
		unsigned ant5		: 1; // Raw0
		unsigned ant6		: 1; // Raw0
		unsigned ant7		: 1; // Raw0
		unsigned ant8		: 1; // Raw0
	};
	unsigned int a_val;
} _antennaFlags;
static _antennaFlags aFlag;

#endif
