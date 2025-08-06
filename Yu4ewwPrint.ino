//----SER PRINT--------
void serPrint( const char *txt1, const char *data1, const char *txt2, int data2 ) 
{
	sprintf ( buffer, "%s = %s , %s = %d", txt1, data1, txt2, data2 );
	Serial.println( buffer );
}
void serPrint( const char *txt1, const char *data1, const char *txt2, const char *data2, const char *txt3, int data3 )
{
	sprintf ( buffer, "%s %s %s %s %s %d", txt1, data1, txt2, data2, txt3, data3 );
	Serial.println( buffer );
}

void printBin(byte aByte)
{
  for (int8_t aBit = 7; aBit >= 0; aBit--)
    Serial.write(bitRead(aByte, aBit) ? '1' : '0');
}

