/* UNI T multimeter ut61bcd - simple read, parse and display tool for the ut61b ut61c ut61d volt-meter 
 * Author: Skammel <git@skammel.de> - Skammel Solutions 
 */
#ifndef __UT61BCD_SER_H
#define __UT61BCD_SER_H

/* this baudrate is not usual - but we really need 19230 for HID -> serial */
#define BAUDRATE 19230

/* HID packet size */
#define HID_PKT_SIZE 8

/* data packet size */
#define DATA_PKT_SIZE 14

/* open and init the given hidraw device */
int open_dev (char *dev);

/* read data */
int read_dev (int fd, unsigned char *data);

/* close device */
void close_dev (int fd);

#endif
