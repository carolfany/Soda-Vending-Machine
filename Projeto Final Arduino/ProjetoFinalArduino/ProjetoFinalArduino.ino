/* O código Arduino foi feito com o objetivo de controlar o display LCD e os 4 motores que fornecem refrigerante.
 * O Arduino recebe 5 dados do kit referentes à moeda colocada, 4 dados referentes ao refrigerante e um referente à
 * confirmação da compra. O Arduino realiza cálculos paralelamente ao kit para poder mostrar o saldo no display,
 * e ao final do processo, calcula o troco e mostra no display, fornecendo o refrigerante escolhido.                                                                               
 */

#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
LiquidCrystal lcd(7, 5, 4, 3, 0, 1); //RS(4) , Enable(6), D4(11), D5(12), D6(13), D7(14), RW(5)->GND, VSS(1)->GND, VCC(2)->5V, V0->pot

int soma = 0;      //variável que guarda o valor do saldo corrente
int troco;
const int conf = 2;
const int moeda1 = 14;    //pinos de entrada no Arduino que vem do kit
const int moeda2 = 15;   
const int moeda3 = 16;    
const int moeda4 = 17;
const int moeda5 = 18;
const int sel1 = 19;
const int sel2 = 13;
const int sel3 = 12;
const int sel4 = 8;
int soma5 = 0;
int soma10 = 0;
int soma25 = 0;
int soma50 = 0;           //variáveis que guardam o estado de cada entrada
int soma100 = 0;
int refri1 = 0;
int refri2 = 0;
int refri3 = 0;
int refri4 = 0;
int p1 = 100;           //preços fixados para cada refrigerante
int p2 = 170;
int p3 = 225;
int p4 = 250;
int confirma = 0;

void setup() {
servo1.attach(11);
servo2.attach(10);
servo3.attach(9);
servo4.attach(6);
pinMode(moeda1, INPUT);
pinMode(moeda2, INPUT);
pinMode(moeda3, INPUT);
pinMode(moeda4, INPUT);
pinMode(moeda5, INPUT);
pinMode(sel1, INPUT);
pinMode(sel2, INPUT);
pinMode(sel3, INPUT);
pinMode(sel4, INPUT);
pinMode(conf, INPUT);
lcd.begin(16, 2);
}

void loop() {
soma5 = digitalRead(moeda1);
soma10 = digitalRead(moeda2);
soma25 = digitalRead(moeda3);
soma50 = digitalRead(moeda4);
soma100 = digitalRead(moeda5);
refri1 = digitalRead(sel1);
refri2 = digitalRead(sel2);
refri3 = digitalRead(sel3);
refri4 = digitalRead(sel4);
confirma = digitalRead(conf);
if(soma5 == HIGH){
  soma = soma + 5;                    //loop while que garante que a soma será feita apenas uma vez quando o botão for pressionado
  while(soma5 == HIGH){
    soma5 = digitalRead(moeda1);
  }
}
if(soma10 == HIGH){
  soma = soma + 10;
   while(soma10 == HIGH){           
    soma10 = digitalRead(moeda2);
   }
}
if(soma25 == HIGH){
  soma = soma + 25;
  while(soma25 == HIGH){
    soma25 = digitalRead(moeda3);
  }
}
if(soma50 == HIGH){
  soma = soma + 50;
  while(soma50 == HIGH){
    soma50 = digitalRead(moeda4);
  }
}
if(soma100 == HIGH){
  soma = soma + 100;
  while(soma100 == HIGH){
    soma100 = digitalRead(moeda5);
  }
}
if(refri1 == HIGH){
  servo1.write(180);                //reposicionamento dos motores para fornecimento do refrigerante
  delay(1000);    
  servo1.write(0);
  troco = soma - p1;                //calcula o troco
  while(refri1 == HIGH){            
    refri1 = digitalRead(sel1);
  }
  lcd.clear();
  while(confirma == LOW){           //loop que espera o sinal de confirmação
  lcd.setCursor(0,0);
  lcd.print("Troco: ");            //mostra o troco no display
  lcd.print(troco);
  confirma = digitalRead(conf);
  }
  lcd.clear();                    //limpa a tela do display e zera a variável soma
  soma = 0;
}
if(refri2 == HIGH){
  servo2.write(180);
  delay(1000);
  servo2.write(0);
  troco = soma - p2;
  while(refri2 == HIGH){
    refri2 = digitalRead(sel2);
  }
  lcd.clear();
  while(confirma == LOW){
  lcd.setCursor(0,0);
  lcd.print("Troco: ");
  lcd.print(troco);
  confirma = digitalRead(conf);

  }
  lcd.clear();
  soma = 0;
}
if(refri3 == HIGH){
  servo2.write(180);
  delay(1000);
  servo3.write(0);
  troco = soma - p3;
  while(refri2 == HIGH){
    refri3 = digitalRead(sel3);
  }
  lcd.clear();
  while(confirma == LOW){
  lcd.setCursor(0,0);
  lcd.print("Troco: ");
  lcd.print(troco);
  confirma = digitalRead(conf);

  }
  lcd.clear();
  soma = 0;
}
if(refri4 == HIGH){
  servo4.write(180);
  delay(1000);
  servo4.write(0);
  troco = soma - p4;
  while(refri4 == HIGH){
    refri4 = digitalRead(sel4);
  }
  lcd.clear();
  while(confirma == LOW){
  lcd.setCursor(0,0);
  lcd.print("Troco: ");
  lcd.print(troco);
  confirma = digitalRead(conf);

  }
  lcd.clear();
  soma = 0;
}
lcd.setCursor(0,0);
lcd.print("Saldo: ");     //mostra o saldo no display
lcd.print(soma);
}
