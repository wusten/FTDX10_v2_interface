//----Read Band---------
static int ReadBand()
{
	txBuf4[0]= 'F';
	txBuf4[1]= 'A';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return band;
}
//----Read mode---------
static char ReadMode()
{
	txBuf4[0]= 'M';
	txBuf4[1]= 'D';
	txBuf4[2]= '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return modeVal;
}
//----Read RF Power-----
static int ReadRfPower()
{
	txBuf4[0]= 'P';
	txBuf4[1]= 'C';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return rfPower;
}
//----Read Cw speed-----
static int ReadCwSpeed()
{
	txBuf4[0]= 'K';
	txBuf4[1]= 'S';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return cwSpeed;
}
//----Read Brake Delay-----
static int ReadBrakeDelay()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'D';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return brakeDelay;
}
//----Read Brake-In------
static int ReadBrakeIn()
{
	txBuf4[0]= 'B';
	txBuf4[1]= 'I';
	txBuf4[2]= ';';
	WriteTxBuffer(3);	
	ReadFromRadio();
	return brakeIn;
}
//----Read Procesor Level
static int ReadProcLevel()
{
	txBuf4[0]= 'P';
	txBuf4[1]= 'L';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return procLevel;
}
//----Read Vox Delay-----
static int ReadVoxDelay()
{
	txBuf4[0]= 'V';
	txBuf4[1]= 'D';
	txBuf4[2]= ';';
	WriteTxBuffer(3);
	ReadFromRadio();
	return voxDelay;
}
//----Read Monitor Level
static int ReadMonLevel()
{
	txBuf4[0]= 'M';
	txBuf4[1]= 'L';
	txBuf4[2]= '1';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return monLevel;
}
//----Read Scope Level--
static int ReadScopeLevel()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'S';
	txBuf4[2]= '0';
	txBuf4[3]= '4';
	txBuf4[4]= ';';
	WriteTxBuffer(5);
	ReadFromRadio();
	return scopeLevel;
}
//----Read Scope Span---
static int ReadScopeSpan()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'S';
	txBuf4[2]= '0';
	txBuf4[3]= '5';
	txBuf4[4]= ';';
	WriteTxBuffer(5);
	ReadFromRadio();
	return scopeSpan;
}
//----Read APF----------
static int __attribute__((unused)) ReadApf()
{
	txBuf4[0]= 'C';
	txBuf4[1]= 'O';
	txBuf4[2]= '0';
	txBuf4[3]= '2';
	txBuf4[4]= ';';
	WriteTxBuffer(5);
	ReadFromRadio();
	return apf;
}
//----Read IPO----------
static int ReadIpo()
{
	txBuf4[0]= 'P';
	txBuf4[1]= 'A';
	txBuf4[2]= '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return ipo;
}
//----Read ATT----------
static int ReadAtt()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'A';
	txBuf4[2]= '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return att;
}
//----Read ROOFING------
static int ReadRFilter()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'F';
	txBuf4[2]= '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return rFilter;
}
//----Read Width------------
static int __attribute__((unused)) ReadWidth()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'H';
	txBuf4[2]= '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);
	ReadFromRadio();
	return width;
}
//----Read Tx Power-----
static int ReadPower()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'M';
	txBuf4[2]= '5';
	txBuf4[3]= ';';  
	WriteTxBuffer(4);
	ReadFromRadio();
	return power;
 }
//----Read SWR----------
static int ReadSwr()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'M';
	txBuf4[2]= '6';
  txBuf4[3]= ';'; 
	WriteTxBuffer(4);
	ReadFromRadio();
	return swr;
}
//----Read IDD----------
static int ReadIdd()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'M';
	txBuf4[2]= '7';
  txBuf4[3]= ';'; 
	WriteTxBuffer(4);
	ReadFromRadio();
	return idd;
}

//----Set Band----------
static void SetBand()
{
	txBuf4[0]= 'B';
	txBuf4[1]= 'S';
	if ( band == 0 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '0';
	}
	if ( band == 1 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '1';
	}
	if ( band == 2 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '3';
	}
	if ( band == 3 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '5';
	}
	if ( band == 4 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '7';
	}
	if ( band == 5 )
	{
		txBuf4[2]= '0';
		txBuf4[3]= '9';
	}
	if ( band == 6 )
	{
		txBuf4[2]= '1';
		txBuf4[3]= '0';
	}
	txBuf4[4]= ';';
	WriteTxBuffer(5);
}
//----Set mode----------
static void SetMode()
{
	txBuf4[0]= 'M';
	txBuf4[1]= 'D';
	txBuf4[2]= '0';
	txBuf4[3]= modeVal;
	txBuf4[4]= ';';
	WriteTxBuffer(5);
}
//----Set RF Power------
static void SetRfPower()
{
	txBuf4[0]= 'P';
	txBuf4[1]= 'C';
	txBuf4[2]= rfPower / 100 + '0';
	txBuf4[3]= ( rfPower - ( rfPower / 100 ) * 100 ) / 10 + '0';
	txBuf4[4]= rfPower - ( rfPower / 10 ) * 10 + '0';
	txBuf4[5]= ';';
	WriteTxBuffer(6);
}
//----Set Cw Speed------
static void SetCwSpeed()
{
	txBuf4[0]= 'K';
	txBuf4[1]= 'S';
	txBuf4[2]= '0';
	txBuf4[3]= cwSpeed / 10 + '0';
	txBuf4[4]= cwSpeed - ( cwSpeed / 10 ) * 10  + '0';
	txBuf4[5]= ';';
	WriteTxBuffer(6);	
}
//----Set Brake Delay------
static void SetBrakeDelay()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'D';
	txBuf4[2]= brakeDelay/10 + '0';
	txBuf4[3]= brakeDelay - (brakeDelay/10)*10 + '0';
	txBuf4[4]= ';';
	WriteTxBuffer(5);	
}
//----Set Brake-In------
static void SetBrakeIn()
{
	txBuf4[0]= 'B';
	txBuf4[1]= 'I';
	txBuf4[2]= brakeIn + '0';
	txBuf4[3]= ';';
	WriteTxBuffer(4);	
}
//----Set Procesor Level
static void SetProcLevel()
{
	if ( procLevel == 0 )
	{
		txBuf4[0]= 'P';
		txBuf4[1]= 'R';
		txBuf4[2]= '0';
		txBuf4[3]= '1';
		txBuf4[4]= ';';
		WriteTxBuffer(5);		
	}
	else
	{
		txBuf4[0]= 'P';
		txBuf4[1]= 'L';
		txBuf4[2]= procLevel / 100 + '0';
		txBuf4[3]= ( procLevel - ( procLevel / 100 ) * 100 ) / 10 + '0';
		txBuf4[4]= procLevel - ( procLevel / 10 ) * 10 + '0';
		txBuf4[5]= ';';
		WriteTxBuffer(6);
	}
	ReadFromRadio();
}
//----Set Vox Delay------
static void SetVoxDelay()
{
	txBuf4[0]= 'V';
	txBuf4[1]= 'D';
	txBuf4[2]= voxDelay/10 + '0';
	txBuf4[3]= voxDelay - (voxDelay/10)*10 + '0';
	txBuf4[4]= ';';
	WriteTxBuffer(5);	
}
//----Set Monitor Level-
static void SetMonLevel()
{
	txBuf4[0]= 'M';
	txBuf4[1]= 'L';
	txBuf4[2]= '1';
	txBuf4[3]=  monLevel / 100 + '0';
	txBuf4[4]= ( monLevel - ( monLevel / 100 ) * 100 ) / 10 + '0';
	txBuf4[5]= monLevel - ( monLevel / 10 ) * 10 + '0';
	txBuf4[6]= ';';
	WriteTxBuffer(7);
}
//----Set Scope Level---
static void SetScopeLevel()
{
  txBuf4[0]= 'S';
	txBuf4[1]= 'S';
	txBuf4[2]= '0';
	txBuf4[3]= '4';
	if ( scopeLevel < 0 )
	{
		txBuf4[4]= '-';
		txBuf4[5]=  -scopeLevel / 100 + '0';
		txBuf4[6]=  ( -scopeLevel + ( scopeLevel / 100 ) * 100 ) / 2 + '0' ;
		txBuf4[7]= '.';
		txBuf4[8]= ( -scopeLevel + ( scopeLevel / 10 ) * 10 ) + '0';
	} 
	else
	{
		txBuf4[4]= '+';
		txBuf4[5]= scopeLevel / 100 + '0';
		txBuf4[6]= ( scopeLevel - ( scopeLevel / 100 ) * 100 ) / 10 + '0';
		txBuf4[7]= '.';
		txBuf4[8]= ( scopeLevel - ( scopeLevel / 10 ) * 10 ) + '0';
	}
	txBuf4[9]= ';';
	WriteTxBuffer(10);
}
//----Set Scope Span----
static void SetScopeSpan()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'S';
	txBuf4[2]= '0';
	txBuf4[3]= '5';
	txBuf4[4]= scopeSpan + '0';
	txBuf4[5]= '0';
	txBuf4[6]= '0';
	txBuf4[7]= '0';
	txBuf4[8]= '0';
	txBuf4[9]= ';';
	WriteTxBuffer(10);
}
//----Set APF ON--------
static void SetApf()
{
	txBuf4[0]= 'C';
	txBuf4[1]= 'O';
	txBuf4[2]= '0';
	txBuf4[3]= '2';
	txBuf4[4]= '0';
	txBuf4[5]= '0';
	txBuf4[6]= '0';
	txBuf4[7]= apf + '0';
	txBuf4[8]= ';';		
	WriteTxBuffer(9);	
}
//----Set IPO-----------
static void SetIpo()
{
	txBuf4[0]= 'P';
	txBuf4[1]= 'A';
	txBuf4[2]= '0';
	txBuf4[3]= ipo + '0';
	txBuf4[4]= ';';
	WriteTxBuffer(5);	
}
//----Set ATT-----------
static void SetAtt()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'A';
	txBuf4[2]= '0';
	txBuf4[3]= att + '0';
	txBuf4[4]= ';';
	WriteTxBuffer(5);	
}
//----Set ROOFING-----------
static void SetRFilter()
{
	txBuf4[0]= 'R';
	txBuf4[1]= 'F';
	txBuf4[2]= '0';
	txBuf4[3]= rFilter + '0';
	txBuf4[4]= ';';
	WriteTxBuffer(5);	
}
//----Set Width-------------
static void SetWidth()
{
	txBuf4[0]= 'S';
	txBuf4[1]= 'H';
	txBuf4[2]= '0';
	txBuf4[3]= '0';
	txBuf4[4]= width / 10 + '0';
	txBuf4[5]= width - 10 * ( width / 10 ) + '0';
	txBuf4[6]= ';';
	WriteTxBuffer(7);	
}


