/* UNI T multimeter ut61bcd - simple read, parse and display tool for the ut61b ut61c ut61d volt-meter 
 * Author: Skammel <git@skammel.de> - Skammel Solutions 
 */
#ifndef __UT61BCD_H
#define __UT61BCD_H

/* parse the given data and create the mode string */
char *get_mode_str (char *mode_str, unsigned char *data);

/* parse the given data and return tge value as double */
double get_val (unsigned char *data);
#endif
