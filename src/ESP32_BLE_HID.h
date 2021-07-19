#pragma once

#if defined(PLATFORM_ESP32) && defined(BLE_HID_JOYSTICK)

#include <Arduino.h>
#include "targets.h"
#include <BleGamepad.h>

#include "CRSF.h"
extern CRSF crsf;

#define numOfButtons 0
#define numOfHatSwitches 0
#define enableX true
#define enableY true
#define enableZ false
#define enableRZ false
#define enableRX true
#define enableRY true
#define enableSlider1 true
#define enableSlider2 true
#define enableRudder true
#define enableThrottle true
#define enableAccelerator false
#define enableBrake false
#define enableSteering false

BleGamepad bleGamepad("ExpressLRS-Joystick", "ELRS", 100);

void BluetoothJoystickBegin()
{
    bleGamepad.setAutoReport(false);
    Serial.println("Starting BLE Joystick!");
    bleGamepad.setControllerType(CONTROLLER_TYPE_MULTI_AXIS);
    bleGamepad.begin(numOfButtons, numOfHatSwitches, enableX, enableY, enableZ, enableRZ, enableRX, enableRY, enableSlider1, enableSlider2, enableRudder, enableThrottle, enableAccelerator, enableBrake, enableSteering);
    bleGamepad.setAutoReport(false);   //This is true by default
}

void BluetoothJoystickSendReport()
{
    if (bleGamepad.isConnected())
    {
        bleGamepad.sendReport();
    }
}

void BluetoothJoystickUpdateValues()
{
    if (bleGamepad.isConnected())
    {
        // Serial.println("crsf update ble values");
        int16_t data[sizeof(crsf.ChannelDataIn)] = {0};

        for (uint8_t i = 0; i < 9; i++)
        {
            data[i] = map(crsf.ChannelDataIn[i], CRSF_CHANNEL_VALUE_MIN - 1, CRSF_CHANNEL_VALUE_MAX + 1, -32768, 32768);
        }

        bleGamepad.setX(data[0]);
        bleGamepad.setY(-data[1]);
        bleGamepad.setRudder(data[2]);
        bleGamepad.setThrottle(data[3]);
        bleGamepad.setSlider1(data[4]);
        bleGamepad.setSlider2(data[5]);
        bleGamepad.setRX(data[6]);
        bleGamepad.setRY(data[7]);
    }
    // process 
}

#endif