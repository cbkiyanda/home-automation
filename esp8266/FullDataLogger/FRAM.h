

#ifndef FRAM_h
#define FRAM_h

#define FREEBYTEPTR 0x02
#define TIMEDUMPPTR 0x04
#define MINDATAPTR  0x20
/*****************************************************
 * MEMORY MAP (all in whole bytes)
 * 
 * 0x00-0x01 (2) - address of first data byte (0x0020)
 * 0x02-0x03 (2) - address of first free byte
 * 0x04-0x08 (4) - unixtime of last data dump
 * 0x08-0x1f ()  - reserved for future
 *  
 * Then there are a bunch of records following
 * 
 * Record format:
 * (time_t)unixtime - (float)lux - (float)pressure - (float)temp
 *  (unsigned long)
 * 
 *****************************************************/

union addressU {
  uint16_t address;
  uint8_t  bytes[2];
};

union unixtimeU {
  time_t  unixtime;
  uint8_t bytes[sizeof(time_t)]; // 4
};

typedef struct {
  time_t unixtime;
  float lux;
  float pressure;
  float temp;
} datarecord;

union datarecordU {
  datarecord data;
  uint8_t bytes[sizeof(datarecord)];
};




void setup_FRAM(Adafruit_FRAM_I2C *fram, bool quiet=false){
  if (fram->begin(0x50)) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C FRAM");
  } else {
    Serial.println("No I2C FRAM found \r\n");
    while (1);
  } 
}

/* return the next address for a write, this is bytes
 * 0x02-0x03 from the map
 */
uint16_t getWriteAddress(Adafruit_FRAM_I2C *fram)
{
  addressU addr;
  addr.bytes[1] = fram->read8(FREEBYTEPTR);
  addr.bytes[0] = fram->read8(FREEBYTEPTR+1);
  if (addr.address < MINDATAPTR)
    addr.address = MINDATAPTR;
  return addr.address;
}

uint16_t setWriteAddress(Adafruit_FRAM_I2C *fram, uint16_t addr_in)
{
  addressU addr;
  addr.address = addr_in;
  fram->write8(FREEBYTEPTR, addr.bytes[1]);
  fram->write8(FREEBYTEPTR+1, addr.bytes[0]);
  return addr.address;
}

/* return the last time that the FRAM was dumped
 *  
 */
time_t getLastDumpTime(Adafruit_FRAM_I2C *fram)
{
  unixtimeU tm;
  tm.bytes[0] = fram->read8(TIMEDUMPPTR);
  tm.bytes[1] = fram->read8(TIMEDUMPPTR+1);
  tm.bytes[2] = fram->read8(TIMEDUMPPTR+2);
  tm.bytes[3] = fram->read8(TIMEDUMPPTR+3);
  return tm.unixtime;
}

/* write the current time to the FRAM as the dump time
 *  then return the same time
 */
time_t writeFRAMDumpTime(Adafruit_FRAM_I2C *fram, time_t time_in) 
{
  unixtimeU tm;
  tm.unixtime = time_in;
  for (uint8_t i=0; i<sizeof(time_t);i++) { // sizeof(time_t)=4
    fram->write8(TIMEDUMPPTR+i, tm.bytes[i]);
  }
  return tm.unixtime;
}

/* given a datarecord struct input write this to the FRAM at the
 *  right spot, return the number of bytes written
 */
uint16_t writeDatarecord(Adafruit_FRAM_I2C *fram, datarecord *data)
{
  uint16_t i;
  // first where do we write it?
  uint16_t addr = getWriteAddress(fram);
  Serial.print("write address: "); Serial.println(addr, HEX);
  // change from the strcut to the union
  datarecordU datau;
  datau.data = *data;
  for (i=0; i<sizeof(datarecord);i++) { // sizeof(time_t)=4
    fram->write8(addr+i, datau.bytes[i]);
  }
  // update the last data pointer
  setWriteAddress(fram, addr+sizeof(datarecord));
  return i;
}
/*
 * get the last data record and return it in data2
 * the return value is the number of bytes read
 * if we have gotten all the data the unixtime is set to 0
 */
datarecord getDatarecord(Adafruit_FRAM_I2C *fram) //, datarecord *data_out) {
{
  datarecordU data_out;
  // first where do we write it?
  uint16_t addr = getWriteAddress(fram);
  // from here we subtract the size and read
  addr -= sizeof(datarecord);
  Serial.print("read address: "); Serial.println(addr, HEX);
  if (addr < 0x0020) {
    // no more data to give back
    data_out.data.unixtime = 0;
    return(data_out.data);
  }
//  datau.data.unixtime = data_out->unixtime;
//  datau.data.lux = data_out->lux;
//  datau.data.pressure = data_out->pressure;
//  datau.data.temp = data_out->temp;
  
  for (uint16_t i=0; i<sizeof(datarecord);i++) { // sizeof(time_t)=4
    data_out.bytes[i] = fram->read8(addr+i);
  }
  return(data_out.data);  
}





#endif



