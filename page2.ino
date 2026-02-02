#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

typedef struct nota{
  int nota;
  int tempo;
} Nota;

typedef struct no {
  Nota notaMus;
  struct no *prox;
} No;

typedef struct musica{
  No *inicio;
  int bpm;
  int tam;
} Musica;


//============= prototipos ==============

// ===================== DEFINES DE NOTAS =====================

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
#define NOTE_C6   1047
#define REST 0

// ===================== PINOS =====================

#define UP     D6
#define DOWN   D7
#define OK     D8
#define BACK   D3
#define BUZZER D5

// ===================== PARTITURA =====================

#define STAFF_TOP 20
#define STAFF_SPACING 6
#define NOTE_STEP (STAFF_SPACING / 2)
#define NOTA_CENTRO_Y 6 

// ===================== DISPLAY =====================

Adafruit_SSD1306 display(128, 64, &Wire, -1);




//====================== FUNÇÕES DE NAVEGAÇÃO ============================

void MenuPrincipal(Musica *mu) {
  int opcao = 0;

  while (digitalRead(OK) == LOW) {

    if (digitalRead(UP) == LOW) {
      opcao = 0;
      delay(200);
    }
    else if (digitalRead(DOWN) == LOW) {
      opcao = 1;
      delay(200);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println(F("======= MENU ======="));
    display.println();

    display.print(opcao == 0 ? "> " : "  ");
    display.println(F("Criar musica"));

    display.print(opcao == 1 ? "> " : "  ");
    display.println(F("Biblioteca"));

    display.display();
    delay(1);
  }
  delay(300);

  if(opcao == 0){
    CriarMusica(mu);
  }
}


void SubMenuMusica(Musica *mu) {
  int opcao = 0;

  while (digitalRead(OK) == LOW) {

    if (digitalRead(UP) == LOW) {
      opcao = 0;
      delay(200);
    }
    else if (digitalRead(DOWN) == LOW) {
      opcao = 1;
      delay(200);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println(F("====== SUBMENU ======"));
    display.println();

    display.print(opcao == 0 ? "> " : "  ");
    display.println(F("Adicionar Nota"));

    display.print(opcao == 1 ? "> " : "  ");
    display.println(F("Finalizar Musica"));

    display.display();
    delay(1);
  }
  delay(300);

  if(opcao == 1){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 28);
    display.println(F("MUSICA ADICIONADA"));
    display.display();
    delay(2000);
    MenuPrincipal(mu);
  }
}

//================= FUNÇÕES DE ESCRITA =====================

void CriarMusica(Musica *mu) {
  mu->inicio = NULL;
  mu->tam = 0;

  int contador = 0; 

  delay(200);

  while (digitalRead(OK) == LOW) {

    if (digitalRead(UP) == HIGH) {
      contador++;
      if (contador > 14) {
        contador = 14;
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.print(F("O bpm deve estar entre 20-200"));
          display.display();
          tone(BUZZER, NOTE_C4);
          delay(1000); 
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
          display.print(F("O bpm deve estar entre 20-200"));
          display.display();
          tone(BUZZER, NOTE_C4);
          delay(1000);
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
  delay(200);
  mu->bpm = (contador * 10) + 60;
  SubMenuMusica(mu);
}

// ===================== SETUP / LOOP =====================

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}


void loop() {
  Musica mu;
  MenuPrincipal(&mu);
  

}
