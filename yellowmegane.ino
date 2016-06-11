//LED Sunglasses with ATTINY85
//Akaki Kuumeri

#define BPM 500 //beat of music for the musical mode

//Pin connected to SH_CP of 74HC595
int clockPin = 0;
////Pin connected to DS of 74HC595
int dataPin = 1;

int led1 = 3;
int led2 = 4;

int mode = 6;
int maxmode = 14;

int i = 0;

int peak1 = 1;
int peak2 = 1;//for mode 11
int volume = 0;
int volume2 = 0;

void setup() {
  //set pins to output so you can control the shift register
  //pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  //digitalWrite(led1, HIGH);
  //digitalWrite(led2, HIGH);
  
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  if (digitalRead(2) == LOW) {
    mode++;
    if (mode > maxmode) mode = 0;
    delay(200);
  }
  i++;
  switch (mode) {
    case 0:
    {
      if (i >= 8) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(B00001111<<i | B00001111 >> 8-i);
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM/8);
    }
    break;
  
  case 1:
    {
      if (i >= 8) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(B0001111>>i | B0001111 << 8-i);
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM/8);
    }
    break;
    
    case 2:
    { //gradient
    if (i >= 5) i = 0;
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      
      out(255<<i+2);
      
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delayMicroseconds(1+i*100);
    }
    break;
    
    case 3:
    {
      if (i >= 256) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(i);  
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(50);
    }break;
  
  case 4:
    {
      if (i >= 6) i = 0;
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      switch (i){
        case 0:
        {
          out(B00000111);
          digitalWrite(led1, LOW);
        }
        break;
        case 1:
        {
          out(B00111100);
          digitalWrite(led1, LOW);
        }
        break;
        case 2:
        {
          out(B11000000);
          digitalWrite(led1, LOW);
        }
        break;
        case 3:
        {
          out(B11000000);
          digitalWrite(led2, LOW);
        }
        break;
        case 4:
        {
          out(B00111100);
          digitalWrite(led2, LOW);
        }
        break;
        case 5:
        {
          out(B00000111);
          digitalWrite(led2, LOW);
        }
        break;
      }
    delay(BPM/8);
    }break;
    
    case 5://opposite flow
    {
      if (i >= 80) i = 0;
      int ii = i/10;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(B00000111<<ii | B00000111 >> 8-ii);
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      delay(1);
      digitalWrite(led1, HIGH);
      out(B00000111>>ii | B00000111 << 8-ii);
      
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(1);
    }
    break;
    
    case 6://strobo
    {
      if (i >= 2) i = 0;
      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(255);
      delay(BPM*0.9);//theoretically, 120 bpm
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM*0.1);
    }
    break;
    
    case 7://opposing flash
    {
      if (i >= 2) i = 0;
      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      // shift out the bits:
      out(255);
      delay(BPM/2);//theoretically, 120 bpm
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      // pause before next value:
      delay(BPM/2);
    }
    break;
    
    case 8://vertical opposing flash
    {
      if (i >= 2) i = 0;
      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      if (i == 0) {out(B00001111);}
      else {out(B11110000);}
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM/2);
    }
    break;
    
    case 9://slow fade
    {
      if (i >= 400) i = 0;
      int ii = (i > 200) ? 200-(i%200) : i;//reflect around if over half of the range of i.
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      out(B11111111);
      delayMicroseconds(ii*2+2);// add two because delay 0 causes problems
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delayMicroseconds(200-ii+2);//delayMicroseconds(abs(i-BPM));
    }
    break;
    
    case 10:
    {
      if (i >= 14) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      if (i < 8) {
        out(1<<i);
      } else {
        out(1<<14-i);
      }
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM/8);
    }
    break;
    
    case 11:
    {//curtains up and down and up and down
      if (i >= 16) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      if (i < 8) {
        out(~(255>>i));
      } else {
        out(~(255>>8-i));
      }
  
      //take the latch pin high so the LEDs will light up:
      //digitalWrite(latchPin, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      // pause before next value:
      delay(BPM/8);
    }
    break;
    
    case 12:
    {//curtains up and down and up and down
      if (i >= 32) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      if (i < 16) {
        
        if (i < 8) {
          out(~(255>>i));
        } else {
          out(~(255>>16-i));
        }
        digitalWrite(led1, LOW);
      } else {
        if (i-16 < 8) {
          out(~(255>>i-16));
        } else {
          out(~(255>>16-(i-16)));
        }
        digitalWrite(led2, LOW);
      }
      delay(BPM/16);
    }
    break;
    
    case 13:
    {//alternating winks
      if (i >= 16) i = 0;
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      if (i < 8) {
        
        if (i < 4) {
          out(B00001111>>(4-i) | B11110000<<(4-i));
        } else {
          out(B00001111<<(i) | B11110000>>(i));
        }
        digitalWrite(led1, LOW);
      } else {
        if (i-8 < 4) {
          out(B00001111>>(4-(i-8)) | B11110000<<4-(i-8));
        } else {
          out(B00001111<<((i-8))| B11110000>>((i-8)));
        }
        digitalWrite(led2, LOW);
      }
      delay(BPM/8);
    }
    break;
    
    case 14:
    {
      if (i >= BPM/30)
       {
         i = 0;
         volume = random(max(1,volume-4), min(volume+4,9));
         peak1 = max(peak1-1, volume+1);
         volume2 = random(max(1,volume2-4), min(volume2+4,9));
         peak2 = max(peak2-1, volume2+1);
       }
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      // shift out the bits:
      
      out((255>>8-volume) | 1 << peak1);
      digitalWrite(led1, LOW);
      delay(1);
      digitalWrite(led1, HIGH);
      
      
      out((255>>8-volume) | 1 << peak2);
      digitalWrite(led2, LOW);
      delay(1);
      
      digitalWrite(led2, HIGH);
      // pause before next value:
      
    }
    break;
  }
}

void out(byte a) {
  shiftOut(dataPin, clockPin, MSBFIRST, ~(a >> 7 | a << 1));//one bit looped around to the other end, and inverted
}  
