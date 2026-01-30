// 4ª oitava
#define NOTE_C4   262
#define NOTE_CS4  277
#define NOTE_D4   294
#define NOTE_DS4  311
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_FS4  370
#define NOTE_G4   392
#define NOTE_GS4  415
#define NOTE_A4   440
#define NOTE_AS4  466
#define NOTE_B4   494

// 5ª oitava
#define NOTE_C5   523
#define NOTE_CS5  554
#define NOTE_D5   587
#define NOTE_DS5  622
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_FS5  740
#define NOTE_G5   784
#define NOTE_GS5  831
#define NOTE_A5   880
#define NOTE_AS5  932
#define NOTE_B5   988

// 6ª oitava
#define NOTE_C6   1047


#define REST      0
#define UP     D6
#define DOWN   D7
#define OK     D8
#define BACK   D3
#define BUZZER D5
#define STAFF_TOP 20
#define STAFF_SPACING 6

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void drawPentagrama() {
  for (int i = 0; i < 5; i++) {
    int y = STAFF_TOP + i * STAFF_SPACING;
    display.drawLine(32, y, 90, y, WHITE);
  }
}


typedef struct no {
  int dado;
  struct no *prox;
} No;

typedef struct musica{
  No *inicio;
  int bpm;
  int tam;
} Musica;

void CriarMusica(Musica *mu);
void drawPentagrama();

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void CriarMusica(Musica *mu) {
  mu->inicio = NULL;
  mu->tam = 0;

  int contador = 0; 

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("UP/DOWN ajusta BPM");
  display.println("OK confirma");
  display.display();
  delay(2000);

  while (digitalRead(OK) == LOW) {

    if (digitalRead(UP) == HIGH) {
      contador++;
      if (contador > 14) {
        contador = 14;
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("O bpm deve estar entre 20 e 200");
          display.display();
          tone(BUZZER, NOTE_F5);
          delay(2000); 
          noTone(BUZZER);
      }
      delay(200);
    }

    if (digitalRead(DOWN) == HIGH) {
      contador--;
      if (contador < -4){
         contador = -4; 
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("O bpm deve estar entre 20 e 200");
          drawPentagrama();
          display.display();
          tone(BUZZER, NOTE_C4);
          delay(2000);
          noTone(BUZZER);
          
      }
      delay(200);
    }

    int bpmAtual = (contador * 10) + 60;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("BPM base: ");
    display.println(bpmAtual);
    display.display();
    delay(1);
  }

  mu->bpm = (contador * 10) + 60;
}

void loop(){

  Musica mu;
  CriarMusica(&mu);
  
 }