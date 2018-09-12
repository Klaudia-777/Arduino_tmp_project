
// Autorzy: Klaudia Bednarz, Klaudia Horyń

#include <Keypad.h>

int digitsCode[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int segmentsAddress[] = {0xFE, 0xFC, 0xFA, 0xF8, 0xF6, 0xF4, 0xF2, 0xF0};
int segmentDigits [] = {0, 0, 0, 0};
int timeToRemember[] = {0, 0, 0, 0};   //tablica przechoujaca czas po zatrzymaniu (przy kliknięciu B- ustawianie budzika)
int buzzerTime[] = {0, 0, 0, 0};       //tablica przechowująca ustawiony przez nas czas budzika

int currentlyChosedDigit = 0;

bool isCounting = true; //zmienna przechowujaca stan zegara (liczy w gore/nie liczy)
int pinA = 6;     //inicjalizacja segmentow i przypisanie im pinów
int pinB = 7;
int pinC = 8;
int pinD = 9;
int pinE = 10;
int pinF = 11;
int pinG = 12;

int D1 = 2;     //inicjalizacja wyświetlaczy i przypisanie im pinów
int D2 = 3;
int D3 = 4;
int D4 = 5;
int digits[4] = {D4, D3, D2, D1};

int tryb = 0;

const byte ROWS = 4; //"włączamy" 4 górne wiersze na płytce
const byte COLS = 2; //i 2 górne kolumny
char keys[ROWS][COLS] = {
  {'B', 'L'},
  {'\0', 'R'},
  {'\0', 'A'},
  {'\0', 'S'}
};

int buzzer = 19;  // pin odpowiedzialny za nasz budzik



byte rowPins[ROWS] = {15, 16, 17, 18};  //przypisanie pinów do naszych wierszy i kolumn
byte colPins[COLS] = {13, 14};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int timeToChange;

void setup() {
  // initialize the digital pins as outputs.
  Serial.begin(9600);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  timeToChange = millis();
}
//wyłączanie wszystkich wyświetlaczy

void offAll() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digits[i], HIGH);
  }
}

//włączanie wszystkich wyświetlaczy

void onAll() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digits[i], LOW);
  }
}

//ustawianie odpowiedniej cyfry na wyswietlaczu

void setChosenDigit(int x) {
  digitalWrite(digits[x - 1], LOW);
}

//  tym miejscu ustawiamy stany logiczne na pinach, by uzyskać odpowiednie cyfry

void setZero(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  delay(5);
}

void setOne(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  delay(5);
}
void setTwo(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  delay(5);
}
void setThree(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  delay(5);
}
void setFour(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  delay(5);
}

void setFive(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  delay(5);
}
void setSix(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  delay(5);
}
void setSeven(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  delay(5);
}

void setEight(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  delay(5);

}
void setNine(int x) {
  offAll();
  setChosenDigit(x);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  delay(5);
}


void countUp() {                    //odliczanie w górę - warunki na zerowanie sie kolejnych wyświetlaczy

  if (millis() - timeToChange >= 1000) {
    timeToChange = millis();
    segmentDigits[0]++;

    if (segmentDigits[0] == 10) {
      segmentDigits[0] = 0;
      segmentDigits[1]++;
    }
    if (segmentDigits[2] == 10) {
      segmentDigits[2] = 0;
      segmentDigits[3]++;
    }
    if (segmentDigits[1] == 6) {
      segmentDigits[1] = 0;
      segmentDigits[2]++;
    }
    if (segmentDigits[3] == 2 && segmentDigits[2] == 4) {
      segmentDigits[0] = 0;
      segmentDigits[1] = 0;
      segmentDigits[2] = 0;
      segmentDigits[3] = 0;

    }
  }
}

void setCurrentDigit(int digit, int number) {            //wrzucamy cyferki na wyświetlacze
  switch (number)
  { case 0:
      setZero(digit);
      break;

    case 1:
      setOne(digit);
      break;

    case 2:
      setTwo(digit);
      break;

    case 3:
      setThree(digit);
      break;

    case 4:
      setFour(digit);
      break;

    case 5:
      setFive(digit);
      break;

    case 6:
      setSix(digit);
      break;

    case 7:
      setSeven(digit);
      break;

    case 8:
      setEight(digit);
      break;

    case 9:
      setNine(digit);
      break;
  }
}



void user_input() {                         //liczenie w gore od ustawionej godziny
  char key = keypad.getKey();
  if (key != NO_KEY) {

    //warunki na korzystanie z odpowiednich przycisków na klawiaturze

    if (key == 'R') {                      //R - right przechodzimy o jeden wyświetlacz dalej w prawo
      digitalRead('R') == HIGH;
      currentlyChosedDigit--;
      if (currentlyChosedDigit < 0) currentlyChosedDigit = 3;
    }

    if (key == 'L') {                      // L - left przechodzimy o jeden wyświetlacz dalej w lewo
      digitalRead('L') == HIGH;
      currentlyChosedDigit++;
      if (currentlyChosedDigit > 3) currentlyChosedDigit = 0;
    }


    if (key == 'A' && !isCounting) {      //A - add, korzystamy tylko jesli zablokowane jest odliczanie w góre przez zegar, inkrementuje cyfry na wybranym wysietlaczu z kazdym kliknieciem o 1
      digitalRead('A') == HIGH;

      // warunki na zerowanie w zaleznosci od czasu wyswietlanego na wysietlaczach

      if (currentlyChosedDigit == 0) {
        segmentDigits[0]++;
        if (segmentDigits[0] == 10) {
          segmentDigits[0] = 0;
        }
      }


      if (currentlyChosedDigit == 1)
        segmentDigits[1]++;
      if (segmentDigits[1] == 6) {
        segmentDigits[1] = 0;
      }



      if (currentlyChosedDigit == 2) {
        segmentDigits[2]++;
        if (segmentDigits[2] == 4 && segmentDigits[3] == 2) {
          segmentDigits[2] = 0;
        }
        if (segmentDigits[2] == 10 && segmentDigits[3] == 1) {
          segmentDigits[2] = 0;
        }
        if (segmentDigits[2] == 10 && segmentDigits[3] == 0) {
          segmentDigits[2] = 0;
        }

      }


      if (currentlyChosedDigit == 3) {
        segmentDigits[3]++;
        if (segmentDigits[2] > 3) {
          if (segmentDigits[3] == 2) segmentDigits[3] = 0;
        }
        if (segmentDigits[3] == 3) segmentDigits[3] = 0;

      }

      setCurrentDigit(currentlyChosedDigit, segmentDigits[currentlyChosedDigit]);
    }
  }
  if (key == 'S') {                      //S-set, zatrzymuje i włącza odliczanie zegara
    digitalRead('S') == HIGH;
    isCounting = !isCounting;
  }

  if (key == 'B') {                       //B-buzzer, rzycisk odpowiedzialny za ustawienie budzika
    isCounting = !isCounting;
    switch (tryb) {
      case 0:
        for (int i = 0; i < 4; i++) {
          timeToRemember[i] = segmentDigits[i];
          segmentDigits[i] = buzzerTime[i];
        }
        tryb = 1;
        break;
      case 1:
        for (int i = 0; i < 4; i++) {
          buzzerTime[i] = segmentDigits[i];
          segmentDigits[i] = timeToRemember[i];

        }
        tryb = 0;
        break;
    }
  }


}


// funkcja porównująca 2 tablice

bool compare(int tab1[4], int tab2[4]) {
  for (int i = 0; i < 4; i++) {
    if (tab1[i] != tab2[i]) return false;
  }
  return true;
}



void loop() {                        //głowna pętla programu, wykonuje się ciągle po wgraniu na płytkę
  for (int i = 1; i < 5; i++) {
    setCurrentDigit(i, segmentDigits[i - 1]);
  }
  if (compare(segmentDigits, buzzerTime) && isCounting) digitalWrite(buzzer, HIGH);
  else {
    digitalWrite(buzzer, LOW);
  }
  if (isCounting)countUp();
  user_input();




}
