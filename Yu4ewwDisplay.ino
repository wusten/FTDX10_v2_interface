
// name[6] = {x, y, w, h , xc, yc };	// X-start, Y-start, X-width, Y-hight, XC-x center, YC-Y center
static int boxA1[6] = { x0+1, y0+1, x1-x0-2, y1-y0-2, (x1+x0)/2, (y1+y0)/2 };
static int boxA2[6] = { x1+1, y0+1, x2-x1-2, y1-y0-2, (x2+x1)/2, (y1+y0)/2 };
static int boxA3[6] = { x2+1, y0+1, x3-x2-2, y1-y0-2, (x3+x2)/2, (y1+y0)/2 };
static int boxA4[6] = { x3+1, y0+1, x4-x3-2, y1-y0-2, (x4+x3)/2, (y1+y0)/2 };
static int boxA5[6] = { x0+1, y5+1, x1-x0-2, y6-y5-2, (x1+x0)/2, (y6+y5)/2 };
static int boxA6[6] = { x1+1, y5+1, x2-x1-2, y6-y5-2, (x2+x1)/2, (y6+y5)/2 };
static int boxA7[6] = { x2+1, y5+1, x3-x2-2, y6-y5-2, (x3+x2)/2, (y6+y5)/2 };
static int boxA8[6] = { x3+1, y5+1, x4-x3-2, y6-y5-2, (x4+x3)/2, (y6+y5)/2 };
static int boxS1[6] = { x0+1, y1+1, x5-x0-2, y2-y1-2, (x5+x0)/2, (y2+y1)/2 };
static int boxS2[6] = { x0+1, y2+1, x5-x0-2, y3-y2-2, (x5+x0)/2, (y3+y2)/2 };
static int boxS3[6] = { x0+1, y3+1, x5-x0-2, y4-y3-2, (x5+x0)/2, (y4+y3)/2 };
static int boxS4[6] = { x0+1, y4+1, x5-x0-2, y5-y4-2, (x5+x0)/2, (y5+y4)/2 };
static int boxE0[6] = { x5+1, y1+1, x4-x5-2, y7-y1-2, (x5+x4)/2, (y7+y1)/2 };
static int boxE1[6] = { x5+1, y7+1, x4-x5-2, y5-y7-2, (x5+x4)/2, (y5+y7)/2 };
static int boxE0t1[6] = { x5+1, y1+1, x4-x5-2, y7a-y1-2, (x5+x4)/2, (y7a+y1)/2 };
static int boxE0t2[6] = { x5+1, y7a+1, x4-x5-2, y7b-y7a-2, (x5+x4)/2, (y7b+y7a)/2 };
static int boxE0d[6] = { x5+1, y7b+1, x4-x5-2, y7-y7b-2, (x5+x4)/2, (y7+y7b)/2 };
static int boxE1t1[6] = { x5+1, y7+1, x4-x5-2, y7c-y7-2, (x5+x4)/2, (y7c+y7)/2 };
static int boxE1t2[6] = { x5+1, y7c+1, x4-x5-2, y7d-y7c-2, (x5+x4)/2, (y7d+y7c)/2 };
static int boxE1d[6] = { x5+1, y7d+1, x4-x5-2, y5-y7d-2, (x5+x4)/2, (y5+y7d)/2 };

//----Init DISPLAY-------------
void InitDisplay()
{
	if ( sFlag.s_val )
	{
		elapsedMicros displayInitTime = 0;
		if ( sFlag.border )			
		{
// draw borders
			tft.drawRect( boxA1[x]-1, boxA1[y]-1, boxA1[w]+2, boxA1[h]+2, borderColor );
			tft.drawRect( boxA2[x]-1, boxA2[y]-1, boxA2[w]+2, boxA2[h]+2, borderColor );
			tft.drawRect( boxA3[x]-1, boxA3[y]-1, boxA3[w]+2, boxA3[h]+2, borderColor );
			tft.drawRect( boxA4[x]-1, boxA4[y]-1, boxA4[w]+2, boxA4[h]+2, borderColor );
			tft.drawRect( boxS1[x]-1, boxS1[y]-1, boxS1[w]+2, boxS1[h]+2, borderColor );
			tft.drawRect( boxS2[x]-1, boxS2[y]-1, boxS2[w]+2, boxS2[h]+2, borderColor );
			tft.drawRect( boxS3[x]-1, boxS3[y]-1, boxS3[w]+2, boxS3[h]+2, borderColor );
			tft.drawRect( boxS4[x]-1, boxS4[y]-1, boxS4[w]+2, boxS4[h]+2, borderColor );
			tft.drawRect( boxE0[x]-1, boxE0[y]-1, boxE0[w]+2, boxE0[h]+2, borderColor );
			tft.drawRect( boxE1[x]-1, boxE1[y]-1, boxE1[w]+2, boxE1[h]+2, borderColor );
			tft.drawRect( boxA5[x]-1, boxA5[y]-1, boxA5[w]+2, boxA5[h]+2, borderColor );
			tft.drawRect( boxA6[x]-1, boxA6[y]-1, boxA6[w]+2, boxA6[h]+2, borderColor );
			tft.drawRect( boxA7[x]-1, boxA7[y]-1, boxA7[w]+2, boxA7[h]+2, borderColor );
			tft.drawRect( boxA8[x]-1, boxA8[y]-1, boxA8[w]+2, boxA8[h]+2, borderColor );
// fill S1 box, add text CW - PWR
			tft.fillRect( boxS1[x], boxS1[y], boxS1[w], boxS1[h], S1ColorBg);
			tft.setTextColor(S1TextColor, S1ColorBg);
			tft.setTextSize(S1TextSize);
			tft.setCursor( boxS1[x]+ S1T1 , boxS1[y] + (boxS1[h]-7*S1TextSize)/2 );
			tft.print ( "CW" );
			tft.setCursor( boxS1[x]+ S1T2 , boxS1[y] + (boxS1[h]-7*S1TextSize)/2 );
			tft.print ( "PWR" );
// draw SWR Scale
			tft.fillRect( boxS2[x], boxS2[y], boxS2[w], boxS2[h], S2ColorBg);
			tft.drawFastHLine(xsStart, ysLine, xsEnd-xsStart, S2TextColor);
			for ( byte j = 0; j < svmarkers; j++)
			{
				tft.drawFastVLine( s[j]+xsStart, ysLine+1, ysMarkerL, S2TextColor);		
			}
			tft.drawFastVLine( s[0]+xpStart, ysBar, ysBarL, boxSwrColor[0]);		
			tft.setTextColor(S2TextColor, S2ColorBg);
			tft.setTextSize(S2TextSize);
			tft.setCursor( s[0]+xsStart , ysText1 );
			tft.print ( "SWR" );
			tft.setCursor( s[0]+xsStart , ysText );
			tft.print ( "1" );
			tft.setCursor( s[1]+1 , ysText );
			tft.print ( "2" );
			tft.setCursor( s[2]+1 , ysText );
			tft.print ( "3" );
			tft.setCursor( s[3]+1 , ysText );
			tft.print ( "5" );
			tft.setCursor( s[4]+1 , ysText );
			tft.print ( "7" );
			tft.setCursor( s[5]-1 , ysText );
			tft.print ( "10" );
// draw RF POWER Scale
			tft.fillRect( boxS3[x], boxS3[y], boxS3[w], boxS3[h], S3ColorBg);
			tft.drawFastHLine(xpStart, ypLine, xpEnd-xpStart, S3TextColor);
			for ( byte j = 0; j < pvmarkers; j++)
			{
				tft.drawFastVLine( p[j]+xpStart, ypLine+1, ypMarkerL, S3TextColor);		
			}
			tft.drawFastVLine( p[0]+xpStart, ypBar, ypBarL, boxPwrColor[0]);		
			tft.setTextColor(S3TextColor, S3ColorBg);
			tft.setTextSize(S3TextSize);
			tft.setCursor( p[0]+xpStart , ypText1 );
			tft.print ( "PWR" );
			tft.setCursor( p[0]+xpStart , ypText );
			tft.print ( "0" );
			tft.setCursor( p[1]-2 , ypText );
			tft.print ( "10" );
			tft.setCursor( p[2]-2 , ypText );
			tft.print ( "20" );
			tft.setCursor( p[3]-2 , ypText );
			tft.print ( "30" );
			tft.setCursor( p[4]-2 , ypText );
			tft.print ( "40" );
			tft.setCursor( p[6]-2 , ypText );
			tft.print ( "60" );
			tft.setCursor( p[8]-2 , ypText );
			tft.print ( "80" );
			tft.setCursor( p[10]-2 , ypText );
			tft.print ( "100" );
// draw ID 
			tft.fillRect( boxS4[x], boxS4[y], boxS4[w], boxS4[h], S4ColorBg);
			tft.drawFastHLine(xiStart, yiLine, xiEnd-xiStart, S4TextColor);
			for ( byte j = 0; j < ivmarkers; j++)
			{
				tft.drawFastVLine( id[j]+xiStart, yiLine+1, yiMarkerL, S4TextColor);		
			}
			tft.drawFastVLine( id[0]+xiStart, yiBar, yiBarL, boxIddColor[0]);		
			tft.setTextColor(S4TextColor, S4ColorBg);
			tft.setTextSize(S4TextSize);
			tft.setCursor( id[0]+xiStart , yiText1 );
			tft.print ( "IDD" );
			tft.setCursor( id[0]+xiStart , yiText );
			tft.print ( "0" );
			tft.setCursor( id[2]+1 , yiText );
			tft.print ( "5" );
			tft.setCursor( id[4]-2 , yiText );
			tft.print ( "10" );
			tft.setCursor( id[6]-2 , yiText );
			tft.print ( "15" );
			tft.setCursor( id[8]-2 , yiText );
			tft.print ( "20" );
			sFlag.border = 0;
		}
		if ( dFlag.disp && Serial )
		{
			Serial.print( "Display - Border init time (us) = ");
			Serial.println( displayInitTime );
		}
	}
}

//----UPDATE DISPLAY-------------
void UpdateDisplay()
{
	if ( aFlag.a_val )
	{
		elapsedMicros displayATime = 0;
		if ( aFlag.ant1 )	// fill box, add text
		{
			tft.fillRect( boxA1[x], boxA1[y], boxA1[w], boxA1[h], boxAColor[0]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA1[xc]-6*Ant[0].name.length()*antTextSize/2, boxA1[yc]-7*antTextSize/2 );
			tft.print(Ant[0].name);
			aFlag.ant1 = 0;
		}
		if ( aFlag.ant2 )	// fill box, add text
		{
			tft.fillRect( boxA2[x], boxA2[y], boxA2[w], boxA2[h], boxAColor[1]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA2[xc]-6*Ant[1].name.length()*antTextSize/2, boxA2[yc]-7*antTextSize/2 );
			tft.print(Ant[1].name);
			aFlag.ant2 = 0;
		}
		if ( aFlag.ant3 )	// fill box, add text
		{
			tft.fillRect( boxA3[x], boxA3[y], boxA3[w], boxA3[h], boxAColor[2]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA3[xc]-6*Ant[2].name.length()*antTextSize/2, boxA3[yc]-7*antTextSize/2 );
			tft.print(Ant[2].name);
			aFlag.ant3 = 0;
		}
		if ( aFlag.ant4 )	// fill box, add text
		{
			tft.fillRect( boxA4[x], boxA4[y], boxA4[w], boxA4[h], boxAColor[3]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA4[xc]-6*Ant[3].name.length()*antTextSize/2, boxA4[yc]-7*antTextSize/2 );
			tft.print(Ant[3].name);
			aFlag.ant4 = 0;
		}
		if ( aFlag.ant5 )	// fill box, add text
		{
			tft.fillRect( boxA5[x], boxA5[y], boxA5[w], boxA5[h], boxAColor[4]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA5[xc]-6*Ant[4].name.length()*antTextSize/2, boxA5[yc]-7*antTextSize/2 );
			tft.print(Ant[4].name);
			aFlag.ant5 = 0;
		}
		if ( aFlag.ant6 )	// fill box, add text
		{
			tft.fillRect( boxA6[x], boxA6[y], boxA6[w], boxA6[h], boxAColor[5]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA6[xc]-6*Ant[5].name.length()*antTextSize/2, boxA6[yc]-7*antTextSize/2 );
			tft.print(Ant[5].name);
			aFlag.ant6 = 0;
		}
		if ( aFlag.ant7 )	// fill box, add text
		{
			tft.fillRect( boxA7[x], boxA7[y], boxA7[w], boxA7[h], boxAColor[6]);
			tft.setTextColor(antTextColor);
			tft.setTextSize(antTextSize);
			tft.setCursor( boxA7[xc]-6*Ant[6].name.length()*antTextSize/2, boxA7[yc]-7*antTextSize/2 );
			tft.print(Ant[6].name);
			aFlag.ant7 = 0;
		}
		if ( aFlag.ant8 )	// fill box, add text
		{
		tft.fillRect( boxA8[x], boxA8[y], boxA8[w], boxA8[h], boxAColor[7]);
		tft.setTextColor(antTextColor);
		tft.setTextSize(antTextSize);
		tft.setCursor( boxA8[xc]-6*Ant[7].name.length()*antTextSize/2, boxA8[yc]-7*antTextSize/2 );
		tft.print(Ant[7].name);
		aFlag.ant8 = 0;
		}
		aFlag.a_val = 0;
		if ( dFlag.disp && Serial )
		{
			Serial.print( "Display - Antenna update time(us) = ");
			Serial.println( displayATime );
		}
	}
	if ( sFlag.s_val )
	{
		elapsedMicros displayTime = 0;
		if ( sFlag.s1cw )	// fill box, add text
		{
			tft.fillRect( S1D1, boxS1[y], 2*S1TextSize*6, boxS1[h], S1ColorBg);
			tft.setTextColor(S1TextColor, S1ColorBg);
			tft.setTextSize(S1TextSize);
			tft.setCursor( boxS1[x]+ S1D1 , boxS1[y] + (boxS1[h]-7*S1TextSize)/2 );
			String S1 = String(cwSpeed);
			tft.print ( S1 );
			sFlag.s1cw = 0;
		}
		if ( sFlag.s1rf )	// fill box, add text
		{
			tft.fillRect( S1D2, boxS1[y], 3*S1TextSize*6, boxS1[h], S1ColorBg);
			tft.setTextColor(S1TextColor, S1ColorBg);
			tft.setTextSize(S1TextSize);
			tft.setCursor( boxS1[x]+ S1D2 , boxS1[y] + (boxS1[h]-7*S1TextSize)/2 );
			String S1 = String(rfPower);
			tft.print ( S1 );
			sFlag.s1rf = 0;
		}
		if ( sFlag.s1txd )	// fill box, add text
		{
			tft.setTextColor(S1TxdColor, S1ColorBg);
			tft.setTextSize(S1TextSize);
			tft.setCursor( boxS1[x]+ S1TXD , boxS1[y] + (boxS1[h]-7*S1TextSize)/2 );
			tft.print ( "TX" );
			sFlag.s1txd = 0;
		}
		if ( sFlag.s2 )	// SWR fill box, add text
		{
			if ( swr < oldSwr )
			{
				tft.fillRect( xsStart+swr+1 , ysBar, xsStart+oldSwr-swr-1, ysBarL, S2ColorBg);
			}
			else
			{
				if ( swr > 0 )
				{
					if ( swr > yswr0 )
					{
						tft.fillRect( xsStart+1 , ysBar, yswr0, ysBarL, boxSwrColor[0]);
					}
					else
					{
						tft.fillRect( xsStart+1 , ysBar, swr, ysBarL, boxSwrColor[0]);
					}
				}
				if ( swr > yswr0 )
				{
					if ( swr > yswr1 )
					{
						tft.fillRect( xsStart+yswr0+1 , ysBar, yswr1-yswr0, ysBarL, boxSwrColor[1]);	
					}
					else
					{
						tft.fillRect( xsStart+yswr0+1 , ysBar, swr-yswr0, ysBarL, boxSwrColor[1]);
					}
				}
				if ( swr > yswr1 )
				{
					if ( swr > 191 )
					{
						swr = 191;
					}
					tft.fillRect( xsStart+yswr1+1 , ysBar, swr-yswr1, ysBarL, boxSwrColor[2]);
				}
			}
			oldSwr = swr;
			sFlag.s2 = 0;
		}
		if ( sFlag.s3 )	// POWER fill box, add text
		{
			if ( power < oldPower )
			{
				tft.fillRect( xpStart+power+1 , ypBar, xpStart+oldPower-power-1, ypBarL, S3ColorBg);
			}
			else
			{
                                if ( power > 0  )
                                {
                                        if ( power > ypwr0 )
                                        {
                                                tft.fillRect( xpStart+1 , ypBar, ypwr0, ypBarL, boxPwrColor[0]);
                                        }
                                        else
                                        {
                                                tft.fillRect( xpStart+1 , ypBar, power, ypBarL, boxPwrColor[0]);
                                        }
                                }
				if ( power > ypwr0 )
				{
					if ( power > ypwr1 )
					{
						tft.fillRect( xpStart+ypwr0+1 , ypBar, ypwr1-ypwr0, ypBarL, boxPwrColor[1]);	
					}
					else
					{
						tft.fillRect( xpStart+ypwr0+1 , ypBar, power-ypwr0, ypBarL, boxPwrColor[1]);
					}
				}
				if ( power > ypwr1 )
				{
					if ( power > 191 )
					{
						power = 191;
					}				
					tft.fillRect( xpStart+ypwr1+1 , ypBar, power-ypwr1, ypBarL, boxPwrColor[2]);
				}
			}
			oldPower = power;
			sFlag.s3 = 0;
		}
		if ( sFlag.s4 )	// fill box, add text
		{
			if ( idd < oldIdd )
			{
				tft.fillRect( xiStart+idd+1 , yiBar, xiStart+oldIdd-idd-1, yiBarL, S4ColorBg);
			}
			else
			{
				if ( idd > 0  )
				{
					if ( idd > yidd0 )
					{
						tft.fillRect( xiStart+1 , yiBar, yidd0, yiBarL, boxIddColor[0]);
					}
					else
					{
						tft.fillRect( xiStart+1 , yiBar, idd, yiBarL, boxIddColor[0]);
					}
				}
				if ( idd > yidd0 )
				{
					if ( idd > yidd1 )
					{
						tft.fillRect( xiStart+yidd0+1 , yiBar, yidd1-yidd0, yiBarL, boxIddColor[1]);	
					}
					else
					{
						tft.fillRect( xiStart+yidd0+1 , yiBar, idd-yidd0, yiBarL, boxIddColor[1]);
					}
				}
				if ( idd > yidd1 )
				{
					if ( idd > 191 )
					{
						idd = 191;
					}				
					tft.fillRect( xiStart+yidd1+1 , yiBar, idd-yidd1, yiBarL, boxIddColor[2]);
				}
			}
			oldIdd = idd;
			sFlag.s4 = 0;
		}
		if ( sFlag.enc0t )	// fill box, add text
		{
			tft.fillRect( boxE0t1[x], boxE0t1[y], boxE0t1[w], boxE0t1[h], E0ColorBg);
			tft.setTextColor(E0TextColor, E0ColorBg);
			tft.setTextSize(E0tTextSize);
			tft.setCursor( boxE0t1[xc]-6*E0txt1[presetState[20]].length()*E0tTextSize/2 , boxE0t1[yc]-7*E0tTextSize/2 );
			tft.print(E0txt1[presetState[20]]);
			tft.fillRect( boxE0t2[x], boxE0t2[y], boxE0t2[w], boxE0t2[h], E0ColorBg);
			tft.setTextColor(E0TextColor, E0ColorBg);
			tft.setTextSize(E0tTextSize);
			tft.setCursor( boxE0t2[xc]-6*E0txt2[presetState[20]].length()*E0tTextSize/2 , boxE0t2[yc]-7*E0tTextSize/2 );
			tft.print(E0txt2[presetState[20]]);
			sFlag.enc0t = 0;
		}
		if ( sFlag.enc0d )	// fill box, add text
		{
			tft.fillRect( boxE0d[x], boxE0d[y], boxE0d[w], boxE0d[h], E0ColorBg);
			tft.setTextColor(E0TextColor, E0ColorBg);
			tft.setTextSize(E0dTextSize);
			if ( presetState[20] == 0 || presetState[20] == 1 || presetState[20] == 2)
			{
				E0Val = String(enc0);
			}
			if ( presetState[20] == 3 )
			{
				E0Val = vdelay[brakeDelay];	
			} 	
			if ( presetState[20] == 4 )
			{
				E0Val = vdelay[voxDelay];	
			} 	
			tft.setCursor( boxE0d[xc]-6*E0Val.length()*E0dTextSize/2 , boxE0d[yc]-7*E0dTextSize/2 );
			tft.print(E0Val);
			sFlag.enc0d = 0;
		}
		if ( sFlag.enc1t )	// fill box, add text
		{
			tft.fillRect( boxE1t1[x], boxE1t1[y], boxE1t1[w], boxE1t1[h], E1ColorBg);
			tft.setTextColor(E1TextColor, E1ColorBg);
			tft.setTextSize(E1tTextSize);
			tft.setCursor( boxE1t1[xc]-6*E1txt1[presetState[12]].length()*E1tTextSize/2 , boxE1t1[yc]-7*E1tTextSize/2 );
			tft.print(E1txt1[presetState[12]]);
			tft.fillRect( boxE1t2[x], boxE1t2[y], boxE1t2[w], boxE1t2[h], E1ColorBg);
			tft.setTextColor(E1TextColor, E1ColorBg);
			tft.setTextSize(E1tTextSize);
			tft.setCursor( boxE1t2[xc]-6*E1txt2[presetState[12]].length()*E1tTextSize/2 , boxE1t2[yc]-7*E1tTextSize/2 );
			tft.print(E1txt2[presetState[12]]);
			sFlag.enc1t = 0;
		}
		if ( sFlag.enc1d )	// fill box, add text
		{
			tft.fillRect( boxE1d[x], boxE1d[y], boxE1d[w], boxE1d[h], E1ColorBg);
			tft.setTextColor(E1TextColor, E1ColorBg);
			tft.setTextSize(E1dTextSize);
			if ( presetState[12] == 0 )
			{
				E1Val = String(0.1 * scopeLevel, 1);
			}
			if ( presetState[12] == 1 )
			{
				E1Val = scopeSpanVal[scopeSpan];
			}
			if ( presetState[12] == 2 )
			{
				E1Val = String(rfPower);
			}
			tft.setCursor( boxE1d[xc]-6*E1Val.length()*E1dTextSize/2 , boxE1d[yc]-7*E1dTextSize/2 );
			tft.print(E1Val);
			sFlag.enc1d = 0;
		}
		if ( dFlag.disp && Serial )
		{
			Serial.print( "Display - Encoder update time (us) = ");
			Serial.println( displayTime );
		}
	}
}