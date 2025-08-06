// ----Init EEPROM----------------------------------
static void InitEeprom()
{	
	if (EEPROM.read( 0 ) == 0xFF )
	{
		if ( dFlag.eeprom && Serial )
		{
			Serial.println("Eeprom not initialized, init to defaults");
		}
		InitEepromToDefaults();
	} 
	else
	{
		if ( dFlag.eeprom && Serial )
		{
			Serial.println("Eeprom initialized, init from Eeprom ");
		}
			InitFromEeprom();
	}
}
// -------------------------------------------------

// ----Init EEPROM TO DEFAULTS----------------------------------
void InitEepromToDefaults()
{
	InitAntennas();
	EEPROM.update( eepromStart, 0 );	
	int j = eepromStart;
	for ( int i = 0; i<Antennas; i++ )
	{
		EEPROM.update( j+1, Ant[i].RxAnt );
		EEPROM.update( j+2, Ant[i].TxAnt );
		EEPROM.update( j+3, Ant[i].Out );
		EEPROM.update( j+4, Ant[i].TxBand );
		EEPROM.put( j+5, Ant[i].name );
		j= j+20;
	}
}
// -------------------------------------------------

// ----Init FROM EEPROM----------------------------------
void InitFromEeprom()
{
	int j = eepromStart;
	for ( int i = 0; i<Antennas; i++ )
	{
		Ant[i].RxAnt = EEPROM.read(j+1);
		Ant[i].TxAnt = EEPROM.read(j+2);
		Ant[i].Out = EEPROM.read(j+3);
		Ant[i].TxBand = EEPROM.read(j+4);
		EEPROM.get( j+5, Ant[i].name );
		j= j+20;
	}
}
// -------------------------------------------------

// ----Update EEPROM RX ANT-----------------------------
static void UpdateEepromRxAnt(int sel)
{	
	EEPROM.update( eepromStart + 20 * sel + 1, Ant[sel].RxAnt );
}
// -------------------------------------------------

// ----Update EEPROM TX ANT-----------------------------
static void UpdateEepromTxAnt(int sel)
{	
	EEPROM.update( eepromStart + 20 * sel + 2, Ant[sel].TxAnt );
}
// -------------------------------------------------

// ----Update EEPROM OUT-----------------------------
static void UpdateEepromOut(int sel)
{	
	EEPROM.update( eepromStart + 20 * sel + 3, Ant[sel].Out );
}
// -------------------------------------------------

// ----Update EEPROM TX BAND-----------------------------
static void UpdateEepromTxBand(int sel)
{	
	EEPROM.update( eepromStart + 20 * sel + 4, Ant[sel].TxBand );
}
// -------------------------------------------------

// ----Update EEPROM ANT NAME-----------------------------
static void UpdateEepromName(int sel)
{	
	EEPROM.put( eepromStart + 20 * sel + 5, Ant[sel].name );
}
// -------------------------------------------------
