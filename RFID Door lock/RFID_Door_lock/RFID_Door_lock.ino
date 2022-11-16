#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MFRC522.h>
 LiquidCrystal_I2C lcd(0x3F,16,2);
 MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
 Servo myservo;
 int angle=0;
 String tagUID = "DA 54 6E 3C"; // String to store UID of tag. Change it with your tag's UID
 
 void setup() {
 myservo.attach(6);
 lcd.init(); // LCD screen
 lcd.backlight();
 SPI.begin(); // Init SPI bus
 mfrc522.PCD_Init(); // Init MFRC522
 
 lcd.clear();
 }
 void loop() {
 lcd.setCursor(0, 0);
 lcd.print(" RFID Door Lock");
 delay(1000);
 lcd.setCursor(0, 1);
 lcd.print(" Show Your Tag ");
 
 // Look for new cards
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
 return;
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
 return;
 }
 
 //Reading from the card
 String tag = "";
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
 tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 tag.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 tag.toUpperCase();
 
 //Checking the card
 if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access
 {
 // If UID of tag is matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Access Granted");
 lcd.setCursor(0, 1);
 lcd.print("Door Opened");
 myservo.write(90);
 //digitalWrite(greenLed, HIGH);
 delay(7000);
 //digitalWrite(greenLed, LOW);
 myservo.write(0);
 lcd.clear();
 }
 
 else
 {
 // If UID of tag is not matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Wrong Tag Shown");
 lcd.setCursor(0, 1);
 lcd.print("Access Denied");
 delay(3000);
 lcd.clear();
 }
 }
