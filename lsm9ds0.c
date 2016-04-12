/************
This is a library for the LSM9DS0.

Inspired by the adafruit library for the same breakout board for the Arduino.

Written by Alex Spitzer, Leo Mehr, Einar Veizaga for ECE 4760.
MIT License
************/
#include "lsm9ds0.h"
#include <plib.h>

unsigned int CS_G;
unsigned int CS_XM;

short igyro_x;
short igyro_y;
short igyro_z;

short iaccel_x;
short iaccel_y;
short iaccel_z;

float gyro_x;
float gyro_y;
float gyro_z;

float accel_x;
float accel_y;
float accel_z;

unsigned char buffer[6];

#define ACCEL_MG_LSB_2G 0.061f
#define GYRO_LSB_245DPS 0.00875f


void spi_write(unsigned int cs, unsigned char address, unsigned char value) {
    mPORTBClearBits(cs); // CS low
    while (TxBufFullSPI2()); // wait for ready

    putcSPI2(address);
    while(!SPI2STATbits.SPIRBF);
    ReadSPI2();
    putcSPI2(value);
    while(!SPI2STATbits.SPIRBF);
    ReadSPI2();

    while (SPI2STATbits.SPIBUSY); // wait for end of transaction
    mPORTBSetBits(cs); // CS high
}

char i;
void spi_read(unsigned int cs, unsigned char address, int n) {
    mPORTBClearBits(cs); // CS low
    while (TxBufFullSPI2()); // wait for ready

    putcSPI2(0b11000000 | address);
    while(!SPI2STATbits.SPIRBF);
    ReadSPI2();    // gets the contents of the SPIBUF register

    for (i = 0; i < n; i++) {
        SPI2BUF = 0x0;
        buffer[i] = getcSPI2();
    }

    while (SPI2STATbits.SPIBUSY); // wait for end of transaction
    mPORTBSetBits(cs); // CS high
}

void configure_accel() {
    spi_write(CS_XM, CTRL_REG1_XM, 0b01100111); // enable and set 100 Hz XYZ
}


void configure_gyro() {
    spi_write(CS_G, CTRL_REG1_G, 0x0F); // enable gyros and set normal mode

    // Enable on chip Gyro HIGH PASS FILTER... note that this causes lag
    //spi_write(CS_G, CTRL_REG2_G, 0b00000000);
    //spi_write(CS_G, CTRL_REG5_G, 0b00010001);
    // see page 41 in the lsm datasheet for more
}

void lsm9ds0_init(unsigned int cs_g, unsigned int cs_xm) {
    CS_G = cs_g;
    CS_XM = cs_xm;

    // Configure SPI 2 SDO (data in for lsm9ds0) pin 14
    PPSOutput(2, RPB5, SDO2);

    // Configure Chip Select for the XM (accel and mag)
    mPORTBSetPinsDigitalOut(CS_XM);
    mPORTBSetBits(CS_XM);

    // Configure Chip Select for the G (gyro)
    mPORTBSetPinsDigitalOut(CS_G);
    mPORTBSetBits(CS_G);

    // Configure SPI DATA in for XM
    PPSInput(3, SDI2, RPB13);

    // Open the LSM9DS0 SPI channel
    SpiChnOpen(2, SPI_OPEN_ON | SPI_OPEN_MODE8 | SPI_OPEN_MSTEN |
            SPI_OPEN_CKE_REV, 4);

    configure_accel();
    configure_gyro();
}

void lsm9ds0_update() {
    spi_read(CS_G, OUT_X_L_G, 6);

    igyro_x = buffer[1];
    igyro_x <<= 8;
    igyro_x |= buffer[0];
    igyro_y = buffer[3];
    igyro_y <<= 8;
    igyro_y |= buffer[2];
    igyro_z = buffer[5];
    igyro_z <<= 8;
    igyro_z |= buffer[4];

    spi_read(CS_XM, OUT_X_L_A, 6);

    iaccel_x = buffer[1];
    iaccel_x <<= 8;
    iaccel_x |= buffer[0];
    iaccel_y = buffer[3];
    iaccel_y <<= 8;
    iaccel_y |= buffer[2];
    iaccel_z = buffer[5];
    iaccel_z <<= 8;
    iaccel_z |= buffer[4];
}

char whoami(unsigned int cs, unsigned char reg) {
    spi_read(cs, reg, 1);
    return buffer[0];
}
char lsm9ds0_whoami_g() {
    return whoami(CS_G, WHO_AM_I_G);
}

char lsm9ds0_whoami_xm() {
    return whoami(CS_XM, WHO_AM_I_XM);
}

#define convert_accel(x) ( (x * ACCEL_MG_LSB_2G) / 1000 )
#define convert_gyro(x) ( (x * GYRO_LSB_245DPS) )

float get_accel_x() {
    return convert_accel(iaccel_x);
}

float get_accel_y() {
    return convert_accel(iaccel_y);
}

float get_accel_z() {
    return convert_accel(iaccel_z);
}

float get_gyro_x() {
    return convert_gyro(igyro_x);
}

float get_gyro_y() {
    return convert_gyro(igyro_y);
}

float get_gyro_z() {
    return convert_gyro(igyro_z);
}
