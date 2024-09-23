#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <HTTPClient.h>

#include <ArduinoJson.h>

class ClientHandler
{
public:
ClientHandler();
String getQRcode(int amount, String content , String bankAccount, String bankCode,String userBankName, String transType, String orderID, String terminalCode, String serviceCode, String additionalData);
String getRespone(String bankCode, String bankName, String bankAccount, String userBankName, String amount, String content, String qrCode, String imgId, int existing, String transactionId, String transactionRefId, String qrLink, String terminalCode, String serviceCode, String additionalData);
String getBalanceFlucs(String bankAccount, int amount, String timePaid, String transType, String referenceNumber, String orderId, String content, int status );
};


class Response
{
public:
Response();
    String extractQRCode(String dataResp);
};

class Amount
{
public:
Amount();
    String extractAmount(String dataBalance);
};
#endif
// String getQRcode(15000, NULL, NULL,int arg14,int arg5)
// {

// }

// String getAmount(string )  // amount":25000.0
// {
// //return  amount":25000.0
// }

// createQRMessage

// string  getQRfromRsp(string resp);

// 3- getAmount(string response)

// extern ClientHandler clientHandler;


// string reps =
// {
//   "bankCode": "MB",
//   "bankName": "MB Bank",
//   "bankAccount": "1234567890",
//   "userBankName": "XYZ Ltd",
//   "amount": "50000",
//   "content": "SampleTransactionDescription",
//   "qrCode": "00020101021138540010A00000072701240006970422011012345678900208QRIBFTTA53037045405200005802VN62350831SampleTransactionDescription6304AAB8",
//   "imgId": "abcd1234-5678-90ef-ghij-klmn01234567",
//   "existing": 1,
//   "transactionId": "",
//   "transactionRefId": "ABC1234567890XYZ",
//   "qrLink": "https://vietqr.vn/test/qr-generated?token=ABC1234567890XYZ ",
//   "terminalCode": "987",
//   "serviceCode": "SVC002",
//   "additionalData": [
//     {
//       "info": "AdditionalInfo1"
//     }
//   ]
// }
// string  getQRfromRsp(string resp)
// {

// }

// main"g
// string qrData =  client.getQRfromRsp(reps);
// serial.Print(qrData); // 00020101021138540010A00000072701240006970422011012345678900208QRIBFTTA53037045405200005802VN62350831SampleTransactionDescription6304AAB8 //

