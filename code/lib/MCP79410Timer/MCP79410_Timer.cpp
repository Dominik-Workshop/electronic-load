#include "MCP79410_Timer.h"

// constructor
MCP79410_Timer::MCP79410_Timer(byte rtcAddress){
  _rtcAddress = rtcAddress;
  Wire.begin();
}

MCP79410_Timer::MCP79410_Timer(void){
  _rtcAddress = 0x6f;
  Wire.begin();
}


void MCP79410_Timer::start(){
  // get the seconds byte form RTC
  byte secondsByte = _getRtcData(0, 8);
  // bitwise OR between seconds byte and 1000 0000
  // sets the first bit to 1 and leave the remaining 7 bits untouched
  secondsByte = secondsByte | 0x80;
  // write the updated byte back to the RTC
  _writeRtcByte(0, secondsByte);
  // set the state = 1 to indicate the clock is running
  _rtcState = 1;
}

void MCP79410_Timer::stop(){
  // get the seconds byte form RTC
  byte secondsByte = _getRtcData(0, 8); // get the seconds byte form RTC
  // bitwise AND between seconds byte and 0111 1111
  // sets the first bit to 0 and leave the remaining 7 bits untouched
  secondsByte = secondsByte & 0x7f;
  _writeRtcByte(0, secondsByte);
  // set the state = 2 to indicate the clock is stopped
  _rtcState = 2;
}

void MCP79410_Timer::reset(){
  // always force a the timer to stop before a reset
  _writeRtcByte(0,0x00);     //SECOND=0 and Clock Stopped
  _writeRtcByte(1,0x00);    //MINUTE=00
  _writeRtcByte(2,0x00);    //HOUR=00
  // set the state = 2 to indicate the clock is reset & stopped
  _rtcState = 0;
}

int MCP79410_Timer::status(){
  return _rtcState;
}

uint32_t MCP79410_Timer::getTotalSeconds(){
  uint32_t hours = _makeDec(_getRtcData(2, 6)) * 60 * 60;   //convert hours to seconds
  uint16_t mins = _makeDec(_getRtcData(1, 7)) * 60;         //convert minutes to seconds
  uint8_t secs = _makeDec(_getRtcData(0,7));                //seconds
  uint32_t dateAsSeconds = hours + mins + secs;             //calculate total seconds
  return dateAsSeconds;                                     //return with total seconds
}

uint8_t MCP79410_Timer::hours() {
    return _makeDec(_getRtcData(2,6));
}

uint8_t MCP79410_Timer::minutes() {
  return _makeDec(_getRtcData(1,7));
}

uint8_t MCP79410_Timer::seconds(){
  return _makeDec(_getRtcData(0,7));
}

String MCP79410_Timer::getTime(){
  return _format2digit(_getRtcData(2,6)) + ":" +
         _format2digit(_getRtcData(1,7)) + ":" +
         _format2digit(_getRtcData(0,7));
}


// NOVÉ METÓDY PRE BATTERY MODE SE SEKUNDOVÝM IMPULZOM
void MCP79410_Timer::startBatteryTimer() {
    // Zapni oscilátor v RTC
    start();  // <- toto volá pôvodnú metódu, ktorá zapíše bit 0x80 do sekúnd

    _batteryTimerRunning = true;
    _lastRtcSecond = seconds(); // inicializácia na aktuálnu sekundu
}

void MCP79410_Timer::stopBatteryTimer() {
    stop(); // <- vypne oscilátor v RTC
    _batteryTimerRunning = false;
}

void MCP79410_Timer::resetBatteryTimer() {
    reset(); // <- vynuluje registre RTC na 00:00:00 a vypne oscilátor
    _batterySeconds = 0;
    _batteryTimerRunning = false;
    _lastRtcSecond = 0;
}

void MCP79410_Timer::updateBatteryTimer() {
    if (!_batteryTimerRunning)
        return;

    uint8_t currentSecond = seconds();

    // keď sa RTC sekunda zmení, pridaj do počítadla
    if (currentSecond != _lastRtcSecond) {
        // Pozor na prechod z 59 → 00
        if ((currentSecond == 0 && _lastRtcSecond == 59) || currentSecond > _lastRtcSecond) {
            _batterySeconds++;
        }
        _lastRtcSecond = currentSecond;
    }
}


uint32_t MCP79410_Timer::getBatterySeconds() {
    return _batterySeconds;
}

String MCP79410_Timer::getBatteryTime() {
    uint32_t totalSeconds = _batterySeconds;
    uint32_t hours = totalSeconds / 3600;
    uint32_t remainingSeconds = totalSeconds % 3600;
    uint8_t minutes = remainingSeconds / 60;
    uint8_t seconds = remainingSeconds % 60;
    
    //max time 999:59:59
    char timeString[12];
    sprintf(timeString, "%3lu:%02d:%02d", hours, minutes, seconds);
    return String(timeString);

}

bool MCP79410_Timer::isBatteryTimerRunning() {
    return _batteryTimerRunning;
}


//Read RTC Byte
unsigned char MCP79410_Timer::_readRtcByte(const unsigned char adr){
  unsigned char data;
  Wire.beginTransmission(0x6f);
  Wire.write(adr);
  Wire.endTransmission();
  Wire.requestFrom(0x6f,1);
  while (Wire.available()) data=Wire.read();
  return data;
}

//Write to RTC
void MCP79410_Timer::_writeRtcByte(const unsigned char adr, const unsigned char data){
  Wire.beginTransmission(0x6f);
  Wire.write(adr);
  Wire.write(data);
  Wire.endTransmission();
}

//convert to decimal
uint8_t MCP79410_Timer::_makeDec(uint8_t num){
    uint8_t units = num & 0x0F;
    uint8_t tens = num >> 4;
    return tens*10 + units;
}

uint8_t MCP79410_Timer::_makeHex(uint8_t num){
  uint8_t units = num % 10;
  uint8_t tens = num / 10;
  return (tens << 4) | units;
}

unsigned char MCP79410_Timer::_getRtcData(const unsigned char adr, const unsigned char validbits){
  unsigned char data;
  data=_readRtcByte(adr);
  data=data & 0xff>>(8-validbits);
  return data;
}

String MCP79410_Timer::_format2digit(unsigned char data){
  uint8_t units = data & 0x0f;
  uint8_t tens = data >> 4;
  return String(tens) + String(units);
}