#include "BleConnection.h"

void _BleConnection::initialize(){
    /*Create the BLE Device*/
    BLEDevice::init(BLE_NAME);
    /*Create the BLE Server*/
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new _BleConnection()); // call backs to listen to BLE connect and disconnect
    /* Create the BLE Service*/
    BLEService *pService = pServer->createService(SERVICE_UUID);
    /*create the BLE characteristic*/
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
    pCharacteristic->setCallbacks(new _BleConnection()); //call back to listen to BLE write
    pCharacteristic->addDescriptor(new BLE2902());    //there was an error in notify "the attribute can't be found" before adding this line                              
    /*Start the service*/
    pService->start();
    /*start Advertising*/
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
}
void _BleConnection::notify(){

}
void _BleConnection::setBleFlag(uint8_t flag, bool status){
    bleFlag.set(flag, status);
}
bool _BleConnection::getBleFlag(uint8_t flag){
    return bleFlag.test(flag);
}
void _BleConnection::onWrite(BLECharacteristic* pCharacteristic){
    std::string value = pCharacteristic -> getValue();
    if(value.length() > 0){
        if (value == KEY) {
            digitalWrite(33, HIGH);
            delay(DELAY);
            digitalWrite(33, LOW);
        }
    }
}
void _BleConnection::onConnect(BLEServer* pServer){
    Serial.println("BLE CONNECTED");
}
void _BleConnection::onDisconnect(BLEServer* pServer){
    Serial.println("BLE DISCONNECTED");
}