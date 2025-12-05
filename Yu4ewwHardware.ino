// -----CHECK BUTTONS-------------------------------
static void CheckButtons()
{
	for ( byte j = 0; j < nrMux; j++ )
	{
		digitalWrite(Mux[j], 1);
		delayMicroseconds(200);
		for ( byte i = 0; i < nrInputs; i++ )
		{
			button = j * nrInputs + i;
			if ( button < buttons )
			{
				if ( buttonState[button] == 0 && digitalRead(buttonIn[i]) == activeState )
				{
					startButtonTimer(button);
					buttonState[button] = 1;
					if ( dFlag.but && Serial )
					{
						Serial.print("Button Nr ");
						Serial.print(button);
						Serial.println( " pressed" );
					}
				}	
				if ( buttonState[button] != 0 && digitalRead(buttonIn[i]) == inactiveState )
				{
					readButtonTimer(button);
					buttonState[button] = 0;
					if ( buttonPressTime[button] > buttonLongTime )
					{
						if ( dFlag.but && Serial )
						{
							Serial.print("Button Nr ");
							Serial.print( button );
							Serial.print( " released after " );
							Serial.println( buttonPressTime[button] );
						}
						buttonPress( button, longPress );
					}
					else
					{
						if ( buttonPressTime[button] > buttonShortTime )
						{
							if ( dFlag.but && Serial )
							{
								Serial.print("Button Nr ");
								Serial.print( button );
								Serial.print( " released after " );
								Serial.println( buttonPressTime[button] );
							}
							buttonPress( button, shortPress );
						}
					}
				}
			}				
		}
		digitalWrite(Mux[j], 0);
		delayMicroseconds(200);
	}
}
//-----------------------------------------------------------

// ----START TIMER--------------------------------------
static void startButtonTimer( int nr )
{
	switch (nr)
	{
		case 0:	{	buttonTime0 = 0; break;	}
		case 1:	{	buttonTime1 = 0; break;	}
		case 2:	{	buttonTime2 = 0; break;	}
		case 3:	{	buttonTime3 = 0; break;	}
		case 4:	{	buttonTime4 = 0; break;	}
		case 5:	{	buttonTime5 = 0; break;	}
		case 6:	{	buttonTime6 = 0; break;	}
		case 7:	{	buttonTime7 = 0; break;	}
		case 8:	{	buttonTime8 = 0; break;	}
		case 9:	{	buttonTime9 = 0; break;	}
		case 10:	{	buttonTime10 = 0; break;	}
		case 11:	{	buttonTime11 = 0; break;	}
		case 12:	{	buttonTime12 = 0; break;	}
		case 13:	{	buttonTime13 = 0; break;	}
		case 14:	{	buttonTime14 = 0; break;	}
		case 15:	{	buttonTime15 = 0; break;	}
		case 16:	{	buttonTime16 = 0; break;	}
		case 17:	{	buttonTime17 = 0; break;	}
		case 18:	{	buttonTime18 = 0; break;	}
		case 19:	{	buttonTime19 = 0; break;	}
		case 20:	{	buttonTime20 = 0; break;	}
		case 21:	{	buttonTime21 = 0; break;	}
		case 22:	{	buttonTime22 = 0; break;	}
		case 23:	{	buttonTime23 = 0; break;	}
		case 24:	{	buttonTime24 = 0; break;	}
		case 25:	{	buttonTime25 = 0; break;	}
		case 26:	{	buttonTime26 = 0; break;	}
		case 27:	{	buttonTime27 = 0; break;	}
		case 28:	{	buttonTime28 = 0; break;	}
		case 29:	{	buttonTime29 = 0; break;	}
		case 30:	{	buttonTime30 = 0; break;	}
		case 31:	{	buttonTime31 = 0; break;	}
	}
}
// ----START TIMER--------------------------------------

// ----READ TIMER--------------------------------------
static void readButtonTimer( int nr )
{
	switch (nr)
	{
		case 0:	{	buttonPressTime[nr] = buttonTime0; break;	}
		case 1:	{	buttonPressTime[nr] = buttonTime1; break;	}
		case 2:	{	buttonPressTime[nr] = buttonTime2; break;	}
		case 3:	{	buttonPressTime[nr] = buttonTime3; break;	}
		case 4:	{	buttonPressTime[nr] = buttonTime4; break;	}
		case 5:	{	buttonPressTime[nr] = buttonTime5; break;	}
		case 6:	{	buttonPressTime[nr] = buttonTime6; break;	}
		case 7:	{	buttonPressTime[nr] = buttonTime7; break;	}
		case 8:	{	buttonPressTime[nr] = buttonTime8; break;	}
		case 9:	{	buttonPressTime[nr] = buttonTime9; break;	}
		case 10:	{	buttonPressTime[nr] = buttonTime10; break;	}
		case 11:	{	buttonPressTime[nr] = buttonTime11; break;	}
		case 12:	{	buttonPressTime[nr] = buttonTime12; break;	}
		case 13:	{	buttonPressTime[nr] = buttonTime13; break;	}
		case 14:	{	buttonPressTime[nr] = buttonTime14; break;	}
		case 15:	{	buttonPressTime[nr] = buttonTime15; break;	}
		case 16:	{	buttonPressTime[nr] = buttonTime16; break;	}
		case 17:	{	buttonPressTime[nr] = buttonTime17; break;	}
		case 18:	{	buttonPressTime[nr] = buttonTime18; break;	}
		case 19:	{	buttonPressTime[nr] = buttonTime19; break;	}
		case 20:	{	buttonPressTime[nr] = buttonTime20; break;	}
		case 21:	{	buttonPressTime[nr] = buttonTime21; break;	}
		case 22:	{	buttonPressTime[nr] = buttonTime22; break;	}
		case 23:	{	buttonPressTime[nr] = buttonTime23; break;	}
		case 24:	{	buttonPressTime[nr] = buttonTime24; break;	}
		case 25:	{	buttonPressTime[nr] = buttonTime25; break;	}
		case 26:	{	buttonPressTime[nr] = buttonTime26; break;	}
		case 27:	{	buttonPressTime[nr] = buttonTime27; break;	}
		case 28:	{	buttonPressTime[nr] = buttonTime28; break;	}
		case 29:	{	buttonPressTime[nr] = buttonTime29; break;	}
		case 30:	{	buttonPressTime[nr] = buttonTime30; break;	}
		case 31:	{	buttonPressTime[nr] = buttonTime31; break;	}
	}	
}
// ----READ TIMER--------------------------------------

//-----BAND CHANGE----------------------------------------
void bandChange()
{
	SetBand();
	ReadMode();
	if ( modeVal == '3' || modeVal == '7' )
	{			
		presetState[20] = 0;
		enc0 = ReadCwSpeed();
		enc0Min = 4;
		enc0Max = 60;
		cwSpeedChanged = false;
	}	
	else if ( modeVal == '8' || modeVal == 'C' )
	{			
		presetState[20] = 2;
		enc0 = ReadMonLevel();
		enc0Min = 0;
		enc0Max = 100;
		monLevelChanged = false;
	}
	else
	{
		presetState[20] = 1;
		enc0 = ReadProcLevel();
		enc0Min = 0;
		enc0Max = 100;
		procLevelChanged = false;
	}
	encT.write( 4 * enc0 );
	oldPresetState20 = presetState[20];
	modeValChanged = false;	
	sFlag.enc0t = 1;
	sFlag.enc0d = 1;
	if ( presetState[12] == 0 )
	{
		enc1 = ReadScopeLevel() / 5;
		enc1Min = -60;
		enc1Max = 60;
		scopeLevelChanged = false;
	}
	if ( modeVal == '3' || modeVal == '7' )
	{
		scopeSpan = scopeSpanCw;
	}
	else if ( modeVal == '8' || modeVal == 'C' )
	{
		scopeSpan = scopeSpanDigi;
	}
	else
	{
		scopeSpan = scopeSpanSsb;
	}
	SetScopeSpan();
	if ( presetState[12] == 1 )
	{
		enc1 = scopeSpan;
		enc1Min = 0;
		enc1Max = 9;
	}
	encB.write( 4 * enc1 );
	sFlag.enc1t = 1;
	sFlag.enc1d = 1;	
}
//-------------------------------------------------------

//-------------------------------------------------------
static void buttonPress(int button, int press_type)
{
	switch (button)
	{
		case 0: // Select Ant1 Rx/Tx
		case 1: // Select Ant2 Rx/Tx
		case 2: // Select Ant3 Rx/Tx
		case 3: // Select Ant4 Rx/Tx
		case 4: // Select Ant5 Rx/Tx
		case 5: // Select Ant6 Rx/Tx
		case 6: // Select Ant7 Rx/Tx
		case 7: // Select Ant8 Rx/Tx
		{
			if ( press_type == shortPress )
			{
				if (  button != SelAnt )
				{
					ClearAnt();
					SelAnt = button;
					SetAnt();
					rxOuts = Ant[Ant[SelAnt].RxAnt-1].Out;
					if ( radioOnTx )
					{
						newTxOuts = Ant[Ant[SelAnt].TxAnt-1].Out;
					}
					else
					{
						txOuts = Ant[Ant[SelAnt].TxAnt-1].Out;
					}
					antChanged = true;
				}
			}
			break;
		}
		case 8: // Brake_In
		{
			ReadBrakeIn();
			if ( brakeIn == 0 )
			{
				brakeIn = 1;
			}
			else
			{
					brakeIn = 0;
			}
			brakeInChanged = false;
			SetBrakeIn();
			break;
		}
		case 9: // x1
		{
			break;
		}
		case 10: // Rx Ant
		{
			if ( press_type == shortPress )
			{
				ClearAnt();
				if (Ant[SelAnt].RxAnt == 8 )
				{
					Ant[SelAnt].RxAnt = 0;
				}
				else
				{
					Ant[SelAnt].RxAnt = Ant[SelAnt].RxAnt + 1;
				}
				SetAnt();
				rxOuts = Ant[Ant[SelAnt].RxAnt-1].Out;
				antChanged = true;
				break;
			}
			if ( press_type == longPress )
			{
				UpdateEepromRxAnt(SelAnt);	
				break;
			}
		}
		case 11: // Tx Ant
		{
			if ( press_type == shortPress )
			{
				ClearAnt();
				if ( Ant[SelAnt].TxAnt == 8 )
				{
					Ant[SelAnt].TxAnt = 0;
				}
				else
				{
					Ant[SelAnt].TxAnt = Ant[SelAnt].TxAnt + 1;
				}
				SetAnt();
				if ( radioOnTx )
				{
					newTxOuts = Ant[Ant[SelAnt].TxAnt-1].Out;
				}
				else
				{
					txOuts = Ant[Ant[SelAnt].TxAnt-1].Out;
				}
				antChanged = true;
				break;
			}
			if ( press_type == longPress )
			{
				UpdateEepromTxAnt(SelAnt);	
				break;
			}
		}
		case 12: // Enc1 button
		{
			presetState[12] =  presetState[12] + 1;
			if ( presetState[12] >= maxPStates[12] )
			{
				presetState[12] = 0;
			}
			if ( presetState[12] == 0 )
			{
				enc1 = ReadScopeLevel() / 5;
				enc1Min = -60;
				enc1Max = 60;
				scopeLevelChanged = false;
			}
			if ( presetState[12] == 1 )
			{
				enc1 = ReadScopeSpan();
				enc1Min = 0;
				enc1Max = 9;
				scopeSpanChanged = false;
			}
			if ( presetState[12] == 2 )
			{
				enc1 = ReadRfPower();
				enc1Min = 5;
				enc1Max = 100;
				rfPowerChanged = false;
			}
			encB.write( 4 * enc1 );
			sFlag.enc1t = 1;
			sFlag.enc1d = 1;
			break;
		}
		case 13: // SSB mode
		{
			if (band < 3)
			{
				modeVal = '1';
			}
			else
			{
				modeVal = '2';
			}
			SetMode();
			procLevel = 40;
			presetState[20] = 1;
			oldPresetState20 = presetState[20];
			enc0 = procLevel;
			enc0Min = 0;
			enc0Max = 100;
			encT.write( 4 * enc0 );
			SetProcLevel();
			if ( presetState[12] == 0 )
			{
				ReadScopeLevel();
				enc1 = scopeLevel / 5;
				enc1Min = -60;
				enc1Max = 60;
				scopeLevelChanged = false;
			}
			scopeSpan = scopeSpanSsb;
			if ( presetState[12] == 1 )
			{
				enc1 = scopeSpan;
				enc1Min = 0;
				enc1Max = 9;
			}
			SetScopeSpan();
			encB.write( 4 * enc1 );
			rFilter = 2;
			SetRFilter();
			width = 17;
			SetWidth();
			sFlag.enc0t = 1;
			sFlag.enc0d = 1;
			sFlag.enc1t = 1;
			sFlag.enc1d = 1;
			break;
		}
		case 14: // CW mode
		{
			if ( band < 3 )
			{
				modeVal = '7';
			}
			else
			{
				modeVal = '3';
			}
			SetMode();
			presetState[20] = 0;
			oldPresetState20 = presetState[20];
			ReadCwSpeed();
			enc0 = cwSpeed;
			enc0Min = 4;
			enc0Max = 60;
			cwSpeedChanged = false;
			encT.write( 4 * enc0 );
			if ( presetState[12] == 0 )
			{
				ReadScopeLevel();
				enc1 = scopeLevel / 5;
				enc1Min = -60;
				enc1Max = 60;
				scopeLevelChanged = false;
			}
			scopeSpan = scopeSpanCw;
			if ( presetState[12] == 1 )
			{
				enc1 = scopeSpan;
				enc1Min = 0;
				enc1Max = 9;
			}
			SetScopeSpan();
			encB.write( 4 * enc1 );
			rFilter = 5;
			SetRFilter();
			width = 6;
			SetWidth();
			apf = 1;
			SetApf();
			sFlag.enc0t = 1;
			sFlag.enc0d = 1;
			sFlag.enc1t = 1;
			sFlag.enc1d = 1;
			break;
		}
		case 15: // DIGI mode
		{
			modeVal = 'C';
			SetMode();
			ReadMonLevel();
			presetState[20] = 2;
			oldPresetState20 = presetState[20];
			enc0 = monLevel;
			enc0Min = 0;
			enc0Max = 100;
			procLevel = 0;
//			SetProcLevel();	// processor off
			encT.write( 4 * enc0 );			
			if ( presetState[12] == 0 )
			{
				ReadScopeLevel();
				enc1 = scopeLevel / 5;
				enc1Min = -60;
				enc1Max = 60;
			}
			scopeSpan = scopeSpanDigi;
			SetScopeSpan();
			if ( presetState[12] == 1 )
			{
				enc1 = scopeSpan;
				enc1Min = 0;
				enc1Max = 9;
			}
			encB.write( 4 * enc1 );
			rFilter = 2;
			SetRFilter();
			width = 18;
			SetWidth();
			sFlag.enc0t = 1;
			sFlag.enc0d = 1;
			sFlag.enc1t = 1;
			sFlag.enc1d = 1;
			break;
		}
		case 20: // Enc0 button
		{
			modeVal = ReadMode();
			presetState[20] = presetState[20] + 1;
			if ( presetState[20] >= maxPStates[20] )
			{
				presetState[20] = 0;
			}
			if ( modeVal == '3' || modeVal == '7' ) // CW
			{			
				if ( presetState[20] == 1 )
				{
					presetState[20] = 2;
				}
				if ( presetState[20] == 4 )
				{
					presetState[20] = 0;
				}
			}	
			else
			{
				if ( presetState[20] == 0 )
				{
					presetState[20] = 1;
				}
				if ( presetState[20] == 3 )
				{
					presetState[20] = 4;
				}				
			}
			oldPresetState20 = presetState[20];
			modeValChanged = false;
			if ( presetState[20] == 0 )
			{
				enc0 = ReadCwSpeed();
				enc0Min = 4;
				enc0Max = 60;
				cwSpeedChanged = false;
			}
			if ( presetState[20] == 1 )
			{
				enc0 = ReadProcLevel();
				enc0Min = 0;
				enc0Max = 100;
				procLevelChanged = false;				
			}
			if ( presetState[20] == 2 )
			{
				enc0 = ReadMonLevel();
				enc0Min = 0;
				enc0Max = 100;
				monLevelChanged = false;				
			}    
			if ( presetState[20] == 3 )
			{
				enc0 = ReadBrakeDelay();
				enc0Min = 0;
				enc0Max = 33;
				brakeDelayChanged = false;
			} 	
			if ( presetState[20] == 4 )
			{
				enc0 = ReadVoxDelay();
				enc0Min = 0;
				enc0Max = 33;
				voxDelayChanged = false;
			} 
			encT.write( 4 * enc0 );
			sFlag.enc0t = 1;
			sFlag.enc0d = 1;
			break;
		}
		case 16: // Band 20m button
		case 17: // Band 15m button
		case 18: // Band 10m button
		case 19: // Band 6m button
		case 21: // Band 160m button
		case 22: // Band 80m button
		case 23: // Band 40m button
		{
			int newBand = 0;
			bandChanged = false;
			if (button > 20 )
			{
				newBand = button - 21;
			}
			else
			{
				newBand = button - 13;
			}
			if ( newBand != band )
			{
				band = newBand;
				bandChanged = true;
			}
			bandChange();
			break;
		}
		case 28: // ATT -
		{
			ReadAtt();
			int new_att = att - 1;
			if ( new_att < 0 )
			{
				new_att = 0;
			}
			if ( new_att != att )
			{
				att = new_att;
				SetAtt();
			}
			attChanged = false;
			break;
		}
		case 29: // ATT +
		{
			ReadAtt();
			int new_att = att + 1;
			if ( new_att > 4 )
			{
				new_att = 3;
			}
			if ( new_att != att )
			{
				att = new_att;
				SetAtt();
			}
			attChanged = false;
			break;
		}
		case 30: // IPO -
		{
			ReadIpo();
			int new_ipo = ipo - 1;
			if ( new_ipo < 0 )
			{
				new_ipo = 0;
			}
			if ( new_ipo != ipo )
			{
				ipo = new_ipo;
				SetIpo();
			}
			ipoChanged = false;
			break;
		}
		case 31: // IPO +
		{
			ReadIpo();
			int new_ipo = ipo + 1;
			if ( new_ipo > 2 )
			{
				new_ipo = 2;
			}
			if ( new_ipo != ipo )
			{
				ipo = new_ipo;
				SetIpo();
			}
			ipoChanged = false;
			break;
		}
		case 24: // FIL -
		{
			ReadRFilter();
			int new_rFilter = rFilter - 1;
			if ( new_rFilter < 1 )
			{
				new_rFilter = 1;
			}
			if ( new_rFilter == 3 )
			{
				new_rFilter = 2;
			}
			if ( new_rFilter != rFilter )
			{
				rFilter = new_rFilter;
				SetRFilter();
			}
			rFilterChanged = false;
			break;
		}
		case 25: // FIL +
		{
			ReadRFilter();
			int new_rFilter = rFilter + 1;
			if ( new_rFilter > 5 )
			{
				new_rFilter = 5;
			}
			if ( new_rFilter == 3 )
			{
				new_rFilter = 4;
			}
			if ( new_rFilter != rFilter )
			{
				rFilter = new_rFilter;
				SetRFilter();
			}
			rFilterChanged = false;
			break;
		}
		default:
		break;
	}
}
// -------------------------------------------------

// ----CHECK ENCODERS-------------------------------
static void CheckEncoders()
{
	newEnc0 = encT.read() / 4;
	if ( enc0 != newEnc0 )
	{
		enc0 = newEnc0;
		if ( enc0 > enc0Max )
		{
			encT.write( 4 * enc0Max );
			enc0 = enc0Max;
		}
		if ( enc0 < enc0Min )
		{
			encT.write( 4 * enc0Min );
			enc0 = enc0Min;
		}
		UpdateEnc0();
	}
	newEnc1 = encB.read() / 4;
	if ( enc1 != newEnc1 )
	{
		enc1 = newEnc1;
		if ( enc1 > enc1Max )
		{
			encB.write( 4 * enc1Max );
			enc1 = enc1Max;
		}
		if ( enc1 < enc1Min )
		{
			encB.write( 4 * enc1Min );
			enc1 = enc1Min;
		}
		UpdateEnc1();
	}
}
// -------------------------------------------------

// ---UPDATE ENC0-----------------------------------
static void UpdateEnc0()
{
	if ( dFlag.enc && Serial )
	{
		Serial.print ( "Enc0 = " );
		Serial.println ( enc0 );
	}	
	if ( presetState[20] == 0 )
	{
		cwSpeed = enc0;
		sFlag.s1cw = 1;
	}
	if ( presetState[20] == 1 )
	{
		procLevel = enc0;
	}
	if ( presetState[20] == 2 )
	{
		monLevel = enc0;
	}
	if ( presetState[20] == 3 )
	{
		brakeDelay = enc0;
	}
	if ( presetState[20] == 4 )
	{
		voxDelay = enc0;
	}
	UpdateRadio0();
	sFlag.enc0d = 1;
}
// -------------------------------------------------

// ---UPDATE ENC1-----------------------------------
static void UpdateEnc1()
{
	if ( dFlag.enc && Serial )
	{
		Serial.print ( "Enc1 = " );
		Serial.println ( enc1 );
	}
	if ( presetState[12] == 0 )
	{
		scopeLevel = 5 * enc1;
	}
	if ( presetState[12] == 1 )
	{
		if ( modeVal == '3' || modeVal == '7' )
		{
			scopeSpan = enc1;
			scopeSpanCw = scopeSpan;
		}
		else
		{
			scopeSpan = enc1;
			scopeSpanSsb = enc1;
		}
	}
	if ( presetState[12] == 2 )
	{
		rfPower = enc1;
		sFlag.s1rf = 1;
	}
	UpdateRadio1();
	sFlag.enc1d = 1;
}
// -------------------------------------------------

// ----CLEAR ANT------------------------------------
static void ClearAnt()
{
	if ( Ant[SelAnt].RxAnt > 0 )
	{
		boxAColor[ Ant[SelAnt].RxAnt - 1 ] = boxAColorBg;
		SetAFlags( Ant[SelAnt].RxAnt );
	}
	if ( Ant[SelAnt].RxAnt != Ant[SelAnt].TxAnt && Ant[SelAnt].TxAnt > 0 )
	{
		boxAColor[ Ant[SelAnt].TxAnt - 1 ] = boxAColorBg;
		SetAFlags( Ant[SelAnt].TxAnt );
	}
}
// -------------------------------------------------

// ----Set ANT------------------------------------
static void SetAnt()
{
	if ( Ant[SelAnt].RxAnt == Ant[SelAnt].TxAnt && Ant[SelAnt].RxAnt > 0 )
	{
		boxAColor[ Ant[SelAnt].RxAnt - 1 ] = boxAColorRxTx;
		SetAFlags( Ant[SelAnt].RxAnt );
	}
	else
	{
		if ( Ant[SelAnt].RxAnt > 0 )
		{		
			boxAColor[ Ant[SelAnt].RxAnt-1 ] = boxAColorRx;
			SetAFlags( Ant[SelAnt].RxAnt );
		}
		if ( Ant[SelAnt].TxAnt > 0 )
		{		
			boxAColor[ Ant[SelAnt].TxAnt-1 ] = boxAColorTx;
			SetAFlags( Ant[SelAnt].TxAnt );
		}
	}
}
// -------------------------------------------------

void SetAFlags( int ant )
{
	switch ( ant )
	{
		case 1:
		{
			aFlag.ant1 = 1;
			break;
		}
		case 2:
		{
			aFlag.ant2 = 1;
			break;
		}
		case 3:
		{
			aFlag.ant3 = 1;
			break;
		}
		case 4:
		{
			aFlag.ant4 = 1;
			break;
		}
		case 5:
		{
			aFlag.ant5 = 1;
			break;
		}
		case 6:
		{
			aFlag.ant6 = 1;
			break;
		}
		case 7:
		{
			aFlag.ant7 = 1;
			break;
		}
		case 8:
		{
			aFlag.ant8 = 1;
			break;
		}
		default:
		break;
	}
}

