// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:
#include <LiquidCrystal.h> 
// Initialize the library with the pins we're using.
LiquidCrystal lcd(12,11,5,4,3,2);
void setup()
{
  // begin lcd of this particular size
  lcd.begin(16, 2);
  // Data sent to the display will stay there until it's
  // overwritten or power is removed. 
  lcd.clear();
  // Now we'll display a message on the LCD!
  lcd.print("Hello World");
} 
void loop()
{
  lcd.print("Resistance is Futile");
  
  //wait a bit before taking another reading
  delay(1000);
}
