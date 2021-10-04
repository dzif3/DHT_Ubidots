#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 4 // mendefinisikan pin dht di nodemcu adalah 4, D2 = 4
#define DHTTYPE DHT11 // mendefinisikan tipe dht yang kita gunakan

char auth[] = "BBFF-JNgd025H8fumhdQFOZzz2AVEkCaA23"; 
char ssid[] = "";
char pass[] = "apaaja123";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); // setting token client di ubidots
unsigned long last = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); // dht mulai membaca suhu dan kelembapan
  delay(20); // delay 0,02 detik
  client.wifiConnection(ssid,pass); // menyambungkan ubidots client dengan wifi

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-last>10000){ //jika sudah 10 detik
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("Kelembapan",hum); //ubidots client membaca kelembapan
    client.add("Temperature",temp); //ubidots client membaca suhu
    client.sendAll(true); // ubidots client mengirimkan semua data
    
    }

    

}
