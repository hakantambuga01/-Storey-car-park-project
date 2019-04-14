#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>


#define A1  53
#define A2  51
#define A3  49
#define A4  47
#define A5  45
#define A6  43
#define B1  41
#define B2  39
#define B3  37
#define B4  35
#define B5  33
#define B6  31
#define C1  29
#define C2  27
#define C3  25
#define C4  23
#define C5  21
#define C6  20
#define D1  19
#define D2  18
#define D3  17
#define D4  16
#define D5  15
#define D6  14

#define kizak_ileri  6
#define kizak_geri  7
#define tabla_adim_pin  9
#define tabla_yon_pin  8
#define asansor_adim1_pin  11
#define asansor_yon1_pin  10
#define asansor_adim2_pin  13
#define asansor_yon2_pin  12

Servo servo_giris;  // create servo object to control a servo
Servo servo_cikis; 
Servo servo_kntrl;
int pos_giris = 0;
int pos_cikis = 100;
int pos_kntrl = 30;
int bariyer_kaldir=0;
const byte satirSayisi= 4;
const byte sutunSayisi= 4;
char tuslar[satirSayisi][sutunSayisi]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte satirPinleri[satirSayisi] = {38,40,42,44};
byte sutunPinleri[sutunSayisi]= {46,48,50,52};
Keypad tusTakimi= Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, satirSayisi, sutunSayisi);

const int rs = 36, en = 34, d4 = 28, d5 = 26, d6 = 24, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int asansor_geri_cekme = 80;
int tabla_suresi = 3000;
int arac_alma_mod=0;
float kat_adimi;
int saat_yonu_tersi_azalt=0;

void setup() {
  Serial.begin(9600);
  pinMode(kizak_ileri,OUTPUT); 
  pinMode(kizak_geri,OUTPUT);
  pinMode(tabla_adim_pin,OUTPUT); 
  pinMode(tabla_yon_pin,OUTPUT);
  pinMode(asansor_adim1_pin,OUTPUT); 
  pinMode(asansor_yon1_pin,OUTPUT);
  pinMode(asansor_adim2_pin,OUTPUT); 
  pinMode(asansor_yon2_pin,OUTPUT);

  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, HIGH);
  digitalWrite(asansor_adim1_pin, LOW);
  digitalWrite(asansor_yon1_pin, LOW);
  digitalWrite(asansor_adim2_pin, LOW);
  digitalWrite(asansor_yon2_pin, LOW);
  digitalWrite(tabla_adim_pin,LOW); 
  digitalWrite(tabla_yon_pin,LOW);

  servo_giris.attach(3);  // attaches the servo on pin 9 to the servo object
  servo_cikis.attach(4);
  servo_kntrl.attach(5);
  
  lcd.begin(20, 4);
  lcd.setCursor(0,1);
  lcd.print("   KATLI OTOPARK");  
  lcd.setCursor(3,2);
  lcd.print("HOS GELDINIZ");
  delay(3000);
  
  for(int s = 54 ; s > 13 ; s--)
  {
    if(s > 21) s--;
    Serial.println(s);
    pinMode(s, INPUT);
  }
  servo_giris.write(15);
  servo_cikis.write(0);
  servo_kntrl.write(50);
}

void loop() 
{
  lcd.clear();  
  lcd.setCursor(1,0);
  lcd.print("ARACINIZI BIRAKMAK");  
  lcd.setCursor(2,1);
  lcd.print("ICIN '*' BASINIZ"); 
  lcd.setCursor(2,2);
  lcd.print("ARACINIZI ALMAK");  
  lcd.setCursor(2,3);
  lcd.print("ICIN '#' BASINIZ");
  delay(100);
//  lcd.print(digitalRead(A1));
//  lcd.setCursor(5,0);
//  lcd.print("A2:");
//  lcd.print(digitalRead(A2));
//  lcd.setCursor(10,0);
//  lcd.print("A3:");
//  lcd.print(digitalRead(A3));
//  lcd.setCursor(16,0);
//  lcd.print("A4:");
//  lcd.print(digitalRead(A4));
//  lcd.setCursor(16,0);
//  lcd.print("A5:");
//  lcd.print(digitalRead(A5));
//  lcd.setCursor(16,0);
//  lcd.print("A6:");
//  lcd.print(digitalRead(A6));
//  delay(100);

  
  char basilanTus = tusTakimi.getKey();
  if (basilanTus != NO_KEY){
  Serial.print(basilanTus);
  if(basilanTus == '*')
  {
    servo_giris.write(100); 
    delay(5000);
    arac_al();    
    servo_giris.write(15);
    if(digitalRead (A1)==0)
    {
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      arac_birak();
//      saat_yonu_tersi_azalt=1;
      saat_yonu_tersi();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if (digitalRead (A2)==0)
    { 
      bir_kat_asagi_git();
      arac_birak();
      bir_kat_yukari_git();   
      servo_kntrl.write(pos_kntrl);  
    }
    else if (digitalRead (A3)==0)
    { 
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      arac_birak();   
      saat_yonu();       
      bir_kat_yukari_git(); 
      servo_kntrl.write(pos_kntrl);     
    }
    else if (digitalRead (A4)==0)
    { 
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();      
      saat_yonu();
      bir_kat_yukari_git();  
      servo_kntrl.write(pos_kntrl);
    }
    else if (digitalRead (A5)==0)
    { 
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      saat_yonu();  
      bir_kat_yukari_git();  
      servo_kntrl.write(pos_kntrl);    
    }
    else if(digitalRead (A6)==0)
    {
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      saat_yonu_tersi();
      bir_kat_yukari_git();  
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B1)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B2)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      arac_birak();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B3)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B4)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B5)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (B6)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C1)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C2)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      arac_birak();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C3)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C4)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C5)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (C6)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D1)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D2)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      arac_birak();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D3)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D4)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D5)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      servo_kntrl.write(pos_kntrl);
      saat_yonu_tersi();
      saat_yonu_tersi();
      saat_yonu_tersi();
      arac_birak();
      saat_yonu();
      saat_yonu();
      saat_yonu();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
    else if(digitalRead (D6)==0)
    {
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      bir_kat_asagi_git();
      saat_yonu();
      saat_yonu();
      arac_birak();
      saat_yonu_tersi();
      saat_yonu_tersi();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      bir_kat_yukari_git();
      servo_kntrl.write(pos_kntrl);
    }
  }
  
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  if(basilanTus == '#')arac_alma_mod = 1;
  while(arac_alma_mod == 1)
  {
    char basilanTus = tusTakimi.getKey();
    if (basilanTus != NO_KEY){
    Serial.print(basilanTus);
    if(basilanTus == 'A')kat_adimi=1;
    if(basilanTus == 'B')kat_adimi=2;
    if(basilanTus == 'C')kat_adimi=3;
    if(basilanTus == 'D')kat_adimi=4;
    Serial.print(kat_adimi);
    if(basilanTus == '1')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
    }
    ///////////////////////--------------------------------//////////////////////////
    if(basilanTus == '2')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        arac_al();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
    }
    ///////////////////////--------------------------------//////////////////////////
    if(basilanTus == '3')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        arac_al();
        saat_yonu(); 
        bir_kat_yukari_git();
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0;
        servo_cikis.write(pos_cikis); 
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
    }
    ///////////////////////--------------------------------//////////////////////////
    if(basilanTus == '4')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0;
        servo_cikis.write(pos_cikis); 
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        saat_yonu_tersi();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
    }
    ///////////////////////--------------------------------//////////////////////////
    if(basilanTus == '5')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0;
        arac_alma_mod=0;  
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu_tersi();
        saat_yonu_tersi();
        saat_yonu_tersi();
        arac_al();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0;
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis); 
        bariyer_kaldir=1; 
      }
    }
    ///////////////////////--------------------------------//////////////////////////
    if(basilanTus == '6')
    {
      if(kat_adimi == 1)
      {
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        saat_yonu();
        arac_al();
        saat_yonu();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 2)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        saat_yonu();
        arac_al();
        saat_yonu();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0; 
        servo_cikis.write(pos_cikis);
        bariyer_kaldir=1; 
      }
      else if(kat_adimi == 3)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        saat_yonu();
        arac_al();
        saat_yonu();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak();  
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu();
        kat_adimi=0; 
        arac_alma_mod=0;  
        servo_cikis.write(pos_cikis);   
        bariyer_kaldir=1;      
      }
      else if(kat_adimi == 4)
      {
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        bir_kat_asagi_git();
        servo_kntrl.write(pos_kntrl);
        saat_yonu();
        saat_yonu();
        arac_al();
        saat_yonu();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        bir_kat_yukari_git();
        servo_kntrl.write(pos_kntrl);
        arac_birak(); 
        saat_yonu(); 
        saat_yonu(); 
        saat_yonu(); 
        kat_adimi=0; 
        arac_alma_mod=0;  
        servo_cikis.write(pos_cikis);  
        bariyer_kaldir=1; 
      }
    }
  }
  if(bariyer_kaldir == 1 ) 
  {
    delay(5000);
    servo_cikis.write(pos_cikis);  
  }
  }
  

  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////  
  ////////////////////////////////////////////////////////////
  if(basilanTus == '4')
  {
    digitalWrite(tabla_yon_pin, HIGH);
    for(long int x = 0; x < 70; x++) {
    digitalWrite(tabla_adim_pin,HIGH); 
    delayMicroseconds(tabla_suresi); 
    digitalWrite(tabla_adim_pin,LOW); 
    delayMicroseconds(tabla_suresi); 
  }
  }
  if(basilanTus == '6')
  {
    digitalWrite(tabla_yon_pin, LOW);
    for(long int x = 0; x < 70; x++) {
    digitalWrite(tabla_adim_pin,HIGH); 
    delayMicroseconds(tabla_suresi); 
    digitalWrite(tabla_adim_pin,LOW); 
    delayMicroseconds(tabla_suresi); 
    }
  }
  if(basilanTus == '2')
  {
//    servo_kntrl.write(0);
    digitalWrite(asansor_yon1_pin, HIGH);
    digitalWrite(asansor_yon2_pin, HIGH);
    for(long int x = 0; x < 2000; x++) {
    digitalWrite(asansor_adim1_pin,HIGH); 
    digitalWrite(asansor_adim2_pin,HIGH); 
    delayMicroseconds(asansor_geri_cekme); 
    digitalWrite(asansor_adim1_pin,LOW); 
    digitalWrite(asansor_adim2_pin,LOW); 
    delayMicroseconds(asansor_geri_cekme); 
    }
//    servo_kntrl.write(60);
  }
  if(basilanTus == '8')
  {
//    servo_kntrl.write(0);
    digitalWrite(asansor_yon1_pin, LOW);
    digitalWrite(asansor_yon2_pin, LOW);
    for(long int x = 0; x < 2000; x++) {
    digitalWrite(asansor_adim1_pin,HIGH); 
    digitalWrite(asansor_adim2_pin,HIGH); 
    delayMicroseconds(asansor_geri_cekme); 
    digitalWrite(asansor_adim1_pin,LOW); 
    digitalWrite(asansor_adim2_pin,LOW); 
    delayMicroseconds(asansor_geri_cekme); 
  }
//    servo_kntrl.write(60);
  }
  }}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void bir_kat_asagi_git()
{
  servo_kntrl.write(0);
  digitalWrite(asansor_yon1_pin, LOW);
  digitalWrite(asansor_yon2_pin, LOW);
  for(long int x = 0; x < 43000; x++) {
  digitalWrite(asansor_adim1_pin,HIGH); 
  digitalWrite(asansor_adim2_pin,HIGH); 
  delayMicroseconds(asansor_geri_cekme); 
  digitalWrite(asansor_adim1_pin,LOW); 
  digitalWrite(asansor_adim2_pin,LOW); 
  delayMicroseconds(asansor_geri_cekme);
  }    
  servo_kntrl.write(60);
}
void bir_kat_yukari_git()
{  
  servo_kntrl.write(0);
  
  digitalWrite(asansor_yon1_pin, HIGH);
  digitalWrite(asansor_yon2_pin, HIGH);
  for(long int x = 0; x < 40000; x++) {
  digitalWrite(asansor_adim1_pin,HIGH); 
  digitalWrite(asansor_adim2_pin,HIGH); 
  delayMicroseconds(asansor_geri_cekme); 
  digitalWrite(asansor_adim1_pin,LOW); 
  digitalWrite(asansor_adim2_pin,LOW); 
  delayMicroseconds(asansor_geri_cekme);
  }   
  servo_kntrl.write(60);
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void arac_al()
{
  digitalWrite(kizak_ileri, LOW);
  digitalWrite(kizak_geri, HIGH);
  delay(3000);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, HIGH);
  digitalWrite(asansor_yon1_pin, HIGH);
  digitalWrite(asansor_yon2_pin, HIGH);
  for(long int x = 0; x < 5000; x++) {
  digitalWrite(asansor_adim1_pin,HIGH); 
  digitalWrite(asansor_adim2_pin,HIGH); 
  delayMicroseconds(asansor_geri_cekme); 
  digitalWrite(asansor_adim1_pin,LOW); 
  digitalWrite(asansor_adim2_pin,LOW); 
  delayMicroseconds(asansor_geri_cekme); 
  }
  delay(500);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, LOW);
  delay(4000);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, HIGH);
}
void arac_birak()
{
  digitalWrite(kizak_ileri, LOW);
  digitalWrite(kizak_geri, HIGH);
  delay(3000);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, HIGH);
  digitalWrite(asansor_yon1_pin, LOW);
  digitalWrite(asansor_yon2_pin, LOW);
  for(long int x = 0; x < 4000; x++) {
  digitalWrite(asansor_adim1_pin,HIGH); 
  digitalWrite(asansor_adim2_pin,HIGH); 
  delayMicroseconds(asansor_geri_cekme); 
  digitalWrite(asansor_adim1_pin,LOW); 
  digitalWrite(asansor_adim2_pin,LOW); 
  delayMicroseconds(asansor_geri_cekme); 
  }
  delay(500);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, LOW);
  delay(3500);
  digitalWrite(kizak_ileri, HIGH);
  digitalWrite(kizak_geri, HIGH);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void saat_yonu()
{
  digitalWrite(tabla_yon_pin, HIGH);
  for(long int x = 0; x < 550; x++) {
  digitalWrite(tabla_adim_pin,HIGH); 
  delayMicroseconds(tabla_suresi); 
  digitalWrite(tabla_adim_pin,LOW); 
  delayMicroseconds(tabla_suresi); 
  }
}

void saat_yonu_tersi()
{
  digitalWrite(tabla_yon_pin, LOW);
  for(long int x = 0; x < 550; x++) {
//  if(saat_yonu_tersi_azalt=1)
//  {
//    if(x >= 500)
//    {
//      x=550;
//      saat_yonu_tersi_azalt=0;
//    }
//  }
  digitalWrite(tabla_adim_pin,HIGH); 
  delayMicroseconds(tabla_suresi); 
  digitalWrite(tabla_adim_pin,LOW); 
  delayMicroseconds(tabla_suresi); 
  }
}



