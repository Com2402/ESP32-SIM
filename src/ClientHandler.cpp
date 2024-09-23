#include <ClientHandler.h>
#include <ArduinoJson.h>
ClientHandler::ClientHandler() {

}
Response::Response() {
    
}
Amount::Amount(){

}
String ClientHandler::getQRcode(int amount, String content , String bankAccount, String bankCode,String userBankName, String transType, String orderID, String terminalCode, String serviceCode, String additionalData) 
{
   {
    String dataContent = "";

    JsonDocument doc;

doc["amount"] = amount ;
if(content.length() == 0){
    doc["content"] = "NULL";
}else doc["content"] = content;
doc["bankAccount"] = bankAccount;
doc["bankCode"] = bankCode;
doc["userBankName"] = userBankName;
doc["transType"] = transType;
doc["orderID"] = orderID;
doc["terminalCode"] = terminalCode;
doc["serviceCode"] = serviceCode;
doc["additionalData"] = additionalData;
 
 serializeJson(doc, dataContent);
 return dataContent;
 }
}
String ClientHandler::getRespone(String bankCode, String bankName, String bankAccount, String userBankName, String amount, String content, String qrCode, String imgId, int existing, String transactionId, String transactionRefId, String qrLink, String terminalCode, String serviceCode, String additionalData)
{
   {
    String dataRespone = "";

    JsonDocument doc;

doc["bankCode"] = bankCode ;
doc["bankName"] = bankName ;
doc["bankAccount"] = bankAccount ;
doc["userBankName"] = userBankName ;
doc["amount"] = amount ;
doc["content"] = content ;
doc["qrCode"] = qrCode ;
doc["imgId"] = imgId ;
doc["existing"] = existing ;
if(transactionId.length() == 0){
    doc["transactionId"] = "NULL";
}else doc["transactionId"] = transactionId;
doc["transactionRefId"] = transactionRefId;
doc["qrLink"] = qrLink;
doc["terminalCode"] = terminalCode;
doc["serviceCode"] = serviceCode;
doc["additionalData"] = additionalData;
 
 serializeJson(doc, dataRespone);
 return dataRespone;
 }
}
String ClientHandler::getBalanceFlucs(String bankAccount, int amount, String timePaid, String transType, String referenceNumber, String orderId, String content, int status)
{
   {
    String dataBalance = "";

    JsonDocument doc;

doc["bankAccount"] = bankAccount ;
doc["amount"] = amount ;
doc["timePaid"] = timePaid ;
doc["transType"] = transType ;
doc["referenceNumber"] = referenceNumber ;
doc["orderId"] = orderId ;
doc["content"] = content ;
doc["status"] = status ;

 
 serializeJson(doc, dataBalance);
 return dataBalance;
 }
}
String Response::extractQRCode(String dataResp) {
    JsonDocument doc;
    deserializeJson(doc, dataResp);

    if (doc["qrCode"].is<String>()) {
        return doc["qrCode"].as<String>();
    } else {
        return "No QR Code found";
    }
}
String Amount::extractAmount(String dataBalance){
    JsonDocument doc;
    deserializeJson(doc, dataBalance);
    if(doc["amount"].is<int>()){
        return doc["amount"].as<String>();
    }else{
        return "No amount found";
    }
}