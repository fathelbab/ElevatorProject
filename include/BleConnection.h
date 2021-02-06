#ifndef BLE_VS_H
#define BLE_VS_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <bitset>
#include "config.h"


class _BleConnection: public BLEServerCallbacks, public BLECharacteristicCallbacks {
    public:
        /*this function is responsible of initializing BLE*/
        void initialize();
        void notify();
        void setBleFlag(uint8_t flag, bool status);
        bool getBleFlag(uint8_t flag);
    private:
        std::bitset<8> bleFlag;
        /*@OVERRIDE function is responsible for burning on flash the new config data sent from ble write*/
        void onWrite(BLECharacteristic *pCharacteristic);
        /*@OVERRIDE function responsible for ble connect-animation while connected to the ble*/
        void onConnect(BLEServer* pServer);
        /*@OVERRIDE function is responsible for end ble connect-animation on disconnect from ble */
        void onDisconnect(BLEServer* pServer) ;
};
extern _BleConnection BleConnection;

#endif