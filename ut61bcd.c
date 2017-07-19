/* UNIT t multimeter ut61bcd - simple read, parse and display tool for the ut61b ut61c ut61d volt-meter 
 * Author: Skammel <git@skammel.de> - Skammel Solutions 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "ut61bcd.h"
#include "ut61bcd_ser.h"

/* DC  0000 V  MAN BG */
unsigned char test1[] =
  { 0x2B, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x11, 0x00, 0x00, 0x80, 0x00,
  0x0D, 0x0A
};

/* DC  348.1 mV AUTO BG */
unsigned char test2[] =
  { 0x2B, 0x33, 0x34, 0x38, 0x31, 0x20, 0x34, 0x31, 0x00, 0x40, 0x80, 0x22,
  0x0D, 0x0A
};

const char sym1[8][64] =
  { "x", "x", " Auto ", " DC ", " AC ", " REL ", " HOLD ", " BG " };
const char sym2[8][64] = { "x", "x", " MAX ", " MIN ", "x", " LowBat ", "n" };
const char sym3[8][64] =
  { "µ", "m", "k", "M", " beep ", " Diode ", " % ", "x" };
const char sym4[8][64] =
  { "V ", "A ", "Ohm ", " ", " Hz ", "F ", "°C ", "°F " };

int main (int argc, char **argv)
{
//  unsigned char *valstr = test1;
  unsigned char datastr[28] = "";
  int fd = -1;
  char tmpstr[255] = "";

  if (argc < 2)
   {
     fprintf (stderr, "Usage: %s <dev>\n \
     exaple: %s /dev/hidraw1\n", argv[0], argv[0]);
     return 1;
   }

  if ((fd = open_dev (argv[1])) < 0)
   {
     return 2;
   }

  /* set stdin to none-blocking */
  fcntl (0, F_SETFL, O_NONBLOCK);

  printf (" press <enter> to quit\n\n");
  while (getc (stdin) != '\n')
   {
     if (read_dev (fd, datastr) != DATA_PKT_SIZE)
       continue;

//     write (2, datastr, 14);

     printf (" %7.3lf %s           \r", get_val (datastr),
             get_mode_str (tmpstr, datastr));
     fflush (stdout);
   }

  close_dev (fd);
  return 0;
}

double get_val (unsigned char *data)
{
  char tmpstr[6] = "";
  int val = 0;

  memset (tmpstr, 0, sizeof (tmpstr));
  memcpy (tmpstr, data, 5);
  val = atoi (tmpstr);

  switch (data[6] & 0x0f)
   {
   case 0:
     return (double) val / 1.0;
   case 4:
     return ((double) val / 10.0);
   case 2:
     return ((double) val / 100.0);
   case 1:
     return ((double) val / 1000.0);
   }

  return 0.0;

}

char *get_mode_str (char *mode_str, unsigned char *data)
{
  int i = 0;

  mode_str[0] = 0;

  for (i = 0; i < 8; i++)
   {
     if (data[8] & (128 >> i))
       strcat (mode_str, sym2[i]);
   }

  for (i = 0; i < 8; i++)
   {
     if (data[9] & (128 >> i))
       strcat (mode_str, sym3[i]);
   }

  for (i = 0; i < 8; i++)
   {
     if (data[10] & (128 >> i))
       strcat (mode_str, sym4[i]);
   }

  for (i = 0; i < 8; i++)
   {
     if (data[7] & (128 >> i))
       strcat (mode_str, sym1[i]);
   }

  return mode_str;
}
