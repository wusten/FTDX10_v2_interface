// -----SERIAL--------------------------------------------
static const char endMarker = '\n';
static const char terminator = '\0';
static const int numChar = 128; // Size of Serial buffer
static char newChar;
static int rcvidx;
static char rcvdChar[numChar];


// Collect characters from the Serial (PC) and check for a complete command
static void Process_serial()
{
	while (Serial.available() > 0 && newData == false)
	{
		newChar = Serial.read();
		if ( newChar != endMarker )
		{
			rcvdChar[rcvidx] = newChar;
			rcvidx++;
			if (rcvidx >= numChar) 
			{
				rcvidx = numChar - 1;
			}
		}
		else 
		{
			rcvdChar[rcvidx] = terminator; // terminate the string
			newData = true;
		}
	}
	if (newData)
	{
		Process_rx_buffer();
	}
}
//----------------------

// Process a command sent/received from the PC
static void Process_rx_buffer()
{
	if ( dFlag.pcRx && Serial )
	{		
		serPrint( "Serial: Rx buffer", rcvdChar, "Idx", rcvidx ); 
	}
	bool good_command = true;
	switch (rcvdChar[0])
	{
		// Antenna setup
    case 'A':
		case 'a':
		{
			// Rx Ant AnRk  (n-selAnt 1-8 , k Ant 0-8 ) 
			if ( isDigit(rcvdChar[1]) && ( rcvdChar[2] == 'r' || rcvdChar[2] == 'R' ) && isDigit(rcvdChar[3]) &&
						rcvidx == 4 && rcvdChar[4] == terminator ) 
			{
				byte sel = rcvdChar[1] - '0' ;
				byte val = rcvdChar[3] - '0';
				if ( sel > 0 && sel < 9 && val < 9 )
				{
					Ant[sel-1].RxAnt = val;
					UpdateEepromRxAnt(sel-1);
					break;
				}
				good_command = false;
				break;				
			}
			// Tx Ant AnTk  (n-selAnt 1-8, k Ant 0-8) 
			if ( isDigit(rcvdChar[1]) && (rcvdChar[2] == 't' || rcvdChar[2] =='T' ) && isDigit(rcvdChar[3]) &&
						rcvidx == 4 && rcvdChar[4] == terminator ) 
			{
				byte sel = rcvdChar[1] - '0';
				byte val = rcvdChar[3] - '0';
				if ( sel > 0 && sel < 9 && val < 9 )
				{
					Ant[sel-1].TxAnt = val;
					UpdateEepromTxAnt(sel-1);
					break;
				}
				good_command = false;
				break;				
			}
			// Ant Outs  AnOkm  (n-Ant 0-8 , k out 1-8, m 0 or 1) 
			if ( isDigit(rcvdChar[1]) && ( rcvdChar[2] == 'o' || rcvdChar[2] == 'O' ) &&
					isDigit(rcvdChar[3]) && ( rcvdChar[4] == '0' || rcvdChar[4] == '1' ) &&
					rcvidx == 5 && rcvdChar[5] == terminator ) 
			{
				byte sel = rcvdChar[1] - '0';
				byte out = rcvdChar[3] - '0';
				byte val = rcvdChar[4] - '0';
				if ( sel > 0 && sel < 9 && out > 0 && out < 9 )
				{
					if ( val == 0 )
					{
						bitClear( Ant[sel-1].Out, out-1 );
					}
					else
					{
						bitSet( Ant[sel-1].Out, out-1 );
					}
					UpdateEepromOut(sel-1);
					break;
				}
				good_command = false;
				break;				
			}
			// Ant TxBand  AnBkm  (n-Ant 0-8 , k band 1-7, m 0 or 1) 
			if ( isDigit(rcvdChar[1]) && ( rcvdChar[2] == 'B' ||rcvdChar[2] == 'b' ) &&
					isDigit(rcvdChar[3]) && ( rcvdChar[4] == '0' || rcvdChar[4] == '1' ) &&
					rcvidx == 5 && rcvdChar[5] == terminator ) 
			{
				byte sel = rcvdChar[1] - '0';
				byte band = rcvdChar[3] - '0';
				byte val = rcvdChar[4] - '0';
				if ( sel > 0 && sel < 9 && band > 0 && band < 9 )
				{
					if ( val == 0 )
					{
						bitClear ( Ant[sel-1].TxBand, band-1 );						
					}
					else
					{
						bitSet( Ant[sel-1].TxBand, band-1 );
					}
					UpdateEepromTxBand(sel-1);
					break;
				}
				good_command = false;
				break;				
			}
			// Ant Name  AnNssssss  (n-Ant 0-8 , s-name  up to 6 char) 

			if ( isDigit(rcvdChar[1]) && ( rcvdChar[2] == 'N' ||rcvdChar[2] == 'n' ) &&
					rcvidx > 3 && rcvidx < 10 && rcvdChar[rcvidx] == terminator ) 
			{
				byte sel = rcvdChar[1] - '0';
				byte len = rcvidx - 3;
				String val = "";
				for( int j=0; j< len; j++ )
				{
					val.concat(rcvdChar[3+j]);
				}
				Ant[sel-1].name = val;
				UpdateEepromName(sel-1);
				break;
			}
			if ( ( rcvdChar[1] == 'D' ||rcvdChar[1] == 'd' ) &&
					 rcvdChar[2] == terminator ) 
			{
				InitEepromToDefaults();
				break;
			}
			good_command = false;
			break;				
  	}
		// Send command to radio
    case 'Y':	
		case 'y':
		{
			for ( byte i = 0; i < rcvidx; i++ )
			{
				txBuf4[i] = rcvdChar[i+1];
			}
			WriteTxBuffer(rcvidx-1);
			rcvidx = 0; 
			ReadFromRadio();
			break;
  	}
		// Set/reset Ptt
    case 'P':	
		case 'p':
		{
			if ( pttNew )
			{
				pttNew = 0;
			}
			else
			{
				pttNew = 1;
			}
			break;
  	}
	  // Read EEPROM 
		case 'E':	
		case 'e':	
		{
			if ( rcvidx == 1 && rcvdChar[1] == terminator ) //Read Band + 1 for RX/TX
			{
				Serial.print("EEPROM Check = ");	
				Serial.println( EEPROM.read( 0 ) );	
				Serial.println("SelAnt RxAnt TxAnt   Ant     Out        TxBand   Name");	
				char nam[7];
				for ( byte i = 0; i < 8 ; i++ )
				{
					Serial.print(" ");
					Serial.print(i+1);
					Serial.print("      ");
					Serial.print(EEPROM.read( 20*i +1));
					Serial.print("     ");
					Serial.print(EEPROM.read( 20*i+2));
					Serial.print("       ");
					Serial.print(i+1);
					Serial.print("     ");
					printBin(EEPROM.read( 20*i+3));
					Serial.print("   ");
					printBin(EEPROM.read( 20*i+4));
					Serial.print("  ");
					EEPROM.get(20*i+5, nam);
					Serial.println(nam);
				}
				break;
			}
			if ( rcvidx == 3 && rcvdChar[3] == terminator ) // Write 0xFF at addr location 
			{
				int addr = ( rcvdChar[1] - '0' ) * 10 + rcvdChar[2] - '0';
				EEPROM.write( addr, 0xFF );
				break;
			}
			if ( rcvidx == 4 && rcvdChar[4] == terminator ) // vrite val at addr
			{
				int addr = ( rcvdChar[1] - '0' ) * 10 + rcvdChar[2] - '0';
				int val = rcvdChar[3];
        EEPROM.write( addr, val );
				break;
			}			
			if ( rcvidx == 2 && ( rcvdChar[1] == 'f' || rcvdChar[1] == 'F' ) && rcvdChar[2] == terminator ) //clear EEPROM
			{
				for ( int i = 0 ; i < 201 ; i++ )
				{
					EEPROM.update(i, 0xFF);
				}
				break;
			}			
			good_command = false;
			break;
		}
		// Set/reset Out
    case 'O':	
		case 'o':
		{
			int ou = rcvdChar[1]-'0';
			if ( digitalRead(outPin[ou]) == 0 )
			{
				digitalWrite(outPin[ou], 1);
			}
			if ( digitalRead(outPin[ou]) == 1 )
			{
				digitalWrite(outPin[ou], 0);
			}
			rcvidx = 0; 
			break;
  	}		
		
    // Print Version
		case 'V':
		case 'v':	
		{
			if ( rcvidx == 1 && rcvdChar[1] == terminator )
			{
				Serial.print("*** Software version: ");
				Serial.print(Version);
				Serial.println("   ***");
				break;
			}
			good_command = false;
			break;
		}
		default:
		good_command = false;
		break;		
	}  
	if (!good_command)
	{
		Serial.println ("Bad command");
	}
	newData = false;
	rcvidx = 0;  
}
//----------------------
