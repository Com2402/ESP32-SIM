#define TINY_GSM_MODEM_SIM7600
#define PPP_MODEM_RST     16
#define PPP_MODEM_RST_LOW false  
#define PPP_MODEM_TX      17
#define PPP_MODEM_RX      18
#define PPP_MODEM_RTS     -1
#define PPP_MODEM_CTS     -1
#define PPP_MODEM_FC      ESP_MODEM_FLOW_CONTROL_NONE
#define PPP_MODEM_MODEL   PPP_MODEM_SIM7600
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <HardwareSerial.h>
#include <TinyGsmClientSIM7600.h>
#include <ClientHandler.h>
#include <ArduinoJson.h>
#include "esp_mac.h"
ClientHandler clientHandler;
Response response;
Amount amount;
// void setup(){
//   Serial.begin(115200);
    
//   String qrCodeData = clientHandler.getQRcode(15000,"PaymentForOrder", "1234567890","MB", "ABC Corporation", "C", "ORD12345XYZ", "987", "SVC001","{\"info\":\"Dung\"}");
//   String dataResp = clientHandler.getRespone("MB","MB Bank", "1234567890","XYZ Ltd", "50000","SampleTransactionDescription","00020101021138540010A00000072701240006970422011012345678900208QRIBFTTA53037045405200005802VN62350831SampleTransactionDescription6304AAB8","abcd1234-5678-90ef-ghij-klmn01234567",1,String(0),"ABC1234567890XYZ","https://vietqr.vn/test/qr-generated?token=ABC1234567890XYZ","987","SVC002","{\"info\":\"Dung\"}");
//   String dataBalance = clientHandler.getBalanceFlucs("9690194300493", 25000, "18/09/2024 16:27:34", "C" ,String(0) ,"ORD12345XYXX", "VQR8e041a61d8 PaymentForOrder", 1);
//   //Serial.println(qrCodeData); 
//   String qrCode = response.extractQRCode(dataResp);
//   String amountout = amount.extractAmount(dataBalance);
//   // Serial.println(qrCode);
//   // Serial.println(amountout);
// }
// void loop(){

// }
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "DungUTC";
const char* mqttPassword = "Dungutc123*";
const char* topic = "vietqr/request/VVB409068";
const char apn[] = "v-internet"; 
const char gprsUser[] = "";     
const char gprsPass[] = ""; 
bool messageSent = false;
HardwareSerial mySerial(1);
TinyGsm modem(mySerial);
TinyGsmClient gsmClient(modem);
PubSubClient client(gsmClient);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void checkSimAndNetwork();
void setup() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, PPP_MODEM_RX, PPP_MODEM_TX);
  
  pinMode(PPP_MODEM_RST, OUTPUT);
  digitalWrite(PPP_MODEM_RST, LOW);  
  delay(100);
  digitalWrite(PPP_MODEM_RST, HIGH);
  String qrCodeData = clientHandler.getQRcode(15000,"PaymentForOrder", "1234567890","MB", "ABC Corporation", "C", "ORD12345XYZ", "987", "SVC001","[{\"info\":\"DungTest\"}]");
  // String dataResp = clientHandler.getRespone("MB","MB Bank", "1234567890","XYZ Ltd", "50000","SampleTransactionDescription","00020101021138540010A00000072701240006970422011012345678900208QRIBFTTA53037045405200005802VN62350831SampleTransactionDescription6304AAB8","abcd1234-5678-90ef-ghij-klmn01234567",1,String(0),"ABC1234567890XYZ","https://vietqr.vn/test/qr-generated?token=ABC1234567890XYZ","987","SVC002","{\"info\":\"Dung\"}");
  String dataBalance = clientHandler.getBalanceFlucs("9690194300493", 25000, "18/09/2024 16:27:34", "C" ,String(0) ,"ORD12345XYXX", "VQR8e041a61d8 PaymentForOrder", 1);
  // String qrCode = response.extractQRCode(dataResp);
  String amountout = amount.extractAmount(dataBalance);
  
  modem.restart();
  String modemInfo = modem.getModemInfo();
  Serial.println("Modem: " + modemInfo);
  if (modem.isNetworkConnected()) {
  Serial.println("Modem is connected to the network.");
} else {
  Serial.println("Modem is NOT connected to the network.");
}


if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
  Serial.println("Failed to connect to GPRS.");
} else {
  Serial.println("GPRS connected.");
  String localIP = modem.getLocalIP();
  Serial.print("Local IP: ");
  Serial.println(localIP);
}

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  client.setKeepAlive(120);
  reconnect();
  checkSimAndNetwork();
  if (client.publish(topic, qrCodeData.c_str(), false)) {
    Serial.println("Message published successfully");
} else {
    Serial.println("Message publish failed");
}
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientID =  "ESPClient-";
    clientID += String(random(0xffff),HEX);
    if (client.connect(clientID.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe("vietqr/response/VVB409068");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic); 
    JsonDocument doc;
    deserializeJson(doc, payload, length);
    if (doc["qrCode"].is<String>()) {
        String qrCode = doc["qrCode"].as<String>();
        
        Serial.println(qrCode);
    } else {
        Serial.println("No QR Code found");
    }
   
}

void publishMessage(const char* topic, String payload, boolean retained){
  
  if(client.publish(topic,payload.c_str(),true))
    Serial.println("Message published ["+String(topic)+"]: "+payload);
}
void checkSimAndNetwork() {
  if (modem.getSimStatus() != SIM_READY) {
    Serial.println("SIM card is not ready.");
    
    pinMode(PPP_MODEM_RST, OUTPUT);
    digitalWrite(PPP_MODEM_RST, LOW);
    delay(100);  
    digitalWrite(PPP_MODEM_RST, HIGH);
    delay(5000); 
    modem.restart();
    
    if (modem.gprsConnect(apn, gprsUser, gprsPass)) {
      Serial.println("Connected to network.");
    } else {
      Serial.println("Failed to connect to network.");
    }
  } else {
    Serial.println("SIM is ready.");
  }
}

void loop() {

  if (!modem.isNetworkConnected()) {
    Serial.println("Network disconnected. Checking SIM...");
    checkSimAndNetwork();
  }
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  


 
}
