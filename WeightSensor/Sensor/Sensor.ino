#include "HX711.h"  //You must have this library in your arduino library folder
#define DOUT  4
#define CLK  5
HX711 scale;
float calibration_factor = 1150; // this calibration factor is adjusted according to my load cell
float units;
void setup() {
 Serial.begin(9600);  
 scale.begin(DOUT , CLK);
 scale.set_scale(calibration_factor); //Adjust to this calibration factor
 scale.tare(); 
}
void loop() {
units = scale.get_units(), 5;
 if (units < 0)
 {
   units = 0.00;
 }
 Serial.print("Weight: ");
 Serial.print(units,5); //displays the weight in 4 decimal places only for calibration
 Serial.print("grams");
 Serial.println();

}
