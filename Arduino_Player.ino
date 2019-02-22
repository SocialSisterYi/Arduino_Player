#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Audio.h>

#define SD_CS  A0
#define LCD_RS 53
#define LCD_E  52
#define LCD_D4 51
#define LCD_D5 50
#define LCD_D6 49
#define LCD_D7 48

LiquidCrystal lcd1602(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void Music_Player(File MusicFile,int rate,int rebuff_time,int volume,uint32_t buffer_size)
{
	int16_t buffer[buffer_size];
	
	Audio.begin(rate,rebuff_time);
	while(MusicFile.available())
	{
		MusicFile.read(buffer,sizeof(buffer));
		Audio.prepare(buffer,buffer_size,volume);
		Audio.write(buffer,buffer_size);
	}
	MusicFile.close();
}

void setup()
{
	lcd1602.begin(16,2);
	lcd1602.clear();
	lcd1602.print("Arduino Player");
	lcd1602.setCursor(0,1);
	lcd1602.print("Social Sister Yi");
	delay(1000);
	lcd1602.clear();
	lcd1602.setCursor(0,0);
	lcd1602.print("Init SD Card");
	lcd1602.setCursor(0,1);
	if (!SD.begin(SD_CS))
	{
		lcd1602.print("Fail!");
		while(1);
	}
	lcd1602.print("OK!");
	delay(500);
	
	lcd1602.clear();
	lcd1602.print("open test.wav");
	lcd1602.setCursor(0,1);
	File myFile=SD.open("test.wav");
	if(!myFile)
	{
		lcd1602.print("Fail!");
		while(1);
	}
	lcd1602.print("OK!");
	delay(500);
	
	lcd1602.clear();
	lcd1602.print("Playing!");
	Music_Player(myFile,88200,200,1024,8192);
	lcd1602.clear();
	lcd1602.print("Done!");
}

void loop()
{
  
}
