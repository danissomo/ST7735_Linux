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

static const uint8_t     spiBPW   = 8 ;
static const uint16_t    spiDelay = 0 ;
static const unsigned int    spiSpeed = 30*2000000;
char buf[10];
char buf2[10];
int com_serial;
int failcount;

struct spi_ioc_transfer xfer[2];


/**
 * init spidev
 * @filename path of spidev /dev/spidevA.B, A- spi line num, B- chipselect.
 * return value: file descriptor of spidev
**/
int spi_init(char filename[40]) {
    int file;
    __u8 mode, lsb, bits;
    __u32 speed = 160000;

    if ((file = open(filename, O_WRONLY)) < 0) {
        printf("Failed to open the bus.");
        com_serial = 0;
        exit(1);
    }
    if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0) {
        perror("can't set bits per word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed) < 0) {
        perror("can't set max speed hz");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("SPI bits_per_word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
            perror("SPI rd_lsb_fist");
            return -1;
    }
    
    if (ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        perror("SPI max_speed_hz");
        return -1;
    }
    
    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n", filename, mode, bits, lsb ? "(lsb first) " : "(msb first) ", speed);

    return file;
}


/**
 * Write buffer to spi
 * @file - spidev file descriptor
 * @bytes - data ptr
 * @bufsize - data length
**/
void spi_write(int file, uint8_t* bytes, int bufsize) {
    struct spi_ioc_transfer spi ;
    int bytes_one_time = 1024*4;
   memset (&spi, 0, sizeof (spi)) ;
    for(size_t i = 0; i < bufsize / bytes_one_time; i++){
        spi.tx_buf        = (unsigned long)(bytes+i*bytes_one_time) ;
        spi.rx_buf        = (unsigned long)NULL ;
        spi.len           = bytes_one_time;
        spi.delay_usecs   = spiDelay ;
        spi.speed_hz      = spiSpeed ;
        spi.bits_per_word = spiBPW ;
        ioctl (file, SPI_IOC_MESSAGE(1), &spi) ;
    }
    spi.tx_buf        = (unsigned long)(bytes + (bufsize/bytes_one_time)*bytes_one_time) ;
    spi.rx_buf        = (unsigned long)NULL ;
    spi.len           = bufsize % bytes_one_time;
    spi.delay_usecs   = spiDelay ;
    spi.speed_hz      = spiSpeed ;
    spi.bits_per_word = spiBPW ;
    ioctl (file, SPI_IOC_MESSAGE(1), &spi) ;
}