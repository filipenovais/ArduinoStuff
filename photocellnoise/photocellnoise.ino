
int photocellPin = 0;
int photocellReading;     
int buzzer = 9;

void setup(void) {
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     
  
  if(photocellReading < 50){
    noTone(buzzer);
    delay(5000);
  }else{
    tone(buzzer, photocellReading*2.7);
  }
 
  delay(100);
}
