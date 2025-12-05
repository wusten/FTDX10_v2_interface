#include "Yu4ewwDefs.h"
//   TO DO LIST  ??
// swr display ?
// Reset eeprom to default 

// ----Init Radio-----------------------------------
static void InitRadio()
{
	radioInitialized = true;
	ReadBand();
	if ( bandChanged )
	{
		bandChanged = false;
	}
	ReadMode();
	if ( modeValChanged )
	{
		if ( modeVal == '3' || modeVal == '7' )
		{			
			presetState[20] = 0;
		}	
		else if ( modeVal == '8' || modeVal == 'C' )
		{
			presetState[20] = 2;
		}		
		else
		{
			presetState[20] = 1;
		}
		modeValChanged = false;
	}
	oldPresetState20 = presetState[20];	
	ReadCwSpeed();
	ReadProcLevel();
	ReadMonLevel();
	ReadBrakeDelay();
	ReadVoxDelay();
	switch ( presetState[20] )
	{
		case 0:
		{
			if ( cwSpeedChanged )
			{
				enc0 = cwSpeed;
				enc0Min = 4;
				enc0Max = 60;
			}
			break;
		}
		case 1:
		{
			if ( procLevelChanged )
			{
				enc0 = procLevel;
				enc0Min = 0;
				enc0Max = 100;
			}
			break;
		}
		case 2:
		{
			if ( monLevelChanged )
			{
				enc0 = monLevel;
				enc0Min = 0;
				enc0Max = 100;
			}
			break;
		}
		case 3:
		{
			if ( brakeDelayChanged )
			{
				enc0 = brakeDelay;
				enc0Min = 0;
				enc0Max = 33;
			}
			break;
		}
		case 4:
		{
			if ( voxDelayChanged )
			{
				enc0 = voxDelay;
				enc0Min = 0;
				enc0Max = 33;
			}
			break;
		}
		default:
		break;
	}
	encT.write( 4 * enc0 );
	sFlag.s1cw = 1;
	sFlag.enc0t = 1;
	sFlag.enc0d = 1;
	cwSpeedChanged = false;
	procLevelChanged = false;
	monLevelChanged = false;
	brakeDelayChanged = false;
	voxDelayChanged = false;
	ReadScopeLevel();
	ReadScopeSpan();
	ReadRfPower();
	switch ( presetState[12] )
	{
		case 0:
		{
			if ( scopeLevelChanged )
			{
				enc1 = scopeLevel / 5;
				enc1Min = -60;
				enc1Max = 60;
			}
			break;
		}
		case 1:
		{
			if ( scopeSpanChanged )
			{
				enc1 = scopeSpan;
				enc1Min = 0;
				enc1Max = 9;
			}
			break;
		}
		case 2:
		{
			if ( rfPowerChanged )
			{
				if ( presetState[12] == 2 )
				{
					enc1 = rfPower;
					enc1Min = 5;
					enc1Max = 100;
				}
			}
			break;
		}
		default:
		break;
	}
	encB.write( 4 * enc1 );
	sFlag.s1rf = 1;
	sFlag.enc1t = 1;
	sFlag.enc1d = 1;
	scopeLevelChanged = false;
	scopeSpanChanged = false;
	rfPowerChanged = false;
	if ( !radioInitialized && Serial )
	{
		Serial.println("Radio not initialized");
		delay (1000);
	}
}
// -------------------------------------------------

// ----INIT ANTENNA ARRAY-----------------------------------
static void InitAntennas()
{
	Ant[0].RxAnt = 1;
	Ant[1].RxAnt = 2;
	Ant[2].RxAnt = 3;
	Ant[3].RxAnt = 4;
	Ant[4].RxAnt = 5;
	Ant[5].RxAnt = 6;
	Ant[6].RxAnt = 7;
	Ant[7].RxAnt = 0;

	Ant[0].TxAnt = 1;
	Ant[1].TxAnt = 2;
	Ant[2].TxAnt = 3;
	Ant[3].TxAnt = 4;
	Ant[4].TxAnt = 5;
	Ant[5].TxAnt = 6;
	Ant[6].TxAnt = 7;
	Ant[7].TxAnt = 0;

	Ant[0].Out = B00000000;
	Ant[1].Out = B00000010;
	Ant[2].Out = B00000001;
	Ant[3].Out = B00000101;
	Ant[4].Out = B00010000;
	Ant[5].Out = B00100000;
	Ant[6].Out = B01000000;
	Ant[7].Out = B10000000;

	Ant[0].TxBand = B01111111;
	Ant[1].TxBand = B00000000;
	Ant[2].TxBand = B00000000;
	Ant[3].TxBand = B00000000;
	Ant[4].TxBand = B00000000;
	Ant[5].TxBand = B00000000;
	Ant[6].TxBand = B00000000;
	Ant[7].TxBand = B00000000;

	Ant[0].name = String( "ANT1" );
	Ant[1].name = String( "ANT2" );
	Ant[2].name = String( "ANT3" );
	Ant[3].name = String( "ANT4" );
	Ant[4].name = String( "ANT5" );
	Ant[5].name = String( "ANT6" );
	Ant[6].name = String( "ANT7" );
	Ant[7].name = String( "ANT8" );  
}
// -------------------------------------------------

// -------------------------------------------------
static void CheckPtt()
{
	pttNew = digitalRead(pttIn);
	if ( pttNew )		// ptt high, RX
	{
		if ( pttNew != pttOld ) //from TX going to Rx
		{
//				Serial.println("PTT OFF");
        digitalWrite( txdOut, 1 );
			S1TxdColor = S1Txd1Color;
			sFlag.s1txd = 1;
			pttOld = pttNew;
			changeDelay = 0;
			delayWait = true;
      if ( antChanged )
			{
				txOuts = newTxOuts;
			}
			radioOnTx = false;
		}
		else //on RX
		{
			if ( antChanged )
			{
				delayWait = true;
				antChanged = false;
				changeDelay = 0;
			}
			if ( delayWait )
			{
				if ( changeDelay > pttRxDelay ) //delay time expired
				{
					for ( byte j = 0; j < Outs; j++ )
					{
						newOut[j] =  bitRead( rxOuts, j );
						if ( Out[j] != newOut[j] )
						{
							Out[j] = newOut[j];
							digitalWrite( outPin[j], Out[j] );
						}
					}
					delayWait = false;
				}
			}					
		}
	}
	else	// ptt low, TX
	{
		if ( bitRead( Ant[SelAnt].TxBand, band ) == 1 && Ant[SelAnt].TxAnt != 0 )
		{
			if ( pttNew != pttOld ) //from RX going to TX
			{
				pttOld = pttNew;
				for ( byte j = 0; j < Outs; j++ )
				{
					newOut[j] =  bitRead( txOuts, j );
					if ( Out[j] != newOut[j] )
					{
						Out[j] = newOut[j];
						digitalWrite( outPin[j], Out[j] );
					}
				}
				changeDelay = 0;
				delayWait = true;
				radioOnTx = true; 
			}
			else //on TX
			{
				if ( delayWait )
				{
					if ( changeDelay > pttTxDelay ) //delay time expired
					{
//						Serial.println("PTT ON");
            digitalWrite( txdOut, 0 );
						S1TxdColor = S1Txd0Color;
						sFlag.s1txd = 1;
						delayWait = false;
					}
				}
			}
		}
	}
}
// -------------------------------------------------

// -------------------------------------------------
void PlotPowerBar()
{
	if (radioOnTx)
	{
		ReadPower();
		if ( powerChanged )
		{
//			Serial.println(power);
                        sFlag.s3 = 1;
			powerChanged = false;
		}
		sFlag.clears= 1;
	}
	else
	{
		if ( sFlag.clears )
		{
			power = 0;
			swr = 0;
			idd = 0;
			sFlag.s2 = 1;
			sFlag.s3 = 1;
			sFlag.s4 = 1;
			sFlag.clears = 0;
		}
	}	
}
// -------------------------------------------------

// -------------------------------------------------
void PlotSwrBar()
{
	if (radioOnTx)
	{
		ReadSwr();
		if ( swrChanged )
		{
			sFlag.s2 = 1;
				swrChanged = false;
		}
		sFlag.clears= 1;
	}
	else
	{
		if ( sFlag.clears )
		{
			power = 0;
			swr = 0;
			idd = 0;
			sFlag.s2 = 1;
			sFlag.s3 = 1;
			sFlag.s4 = 1;
			sFlag.clears = 0;
		}
	}	
}
// -------------------------------------------------

// -------------------------------------------------
void PlotIddBar()
{
	if (radioOnTx)
	{
		ReadIdd();
		if ( iddChanged )
		{
			sFlag.s4 = 1;
			iddChanged = false;
		}
		sFlag.clears= 1;
	}
	else
	{
		if ( sFlag.clears )
		{
			power = 0;
			swr = 0;
			idd = 0;
			sFlag.s2 = 1;
			sFlag.s3 = 1;
			sFlag.s4 = 1;
			sFlag.clears = 0;
		}
	}
}
// -------------------------------------------------

// ----SETUP----------------------------------------
void setup()
{
	delay (500);
// ----SETUP IO-------------------------------------
	encT.setInitConfig();
 //Optional filter setup
 //encT.EncConfig.filterCount = 5;
 //encT.EncConfig.filterSamplePeriod = 255;
	encT.init();
	encB.setInitConfig();
 //Optional filter setup
 //encB.EncConfig.filterCount = 5;
 //encB.EncConfig.filterSamplePeriod = 255;
	encB.init();
	pinMode(pttIn, INPUT_PULLUP);
	pttOld = digitalRead ( pttIn );
	pinMode(txdOut, OUTPUT);
	digitalWrite(txdOut, 1);
	pinMode(micPwr, OUTPUT);
	digitalWrite(micPwr, 0);
	pinMode(tftLight, OUTPUT);
	analogWriteFrequency(tftLight, 560);
	analogWrite(tftLight, 255);
	for (byte i = 0; i < nrInputs; i++)
	{
		pinMode(buttonIn[i], INPUT);
	}
	for (byte i = 0; i < nrMux; i++)
	{
		pinMode(Mux[i], OUTPUT);
		digitalWrite(Mux[i], 0);
	}
	for (byte i = 0; i < Outs; i++)
	{
		pinMode(outPin[i], OUTPUT);
		digitalWrite(outPin[i], 0);
	}
// ----SETUP SERIAL---------------------------------
	Serial.begin(115200);	// Serial PC
	Serial4.begin(38400);	// Serial Radio
	while(!Serial4);
	Serial4.flush();
	Serial5.begin(38400, SERIAL_8N2);	// Serial Amp
	while(!Serial5);
	Serial5.flush();
// ----SETUP TFT-----------------------------------
	tft.begin();
	tft.setClock(60000000);
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
//---------- TEMP FLAGS-----------------------------
	dFlag.yaesuRx = 1;
  dFlag.yaesuTx = 1;
//	dFlag.pcRx = 1;
//	dFlag.enc= 1;
//	dFlag.disp = 1;	// temp
//	dFlag.eeprom = 1;
//	dFlag.but = 1;
// ----INIT-----------------------------------------	
	sFlag.s_val = 0xFFFF;	// for InitDisplay
	aFlag.a_val = 0xFF;		// for InitDisplay
	InitRadio();
//	EEPROM.update(eepromStart, 0xFF);
	InitEeprom();
  InitDisplay();
	buttonPress(0,0);	//init first ant at start
  UpdateDisplay();
	sFlag.s_val = 0;	//reset screen flags
	aFlag.a_val = 0;	//reset screen flags
	if ( Serial )
	{
		sprintf(buffer, "** YU4EWW FTDX10 ** %s **", Version);
		Serial.println(buffer);
	}
	// ----INIT TIMERS----------------------------------
	loop_time = 0;
}
// -------------------------------------------------

// ----MAIN LOOP------------------------------------
void loop()
{
	CheckPtt();
  CheckAmp();
	if ( loop_time >= loop_period )
	{
		loop_time = 0;
		if ( loop_state == loop_states )
		{
			loop_state = 0;
		}
		else
		{
			loop_state = loop_state + 1;
		}
		switch (loop_state)
		{
			case 0: // Swr bar
			{
				PlotSwrBar();
				CheckPtt();
				CheckEncoders();
//				UpdateDisplay();
				break;
			}
			case 1: // Serial
			{
				if (  Serial )
				{
					Process_serial();
				}
				CheckPtt();
				CheckButtons();
//				UpdateDisplay();
				break;
			}
			case 2: //Power bar
			{
				PlotPowerBar();
				CheckPtt();
				CheckEncoders();
				UpdateDisplay();
				break;
			}
			case 3: //Amp
			{
				
				CheckPtt();
				CheckButtons();		
//				UpdateDisplay();
				break;
			}		
			case 4: //Idd bar
			{
				PlotIddBar();
				CheckPtt();
				CheckEncoders();
//				UpdateDisplay();
				break;
			}
			case 5: //Radio
			{
				//CheckRadio();
				CheckPtt();
				CheckButtons();		
				UpdateDisplay();
				break;
			}
			default:
			break;
		}
	}		
}
