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
static const unsigned int    spiSpeed = 1000000 ;
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
    __u32 speed = 160000;

    if ((file = open(filename, O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        com_serial = 0;
        exit(1);
    }

    if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
        perror("SPI rd_lsb_fist");
        return -1;
    }
    //sunxi supports only 8 bits

    if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0) {
        perror("can't set bits per word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("SPI bits_per_word");
        return -1;
    }

    if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed) < 0) {
        perror("can't set max speed hz");
        return -1;
    }

    if (ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        perror("SPI max_speed_hz");
        return -1;
    }
    
    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n", filename, mode, bits, lsb ? "(lsb first) " : "(msb first) ", speed);

    return file;
}

//////////
// Write buffer to spi
//////////
void spi_write(int file, uint8_t* bytes, int bufsize) {
    struct spi_ioc_transfer spi ;
// Mentioned in spidev.h but not used in the original kernel documentation
//	test program )-:

  memset (&spi, 0, sizeof (spi)) ;

  spi.tx_buf        = (unsigned long)bytes ;
  spi.rx_buf        = (unsigned long)bytes ;
  spi.len           = bufsize ;
  spi.delay_usecs   = spiDelay ;
  spi.speed_hz      = spiSpeed ;
  spi.bits_per_word = spiBPW ;

  ioctl (file, SPI_IOC_MESSAGE(1), &spi) ;
}