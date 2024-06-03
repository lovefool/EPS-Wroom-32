# E220(JP) ESP-Wroom-32 adapting E220-900T22S(JP) version

(1) New wire connetion to use HardwareSerial2 <br>
 To use SPI SD card, moved E220 wires.<br>
 * E220       ----- ESP-WROOM-32D
 * M0         ----- GPIO25 (14)
 * M1         ----- GPIO26 (15)
 * RX         ----- GPIO17 (27) U2TXD
 * TX         ----- GPIO16 (25) U2RXD
 * AUX        ----- GPIO27 (16)
 * VCC        ----- 3.3v
 * GND        ----- GND
 


