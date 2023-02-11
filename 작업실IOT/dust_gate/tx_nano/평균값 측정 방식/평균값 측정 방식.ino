

#define ITERATIONS 300    //Number of itterations to measure for current
#define inputPin A2       //ACS712 아날로그 인풋 핀
#define relayPin 7        //릴레이 아웃풋 핀
#define sensorType 20     //Specifies the A that the sensor is rated for

float highPeak,lowPeak,sensorPrecision;
float value_PeakToPeak, value_RMS;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;


const long interval = 5000;   //5초 인터벌 

void setup() 
{
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  
  sensorPrecision = 1024.0 / (sensorType * 1000.0);
}

void loop() 
{
  measure();
  value_RMS = value_PeakToPeak * 0.3536 * sensorPrecision;     

//alue_PeakToPeak는 높은 값과 낮은 값의 차이*0.3536
//rms값을 확인 


  Serial.print(sensorPrecision);
  Serial.print("\t");
  Serial.print(value_RMS);
  Serial.print("\t");
  Serial.println(value_PeakToPeak);
  if (value_RMS > 0.2) {
    digitalWrite(relayPin, LOW);  //전류 값이 낮아 작동 안함
    previousMillis = millis();
  } else {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(relayPin, HIGH); //작동 함. 
    }
  }
  delay(200);
}

void measure()
{     
  int cnt;
  //우리는 먼저 높은 피크가 0이고 낮은 피크가 1024라고 가정합니다.
  highPeak = 0;
  lowPeak = 1024;

  //loww 및 high peak 값 결정
  for (cnt = 0; cnt < ITERATIONS; cnt++) {    //반복 횟수  300번 반복 한다.       
    float sensorValue = analogRead(inputPin); //센서 값을 넣고 
    if(sensorValue > highPeak){               //센서 값이 highPeak값보다 높으면 
      highPeak = sensorValue; //센서 값을 하이피크(기본값 0) 값에 넣고           
    } else if(sensorValue < lowPeak) {  //그렇지 않다면 로우 피크값을 넣는다(lowPeak값은 0);
      lowPeak = sensorValue;  
    }
  }
  //하이 피크에서 로우 피크까지의 차이를 얻으십시오
  value_PeakToPeak = highPeak - lowPeak;   //가장 높은 피크 값과, 가장 낮은 피크의 차이 
  //550과 480정도의 차이가 될 것 같다. 70의 값
}
