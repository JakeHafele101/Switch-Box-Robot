const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState[8];         // variable for reading the pushbutton status

void setup() {  
  // initialize the pushbutton pin as an input:
  for(int i = 0; i < 8; i++){
    pinMode(i + 2, INPUT);
  } 
  Serial.begin(9600);
}

void loop(){
  // read the state of the pushbutton value:
  for(int i = 0; i < 8; i++){
    buttonState[i] = digitalRead(i + 2);
    Serial.print(buttonState[i]);
    Serial.print(" ");
  }
  Serial.println();
}
