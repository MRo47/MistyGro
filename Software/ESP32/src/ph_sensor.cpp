#include "ph_sensor.h"

PHSensor::PHSensor(int temp_pin, int ph_pin, int power_pin)
    : temp_pin_(temp_pin), ph_pin_(ph_pin), power_pin_(power_pin),
      ph_(7.0),
      voltage_(1500.0),
      temp_(25.0),
    //   ph_calib_data_{2032.44, //buffer soln 4.0 at 25C
    //                  1500.0}, //buffer soln 7.0 at 25C
      eeprom(CustomEEPROM::getInstance()){}  

void PHSensor::begin()
{
    pinMode(temp_pin_, INPUT);
    pinMode(ph_pin_, INPUT);
    pinMode(power_pin_, OUTPUT);

    PhData temp_data = eeprom.getPhCalib();

    if (isnan (temp_data.ph4_v)
        || isnan(temp_data.ph7_v))
    {
        temp_data = {2032.44, //buffer soln 4.0 at 25C
                     constants::ph7_volt_at_25C}; //buffer soln 7.0 at 25C
        Serial.println("saving");
        eeprom.savePhCalib(temp_data);
    }
    Serial.println("ph_data: ph4_v, ph7_v: " + String(temp_data.ph4_v) +
                   " " + String(temp_data.ph7_v));

    float m_ = 3.0 / ((temp_data.ph7_v - constants::ph7_volt_at_25C) / 3.0 -
                      (temp_data.ph4_v - constants::ph7_volt_at_25C) / 3.0);

    float c_ = 7.0 - m_ * (temp_data.ph7_v - constants::ph7_volt_at_25C) / 3.0;
}

float PHSensor::read()
{
    return m_ * (voltage_ - constants::ph7_volt_at_25C) / 3.0 + c_; //y = mx + c;
}

void PHSensor::calibration()
{
    float volt = analogRead(ph_pin_);

}

boolean DFRobot_ESP_PH_WITH_ADC::cmdSerialDataAvailable()
{
    char cmdReceivedChar;
    static unsigned long cmdReceivedTimeOut = millis();
    while (Serial.available() > 0)
    {
        if (millis() - cmdReceivedTimeOut > 500U)
        {
            this->_cmdReceivedBufferIndex = 0;
            memset(this->_cmdReceivedBuffer, 0, (ReceivedBufferLength));
        }
        cmdReceivedTimeOut = millis();
        cmdReceivedChar = Serial.read();
        if (cmdReceivedChar == '\n' || this->_cmdReceivedBufferIndex == ReceivedBufferLength - 1)
        {
            this->_cmdReceivedBufferIndex = 0;
            strupr(this->_cmdReceivedBuffer);
            return true;
        }
        else
        {
            this->_cmdReceivedBuffer[this->_cmdReceivedBufferIndex] = cmdReceivedChar;
            this->_cmdReceivedBufferIndex++;
        }
    }
    return false;
}

byte DFRobot_ESP_PH_WITH_ADC::cmdParse(const char *cmd)
{
    byte modeIndex = 0;
    if (strstr(cmd, "ENTERPH") != NULL)
    {
        modeIndex = 1;
    }
    else if (strstr(cmd, "EXITPH") != NULL)
    {
        modeIndex = 3;
    }
    else if (strstr(cmd, "CALPH") != NULL)
    {
        modeIndex = 2;
    }
    return modeIndex;
}

byte DFRobot_ESP_PH_WITH_ADC::cmdParse()
{
    byte modeIndex = 0;
    if (strstr(this->_cmdReceivedBuffer, "ENTERPH") != NULL)
    {
        modeIndex = 1;
    }
    else if (strstr(this->_cmdReceivedBuffer, "EXITPH") != NULL)
    {
        modeIndex = 3;
    }
    else if (strstr(this->_cmdReceivedBuffer, "CALPH") != NULL)
    {
        modeIndex = 2;
    }
    return modeIndex;
}

void DFRobot_ESP_PH_WITH_ADC::phCalibration(byte mode)
{
    char *receivedBufferPtr;
    static boolean phCalibrationFinish = 0;
    static boolean enterCalibrationFlag = 0;
    switch (mode)
    {
    case 0:
        if (enterCalibrationFlag)
        {
            Serial.println(F(">>>Command Error<<<"));
        }
        break;

    case 1:
        enterCalibrationFlag = 1;
        phCalibrationFinish = 0;
        Serial.println();
        Serial.println(F(">>>Enter PH Calibration Mode<<<"));
        Serial.println(F(">>>Please put the probe into the 4.0 or 7.0 standard buffer solution<<<"));
        Serial.println();
        break;

    case 2:
        if (enterCalibrationFlag)
        {
            // buffer solution:7.0
            // 7795 to 1250
            if ((this->_voltage > PH_VOLTAGE_NEUTRAL_LOW_LIMIT) && (this->_voltage < PH_VOLTAGE_NEUTRAL_HIGH_LIMIT))
            {
                Serial.println();
                Serial.print(F(">>>Buffer Solution:7.0"));
                this->_neutralVoltage = this->_voltage;
                Serial.println(F(",Send EXITPH to Save and Exit<<<"));
                Serial.println();
                phCalibrationFinish = 1;
            }
            //buffer solution:4.0
            //1180 to 1700
            else if ((this->_voltage > PH_VOLTAGE_ACID_LOW_LIMIT) && (this->_voltage < PH_VOLTAGE_ACID_HIGH_LIMIT))
            {
                Serial.println();
                Serial.print(F(">>>Buffer Solution:4.0"));
                this->_acidVoltage = this->_voltage;
                Serial.println(F(",Send EXITPH to Save and Exit<<<"));
                Serial.println();
                phCalibrationFinish = 1;
            }
            else
            {
                Serial.println();
                Serial.print(F(">>>Buffer Solution Error Try Again<<<"));
                Serial.println(); // not buffer solution or faulty operation
                phCalibrationFinish = 0;
            }
        }
        break;

    case 3: //store calibration value in eeprom
        if (enterCalibrationFlag)
        {
            Serial.println();
            if (phCalibrationFinish)
            {
                // buffer solution:7.0
                // 7795 to 1250
                if ((this->_voltage > PH_VOLTAGE_NEUTRAL_LOW_LIMIT) && (this->_voltage < PH_VOLTAGE_NEUTRAL_HIGH_LIMIT))
                {
                    EEPROM.writeFloat(this->_eepromStartAddress, this->_neutralVoltage);
                    EEPROM.commit();
                }
                //buffer solution:4.0
                //1180 to 1700
                else if ((this->_voltage > PH_VOLTAGE_ACID_LOW_LIMIT) && (this->_voltage < PH_VOLTAGE_ACID_HIGH_LIMIT))
                {
                    EEPROM.writeFloat(this->_eepromStartAddress + (int)sizeof(float), this->_acidVoltage);
                    EEPROM.commit();
                }
                Serial.print(F(">>>Calibration Successful"));
            }
            else
            {
                Serial.print(F(">>>Calibration Failed"));
            }
            Serial.println(F(",Exit PH Calibration Mode<<<"));
            Serial.println();
            phCalibrationFinish = 0;
            enterCalibrationFlag = 0;
        }
        break;
    }
}
