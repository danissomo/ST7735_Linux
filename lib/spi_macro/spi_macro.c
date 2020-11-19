//http://linux-sunxi.org/SPIdev#In_the_user_space
#include "spi_macro/spi_macro.h"

#include <fcntl.h>
#include <getopt.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>


char buf[10];
char buf2[10];
int com_serial;
int failcount;

struct spi_ioc_transfer xfer[2];

//////////
// Init SPIdev
//////////
int spi_init(char filename[40]) {
    int file;
    __u8 mode, lsb, bits;
    __u32 speed = 2500000;

    if ((file = open(filename, O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        com_serial = 0;
        exit(1);
    }

    if (ioctl(file, SPI_IOC_RD_MODE, &mode) < 0) {
        perror("SPI rd_mode");
        return -1;
    }
    if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
        perror("SPI rd_lsb_fist");
        return -1;
    }
    //sunxi supports only 8 bits

    if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, (__u8[1]){8}) < 0) {
        perror("can't set bits per word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("SPI bits_per_word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0) {
        perror("can't set max speed hz");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        perror("SPI max_speed_hz");
        return -1;
    }

    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n", filename, mode, bits, lsb ? "(lsb first) " : "", speed);

    //xfer[0].tx_buf = (unsigned long)buf;
    xfer[0].len = 3;                 /* Length of  command to write*/
    xfer[0].cs_change = 0;           /* Keep CS activated */
    xfer[0].delay_usecs = 0,         //delay in us
        xfer[0].speed_hz = 2500000,  //speed
        xfer[0].bits_per_word = 8,   // bites per word 8

        //xfer[1].rx_buf = (unsigned long) buf2;
        xfer[1].len = 4;   /* Length of Data to read */
    xfer[1].cs_change = 0; /* Keep CS activated */
    xfer[0].delay_usecs = 0;

    return file;
}

//////////
// Write buffer to spi
//////////
void spi_write(int file, uint8_t* bytes, int bufsize) {
    uint8_t buf[32];
    memcpy(buf, bytes, bufsize);
    xfer[0].rx_buf = (unsigned long long)buf;
    xfer[0].len = bufsize;
    int status = ioctl(file, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0) {
        perror("SPI_IOC_MESSAGE");
        return;
    }

    com_serial = 1;
    failcount = 0;
}