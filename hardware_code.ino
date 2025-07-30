#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define calibration_factor -7050.0 
#define LOADCELL_DOUT_PIN  13
#define LOADCELL_SCK_PIN  2
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
float sensorValue;
int flag=0;
const int Aapp=4;
const int Aorange=8;
const int Achips=9;
const int Asub=10;
int bapp = 0;
int borange = 0;
int bchips = 0;
int bsub = 0;
HX711 scale;
float fweight;
double total = 0;
double fapp = 0;
double forang = 0;
double fchips = 0;
double fkgapp = 0;
double fkgorang = 0;
double fkgchips = 0;
int count_prod = 0;
void setup()
{
Serial.begin(9600);
 pinMode(Aapp,INPUT);
  pinMode(Aorange,INPUT);
pinMode(Achips,INPUT);
 pinMode(Asub,INPUT);
 
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0               // show on OLED
  
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Reading"); // text to display
  oled.println("---------"); // text to display
  oled.display();               // show on OLED
  delay(2000);
  
}
 
void loop()
{
   bapp= digitalRead(Aapp);
 borange= digitalRead(Aorange);
 bgraps= digitalRead(Achips);
 bsub= digitalRead(Asub);
 scale.set_scale(calibration_factor);
  fweight=abs(scale.get_units());
  Serial.println(fweight);
 if(fweight>=2) //Check the sensor output
 {
Serial.println("Weight");
   if(bapp == HIGH)
   {
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 10);        // position to display
    oled.println("Apple"); // text to display
                  // show on OLED
    fkgapp=abs((1-fweight)+fkgapp-fkgorang-fkgchips);
    
    fapp = (520/10)*fkgapp;
    oled.print("Cal=");
    oled.println(fapp); 
    oled.display(); 
    delay(500);
   }
   if(borange == HIGH)
   {
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 10);        // position to display
    oled.println("Orange"); // text to display
                  // show on OLED
    fkgorang=abs((1-fweight)+fkgapp-fkgorang-fkgchips);
    forang = (470/10)*fkgorang;
    oled.print("Cal=");
    oled.println(forang); 
    oled.display(); 
    delay(500);
   }
   if(bchips == HIGH)
   {
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 10);        // position to display
    oled.println("PotatoChips"); // text to display
                  // show on OLED
    fkgchips=abs((1-fweight)+fkgapp-fkgorang-fkgchips);
    fchips = (670/10)*fkgchips;
    oled.print("Cal=");
    oled.println(fchips); 
    oled.display(); 
    delay(500);
   }
   if(bsub == HIGH)
   {
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 10);        // position to display
    oled.println("Total"); // text to display
                  // show on OLED
    total=fapp+forang+bchips;
    oled.print("Cal=");
    oled.println(total); 
    oled.display(); 
    delay(500);
     total = 0;
    fapp = 0;
    forang = 0;
    fchips = 0;
    fkgorang = 0;
    fkgchips = 0;
   }
   
 }
}
