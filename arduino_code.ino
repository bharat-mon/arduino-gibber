#include <LiquidCrystal.h>
#include "CMBMenu.hpp"
#include <ArduinoJson.h>

// Initialize lcd with pin numbers
LiquidCrystal g_Lcd(7, 8, 9, 10, 11, 12);

// define text to display
const char g_Var1_pc[] PROGMEM = {"1. Var1"};
const char g_Var2_pc[] PROGMEM = {"2. Var2"};

// define function IDs
enum MenuFID {
  Var1,
  Var2
};

// Initialize the menu libraray
CMBMenu<5> g_Menu;

// Initialize JSON Serializer
StaticJsonDocument<32> doc;

// Buttons setup
int KeyRight = 5;
int KeyLeft = 4;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  // set LCD contrast
  analogWrite(13, 100);
  // mbLib LCD setup
  g_Lcd.begin(16, 2);
  g_Lcd.clear();

  // add nodes to menu (layer, string, function ID)
  g_Menu.addNode(0, g_Var1_pc , Var1);
  g_Menu.addNode(0, g_Var2_pc, Var2);

  // build menu and print menu
  const char* info;
  g_Menu.buildMenu(info);
  g_Menu.printMenu();
  // print current menu entry
  printMenuEntry(info);

  // Buttons
  pinMode(KeyRight, INPUT_PULLUP);
  pinMode(KeyLeft, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // function ID
  int fid = 0;

  // info text from menu
  const char* info;
  
  if (digitalRead(KeyRight) == LOW)
  {
    g_Menu.right();
  }
  if (digitalRead(KeyLeft) == LOW)
  {
    g_Menu.left();
  }
  delay(100);

  fid = g_Menu.getInfo(info);
  printMenuEntry(info);

  // potentiometer value
  int sensorValue = analogRead(A1);

  // Serialize data into JSON and send it via serial port
  doc["varSelect"] = fid;
  doc["value"] = sensorValue;
  serializeJson(doc, Serial);
  Serial.println();
  delay(1);
}

void printMenuEntry(const char* f_Info)
{
  String info_s;
  MBHelper::stringFromPgm(f_Info, info_s);

  // print on LCD
  g_Lcd.clear();
  g_Lcd.setCursor(0, 0);
  g_Lcd.print(info_s);
}
