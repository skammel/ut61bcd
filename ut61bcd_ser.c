/* UNI T multimeter ut61bcd - simple read, parse and display tool for the ut61b ut61c ut61d volt-meter 
 * Author: Skammel <git@skammel.de> - Skammel Solutions 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <linux/hidraw.h>
#include "ut61bcd_ser.h"
int open_dev (char *dev)
{
  unsigned char buf[6] = "";
  uint32_t bps = BAUDRATE;
  int fd = -1;

  fd = open (dev, O_RDWR);
  if (fd < 0)
   {
     fprintf (stderr, "error cannot open %s\n", dev);
     return -1;
   }

  buf[0] = 0;
  buf[1] = bps;
  buf[2] = bps >> 8;
  buf[3] = bps >> 16;
  buf[4] = bps >> 24;
  buf[5] = 3;                   // 3 = 8 bits no parity??
  if (ioctl (fd, HIDIOCSFEATURE (6), buf) < 0)
   {
     fprintf (stderr, "error: cannot configure %s\n", dev);
     close (fd);
     return -2;
   }

  return fd;
}

int read_dev (int fd, unsigned char *data)
{
  unsigned char buf[HID_PKT_SIZE];
  int cnt = 0;

  while (cnt < DATA_PKT_SIZE)
   {
     read (fd, buf, HID_PKT_SIZE);

     if (buf[0] & 7)
      {
        data[cnt] = buf[1];
        cnt++;
        if (buf[1] == '\n')
         {
           return cnt;
         }
      }
     else
       break;

   }

  return 0;
}

void close_dev (int fd)
{
  if (fd >= 0)
    close (fd);
}
