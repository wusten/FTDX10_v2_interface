// -----SERIAL 1------------------------------------------
static const char terminator4 = ';';
static const int numChar4 = 128; // Size of Serial buffer
static char newChar4;
static int rcvidx4;
static char rcvdChar4[numChar4];

static const char terminator5 = ';';
static const int numChar5 = 128; // Size of Serial buffer
static char newChar5;
static int rcvidx5;
static char rcvdChar5[numChar5];

// Write to Yaesu port
static void WriteTxBuffer(int i)
{
	if ( dFlag.yaesuTx && Serial )
	{
		txBuf4[i] = '\0';
		serPrint( "Radio: Tx buffer", txBuf4, "bytes", i ); 
	}
	Serial4.write(txBuf4, i);
	elapsedMicros txRadio = 0;
	while ( txRadio < 100 ){}
}
//----------------------


// Write to Amp port
static void WriteTxBuffer5(int i)
{
	if ( dFlag.yaesuTx && Serial )
	{
		txBuf4[i] = '\0';
		serPrint( "Radio: Tx buffer", txBuf4, "bytes", i ); 
	}
	Serial5.write(txBuf4, i);
	elapsedMicros txRadio1 = 0;
//	while ( txRadio1 < 100 ){}
}
//----------------------


// Read from Yaesu port
static void ReadFromRadio()
{
	elapsedMillis serial4Time = 0;
	while ( serial4Time < Serial4Timeout && newData4 == false )
	{
		Process_serial4();
	}
  if ( dFlag.yaesuRx && Serial )
	{
		Serial.print( "Radio read time = " );
		Serial.print( serial4Time );
		Serial.println(" ms" );
	}
	if (newData4)
	{
		Process_rx_buffer4();
	}
	else
	{
		radioInitialized = false;
	}
}
//----------------------

//----UPDATE RADIO 0----
static void UpdateRadio0()
{
	if ( presetState[20] == 0 )
	{
		SetCwSpeed();
	}
	if ( presetState[20] == 1 )
	{
		SetProcLevel();
	}
	if ( presetState[20] == 2 )
	{
		SetMonLevel();
//		ReadMonLevel();	// added to avoid 064 reading from ML
	}
	if ( presetState[20] == 3 )
	{
		SetBrakeDelay();
	}
	if ( presetState[20] == 4 )
	{
		SetVoxDelay();
	}
}
//----------------------

//----UPDATE RADIO 1----
static void UpdateRadio1()
{
	if ( presetState[12] == 0 )
	{
		SetScopeLevel();
	}
	if ( presetState[12] == 1 )
	{
		SetScopeSpan();
	}
	if ( presetState[12] == 2 )
	{
		SetRfPower();
	}
}
//----------------------

// Check Radio for Change
static void CheckRadio()
{
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
	}
	if ( oldPresetState20 != presetState[20] )
	{
		oldPresetState20 = presetState[20];
		sFlag.enc0t = 1;
	}
	ReadCwSpeed();
	if ( cwSpeedChanged )
	{
		sFlag.s1cw = 1;
		if ( presetState[20] == 0 )
		{
			enc0 = cwSpeed;
			enc0Min = 4;
			enc0Max = 60;
			sFlag.enc0d = 1;
		}
		cwSpeedChanged = false;
	}
	if ( presetState[20] == 1 )
	{
		ReadProcLevel();
		if ( procLevelChanged )
		{
			enc0 = procLevel;
			enc0Min = 0;
			enc0Max = 100;
			encT.write( 4 * enc0 );
			procLevelChanged = false;
			sFlag.enc0d = 1;
		}
	}
	if ( presetState[20] == 2 )
	{
		ReadMonLevel();
		if ( monLevelChanged )
		{
			enc0 = monLevel;
			enc0Min = 0;
			enc0Max = 100;
			encT.write( 4 * enc0 );
			monLevelChanged = false;
			sFlag.enc0d = 1;
		}
	}
	if ( presetState[20] == 3 )
	{
		ReadBrakeDelay();
		if ( brakeDelayChanged )
		{
			enc0 = brakeDelay;
			enc0Min = 0;
			enc0Max = 33;
			encT.write( 4 * enc0 );
			brakeDelayChanged = false;
			sFlag.enc0d = 1;
		}
	}
	if ( presetState[20] == 4 )
	{
		ReadVoxDelay();
		if ( voxDelayChanged )
		{
			enc0 = voxDelay;
			enc0Min = 0;
			enc0Max = 33;
			encT.write( 4 * enc0 );
			voxDelayChanged = false;
			sFlag.enc0d = 1;
		}
	}
	if ( presetState[12] == 0 )
	{
		ReadScopeLevel();
		if ( scopeLevelChanged )
		{
			enc1 = scopeLevel / 5;
			enc1Min = -60;
			enc1Max = 60;
			encB.write( 4 * enc1 );
			scopeLevelChanged = false;
			sFlag.enc1d = 1;
		}
	}
	if ( presetState[12] == 1 )
	{
		ReadScopeSpan();
		if ( scopeSpanChanged )
		{
			enc1 = scopeSpan;
			enc1Min = 0;
			enc1Max = 9;
			encB.write( 4 * enc1 );
			scopeSpanChanged = false;
			sFlag.enc1d = 1;
		}
	}
	ReadRfPower();
	if ( rfPowerChanged )
	{
		sFlag.s1rf = 1;
		if ( presetState[12] == 2 )
		{
			enc1 = rfPower;
			enc1Min = 5;
			enc1Max = 100;
			encB.write( 4 * enc1 );
			sFlag.enc1d = 1;
		}
		rfPowerChanged = false;
	}
}
//----------------------

// Collect characters from the Serial4 (Radio) and check for a complete command
static void Process_serial4()
{
	while (Serial4.available() > 0 && newData4 == false)
	{
		newChar4 = Serial4.read();
		if ( newChar4 != terminator4 )
		{
			rcvdChar4[rcvidx4] = newChar4;
			rcvidx4++;
			if (rcvidx4 >= numChar4) 
			{
				rcvidx4 = numChar4 - 1;
			}
		}
		else 
		{
			rcvdChar4[rcvidx4] = terminator4; // terminate the string
			newData4 = true;
		}
	}
}
//----------------------

// Process a command sent/received from the Radio
static void Process_rx_buffer4()
{

  if ( dFlag.yaesuRx && Serial )
	{
		rcvdChar4[rcvidx4+1] = '\0';
		serPrint( "Radio: Rx buffer", rcvdChar4, "Idx", rcvidx4 ); 
	}
	bool good_command1 = true;
	switch (rcvdChar4[0])
	{
		case '?':	
		{
			if ( Serial )
			{
				Serial.print("Bad command sent to radio, ");
				Serial.println(txBuf4);
			}
			break;
		}
		case 'B':	
		{
			if (rcvdChar4[1] == 'I')
			{				
				if ( rcvidx4 == 3 && rcvdChar4[3] == terminator4 &&  isDigit(rcvdChar4[2]) )
				{
					int new_brakeIn = rcvdChar4[2] - '0';
					brakeInChanged = false;
					if ( new_brakeIn != brakeIn )
          {
 						brakeIn = new_brakeIn;
						brakeInChanged = true;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
      good_command1 = false;
			break;
		}
		case 'C':	
		{
			if (rcvdChar4[1] == 'O' && rcvdChar4[2] == '0' )
			{				
				if ( rcvidx4 == 8 && rcvdChar4[8] == terminator4 &&  rcvdChar4[3] == 2 )
				{
					int new_apf =  rcvdChar4[7]-'0';
					apfChanged = false;
					if ( new_apf != apf )
          {
						apf = new_apf;
						apfChanged = true;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
			good_command1 = false;
			break;
		}
		case 'F':	
		{
			if( rcvdChar4[1] == 'A' )	
			{
				if ( rcvidx4 == 11 && rcvdChar4[11] == terminator4 && isDigit(rcvdChar4[2]) && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) && isDigit(rcvdChar4[6]) && isDigit(rcvdChar4[7]) && isDigit(rcvdChar4[8]) && isDigit(rcvdChar4[9]) && isDigit(rcvdChar4[10]) )
				{
					for ( byte j=2; j<11; j++)
					{
						Fa[j-2] = rcvdChar4[j];
					}
					int MHz = ( rcvdChar4[3] - '0' ) * 10 + rcvdChar4[4] - '0' ;
					int newBand = 0;
					if (MHz == 1) {newBand = 0;}
					if (MHz == 3) {newBand = 1;}
					if (MHz == 7) {newBand = 2;}
					if (MHz == 14) {newBand = 3;}
					if (MHz == 21) {newBand = 4;}
					if (MHz == 28) {newBand = 5;}
					if (MHz == 50) {newBand = 6;}
					bandChanged = false;
					if ( newBand != band)
					{
						band = newBand;
						bandChanged = true;
					}
					break;
				}
        good_command1 = false;
			  break;
			}	
			good_command1 = false;
			break;
		}
		case 'K':	
		{
			if (rcvdChar4[1] == 'S')
			{				
				if ( rcvidx4 == 5 && rcvdChar4[5] == terminator4 &&  rcvdChar4[2] == '0' && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) )
				{
					int new_cwSpeed = ( rcvdChar4[3] - '0' ) * 10 + rcvdChar4[4] - '0';
          cwSpeedChanged = false;
					if ( new_cwSpeed != cwSpeed )
          {
						cwSpeed = new_cwSpeed;
						cwSpeedChanged = true;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
			good_command1 = false;
			break;
		}
		case 'M':	
		{
			if ( rcvdChar4[1] == 'D')
			{
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 && rcvdChar4[2] == '0' && ( isDigit(rcvdChar4[3]) || rcvdChar4[3] == 'A' || rcvdChar4[3] == 'B' || rcvdChar4[3] == 'C' || rcvdChar4[3] == 'D' || rcvdChar4[3] == 'E' || rcvdChar4[3] == 'F' ) )
				{
					char new_mode = rcvdChar4[3];
          modeValChanged = false;
					if ( new_mode != modeVal )
          {
						modeVal = new_mode;
						modeValChanged = true;
					}
					break;
				}
        good_command1 = false;
			  break;
			}
			if ( rcvdChar4[1] == 'L')
			{
				if ( rcvidx4 == 6 && rcvdChar4[6] == terminator4 && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) )
				{
					int new_monLevel = ( rcvdChar4[3] - '0' ) * 100 + ( rcvdChar4[4] - '0' ) * 10 + rcvdChar4[5] - '0';
					monLevelChanged = false;
					if ( new_monLevel != monLevel )
          {
						monLevel = new_monLevel;
						monLevelChanged = true;
          }
          break;
				}
        good_command1 = false;
			  break;
			}
			good_command1 = false;
			break;
		}
		case 'P':	
		{
			if ( rcvdChar4[1] == 'A' && rcvdChar4[2] == '0' )
			{
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 && isDigit(rcvdChar4[3]) )
				{
					int new_ipo = ( rcvdChar4[3] - '0' );
					ipoChanged = false;
					if ( new_ipo != ipo )
					{
						ipo = new_ipo;
						ipoChanged = true;
					}
          break;
				}
				good_command1 = false;
				break;        
      }    
			if ( rcvdChar4[1] == 'C')
			{
				if ( rcvidx4 == 5 && rcvdChar4[5] == terminator4 && isDigit(rcvdChar4[2]) && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) )
				{
					int new_rfPower = ( rcvdChar4[2] - '0' ) * 100 + ( rcvdChar4[3] - '0' ) * 10 + rcvdChar4[4] - '0';
					rfPowerChanged = false;
					if ( new_rfPower != rfPower )
          {
						rfPower = new_rfPower;
						rfPowerChanged = true;
          }
					break;
				}
				good_command1 = false;
				break;
			}
			if ( rcvdChar4[1] == 'L' )
			{
				if ( rcvidx4 == 5 && rcvdChar4[5] == terminator4 && isDigit(rcvdChar4[2]) && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) )
				{
					int new_procLevel = ( rcvdChar4[2] - '0' ) * 100 + ( rcvdChar4[3] - '0' ) * 10 + rcvdChar4[4] - '0';
					procLevelChanged = false;
					if ( new_procLevel != procLevel )
          {
						procLevel = new_procLevel;
						procLevelChanged = true;
          }
					break;
				}
				good_command1 = false;
				break;
			}
			good_command1 = false;
			break;
		}
   	case 'R':	
		{
			if ( rcvdChar4[1] == 'A' && rcvdChar4[2] == '0' )
			{
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 && isDigit(rcvdChar4[3]) )
				{
					int new_att = ( rcvdChar4[3] - '0' );
					attChanged = false;
					if ( new_att != att )
					{
						att = new_att;
						attChanged = true;
					}
          break;
				}
				good_command1 = false;
				break;        
      }        
			if ( rcvdChar4[1] == 'F' && rcvdChar4[2] == '0' )
			{
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 )
				{
	  			int new_rFilter = 0;
					if ( rcvdChar4[3] >= '0' && rcvdChar4[3] <= '9' )
					{
						new_rFilter = ( rcvdChar4[3] - '0' ) - 5 ;
					}
					
					if ( rcvdChar4[3] == 'A' )
					{
						 new_rFilter = 5;
					}
					rFilterChanged = false;
					if ( new_rFilter != rFilter )
					{
						rFilter = new_rFilter;
						rFilterChanged = true;
					}
          break;
				}
				good_command1 = false;
				break;        
      }        
			if ( rcvdChar4[1] == 'M' && rcvdChar4[2] == '5' )
			{
				if ( rcvidx4 == 9 && rcvdChar4[9] == terminator4 && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) 
        && rcvdChar4[6] == '0' && rcvdChar4[7] == '0' && rcvdChar4[8] == '0' )
				{
					int newPower = int( pwrScale * ( ( rcvdChar4[3] - '0' ) * 100 + ( rcvdChar4[4] - '0' ) * 10 + rcvdChar4[5] - '0' ) );
					powerChanged = false;
					if ( newPower != power )
					{
						power = newPower;
						powerChanged = true;
					}
          break;
				}
				good_command1 = false;
				break;        
      }        
	    if ( rcvdChar4[1] == 'M' && rcvdChar4[2] == '6' )
			{
				if ( rcvidx4 == 9 && rcvdChar4[9] == terminator4 && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) 
        && rcvdChar4[6] == '0' && rcvdChar4[7] == '0' && rcvdChar4[8] == '0' )
				{
					int newSwr = int( swrScale * ( ( rcvdChar4[3] - '0' ) * 100 + ( rcvdChar4[4] - '0' ) * 10 + rcvdChar4[5] - '0' ));
					swrChanged = false;
					if ( newSwr != swr )
					{
						swr = newSwr;
						swrChanged = true;
					}
					break;
				}
				good_command1 = false;
				break;
			}
	    if ( rcvdChar4[1] == 'M' && rcvdChar4[2] == '7' )
			{
				if ( rcvidx4 == 9 && rcvdChar4[9] == terminator4 && isDigit(rcvdChar4[3]) && isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) 
        && rcvdChar4[6] == '0' && rcvdChar4[7] == '0' && rcvdChar4[8] == '0' )
				{
					int newIdd = int( iddScale * ( ( rcvdChar4[3] - '0' ) * 100 + ( rcvdChar4[4] - '0' ) * 10 + rcvdChar4[5] - '0' ) );
					iddChanged = false;
					if ( newIdd != idd )
					{
						idd = newIdd;
						iddChanged = true;
					}
					break;
				}
				good_command1 = false;
				break;
			}
			good_command1 = false;
			break;
		} 
		case 'S':	
		{
			if (rcvdChar4[1] == 'D')
			{				
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 &&  isDigit(rcvdChar4[2]) && isDigit(rcvdChar4[3]) )
				{
					int new_brakeDelay = ( rcvdChar4[2] - '0' ) * 10 + rcvdChar4[3] - '0';
          brakeDelayChanged = false;
					if ( new_brakeDelay != brakeDelay )
          {
						brakeDelay = new_brakeDelay;
						brakeDelayChanged = true;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
			if (rcvdChar4[1] == 'H' && rcvdChar4[2] == '0' && rcvdChar4[3] == '0')
			{				
				if ( rcvidx4 == 6 && rcvdChar4[6] == terminator4 &&  isDigit(rcvdChar4[4]) && isDigit(rcvdChar4[5]) )
				{
					int new_width = ( rcvdChar4[4] - '0' ) * 10 + rcvdChar4[5] - '0';
          widthChanged = false;
					if ( new_width != width )
          {
						width = new_width;
						widthChanged = true;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
			if ( rcvdChar4[1] == 'S' && rcvdChar4[2] == '0' && rcvdChar4[3] == '4' )
			{
				if ( rcvidx4 == 9 && rcvdChar4[9] == terminator4 &&  isDigit(rcvdChar4[5]) && isDigit(rcvdChar4[6]) && rcvdChar4[7] == '.' && isDigit(rcvdChar4[8]) )
				{
          if ( rcvdChar4[4] == '-' )
          {
            int new_scope_level = -( rcvdChar4[5] - '0' ) * 100 - ( rcvdChar4[6] - '0' ) * 10 - ( rcvdChar4[8] - '0');
					  scopeLevelChanged = false;
						if ( new_scope_level != scopeLevel )
            {
 							scopeLevel = new_scope_level;
							scopeLevelChanged = true;
						}
            break; 
          }
          if ( rcvdChar4[4] == '+' )
          {
            int new_scope_level = ( rcvdChar4[5] - '0' ) * 100 + ( rcvdChar4[6] - '0' ) * 10 + ( rcvdChar4[8] - '0' );
						scopeLevelChanged = false;
					  if ( new_scope_level != scopeLevel )
            {
							scopeLevel = new_scope_level;
							scopeLevelChanged = true;
            }
            break;
          }
          good_command1 = false;
			    break;
				}
        good_command1 = false;
			  break;
			}
			if ( rcvdChar4[1] == 'S' && rcvdChar4[2] == '0' && rcvdChar4[3] == '5' )
			{
				if ( rcvidx4 == 9  && rcvdChar4[9] == terminator4 && isDigit( rcvdChar4[4] ) && rcvdChar4[5] == '0' && rcvdChar4[6] == '0' && rcvdChar4[7] == '0' && rcvdChar4[8] == '0' )
				{
					int new_scopeSpan = rcvdChar4[4] - '0';
					scopeSpanChanged = false;
          if ( new_scopeSpan != scopeSpan )
          {
						scopeSpan = new_scopeSpan;
						scopeSpanChanged = true;
          }
					break;
				}
			  good_command1 = false;
			  break;
			}
			good_command1 = false;
			break;
		}		
		case 'V':	
		{
			if (rcvdChar4[1] == 'D')
			{				
				if ( rcvidx4 == 4 && rcvdChar4[4] == terminator4 &&  isDigit(rcvdChar4[2]) && isDigit(rcvdChar4[3]) )
				{
					int new_voxDelay = ( rcvdChar4[2] - '0' ) * 10 + rcvdChar4[3] - '0';
          voxDelayChanged = false;
					if ( new_voxDelay != voxDelay )
          {
						voxDelay = new_voxDelay;
						voxDelayChanged = false;
          }
        	break;
				}
        good_command1 = false;
			  break;
			}	
			good_command1 = false;
			break;
		}
		default:
		good_command1 = false;
		break;		
	}  
	if (!good_command1)
	{
		txBuf4[10] = '\0';
		rcvdChar4[rcvidx4+1] = '\0';
		serPrint( "Bad command, rcvd at Ser4-", rcvdChar4, "Idx-", rcvidx4 ); 
	}
	newData4 = false;
	rcvidx4 = 0;  
}

void CheckAmp()
{
	while (Serial5.available() > 0 && newData5 == false)
	{
		newChar5 = Serial5.read();
		if ( newChar5 != terminator5 )
		{
			rcvdChar5[rcvidx5] = newChar5;
			rcvidx5++;
			if (rcvidx5 >= numChar5) 
			{
				rcvidx5 = numChar5 - 1;
			}
		}
		else 
		{
			rcvdChar5[rcvidx5] = terminator5; // terminate the string
			newData5 = true;
		}
	}	
	if ( newData5 )
	{
/*
		txBuf4[0] = 'F';
		txBuf4[1] = 'A';
		for ( byte i=0; i <9; i++ )
		{
			txBuf4[i+2] = Fa[i];
		}
		txBuf4[11] = ';';
		WriteTxBuffer5(12);
*/
		for ( byte i=0; i <= rcvidx5; i++ )
		{
			txBuf4[i] = rcvdChar5[i];
		}
		WriteTxBuffer(rcvidx5+1);
    newData5 = false;
    rcvidx5 = 0;
  }  
	Process_serial4();
  if ( newData4 )
  {
    for ( byte i=0; i <= rcvidx4; i++ )
    {
      txBuf4[i] = rcvdChar4[i];
    }			
    WriteTxBuffer5(rcvidx4+1);
    newData4 = false;
    rcvidx4 = 0;
  }
}
