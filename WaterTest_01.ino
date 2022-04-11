int sensorPin=0; //identify analog pin

int moistureLevel, currentVal; //stores analog read


String dataLabel = "Moisture Monitor"; //Format CSV

bool header = true;//used to initialize the header

//float percent = 0.5;
//int threshold = 1024*percent; //within 5% change



//begin polling
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {

while(header != false){
  Serial.println(dataLabel);//creates header for CSV
  header = false;
}

moistureLevel = analogRead(sensorPin);
//assign first read for comparison
//currentVal = moistureLevel;

//checks if moisture is +/- 5% than previous poll - requires more testing
//if(moistureLevel >= currentVal || moistureLevel <= currentVal){

if(moistureLevel >= currentVal + 20 || moistureLevel <= currentVal - 20){
moistureLevel = analogRead(sensorPin);
Serial.print(moistureLevel);
Serial.println(",");
currentVal = moistureLevel;

}
currentVal = moistureLevel;
delay(5000);

//max ~400 (read in)
//min 0

  

}
