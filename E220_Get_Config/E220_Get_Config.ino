/*
 * LoRa E220 LLCC68
 * Get configuration.
 * https://mischianti.org
 *
 * 2024/5/10
 * 
 * update for ESP-WROOM-32D Hardware serial2
 *
 * E220       ----- ESP-WROOM-32D
 * M0         ----- GPIO25 (14)
 * M1         ----- GPIO26 (15)
 * RX         ----- GPIO17 (27) U2TXD
 * TX         ----- GPIO16 (25) U2RXD
 * AUX        ----- GPIO27 (16)
 * VCC        ----- 3.3v
 * GND        ----- GND
 *
 */

#include "EByte_LoRa_E220_library.h"

#define E220_M0     14
#define E220_M1     15
#define E220_AUX    16

// ---------- esp8266 pins --------------
//LoRa_E220 e220ttl(RX, TX, AUX, M0, M1);  // Arduino RX <-- e220 TX, Arduino TX --> e220 RX
//LoRa_E220 e220ttl(D3, D4, D5, D7, D6); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX AUX M0 M1
// LoRa_E220 e220ttl(D7, D8); // Config without connect AUX and M0 M1
 
// #include <SoftwareSerial.h>
// SoftwareSerial mySerial(D7, D8); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX
// LoRa_E220 e220ttl(&mySerial); // no AUX M0 M1
//LoRa_E220 e220ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------
 
// ------------- Arduino MKR WiFi 1010 -------------
// LoRa_E220 e220ttl(&Serial1, 2, 4, 6); //  RX AUX M0 M1
// -------------------------------------------------
 
// ---------- esp32 pins --------------
LoRa_E220 e220ttl(&Serial2, E220_AUX, E220_M0, E220_M1); //  RX AUX M0 M1
 
//LoRa_E220 e220ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e220 TX, esp32 TX --> e220 RX AUX M0 M1
// -------------------------------------
 
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
 
void setup() {
    Serial.begin(9600);
    while(!Serial){};
    delay(500);
 
    Serial.println();
    Serial.println("Start config"); 
 
    // Startup all pins and UART
    e220ttl.begin();
 
    ResponseStructContainer c;
    c = e220ttl.getConfiguration();
    // It's important get configuration pointer before all other operation
    Configuration configuration = *(Configuration*) c.data;
    Serial.println(c.status.getResponseDescription());
    Serial.println(c.status.code);
 
    printParameters(configuration);
 
    ResponseStructContainer cMi;
    cMi = e220ttl.getModuleInformation();
    // It's important get information pointer before all other operation
    ModuleInformation mi = *(ModuleInformation*)cMi.data;
 
    Serial.println(cMi.status.getResponseDescription());
    Serial.println(cMi.status.code);
 
    printModuleInformation(mi);
    c.close();
}
 
void loop() {
 
}
void printParameters(struct Configuration configuration) {
    Serial.println("----------------------------------------");
 
    Serial.print(F("HEAD : "));  Serial.print(configuration.COMMAND, HEX);Serial.print(" ");Serial.print(configuration.STARTING_ADDRESS, HEX);Serial.print(" ");Serial.println(configuration.LENGHT, HEX);
    Serial.println(F(" "));
    Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, HEX);
    Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, HEX);
    Serial.println(F(" "));
    Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUARTDatte     : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRateDescription());
    Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRateDescription());
    Serial.println(F(" "));
    Serial.print(F("OptionSubPacketSett: "));  Serial.print(configuration.OPTION.subPacketSetting, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getSubPacketSetting());
    Serial.print(F("OptionTranPower    : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
    Serial.print(F("OptionRSSIAmbientNo: "));  Serial.print(configuration.OPTION.RSSIAmbientNoise, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getRSSIAmbientNoiseEnable());
    Serial.println(F(" "));
    Serial.print(F("TransModeWORPeriod : "));  Serial.print(configuration.TRANSMISSION_MODE.WORPeriod, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getWORPeriodByParamsDescription());
    Serial.print(F("TransModeEnableLBT : "));  Serial.print(configuration.TRANSMISSION_MODE.enableLBT, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getLBTEnableByteDescription());
    Serial.print(F("TransModeEnableRSSI: "));  Serial.print(configuration.TRANSMISSION_MODE.enableRSSI, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getRSSIEnableByteDescription());
    Serial.print(F("TransModeFixedTrans: "));  Serial.print(configuration.TRANSMISSION_MODE.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getFixedTransmissionDescription());
 
 
    Serial.println("----------------------------------------");
}
void printModuleInformation(struct ModuleInformation moduleInformation) {
    Serial.println("----------------------------------------");
    Serial.print(F("HEAD: "));  Serial.print(moduleInformation.COMMAND, HEX);Serial.print(" ");Serial.print(moduleInformation.STARTING_ADDRESS, HEX);Serial.print(" ");Serial.println(moduleInformation.LENGHT, DEC);
 
    Serial.print(F("Model no.: "));  Serial.println(moduleInformation.model, HEX);
    Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
    Serial.println("----------------------------------------");
 
}