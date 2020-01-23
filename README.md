# Smart Sensor

At Avans Hogeschool we have a living lab; Smart Sensor. The goal of this Smart Sensor
is to have a development platform that communicates via a Mesh network and is able
to measure different kind of things.

# Install programming environment

## Hardware
We use the USBasp programming hardware. More information can be found on the website https://www.fischl.de/usbasp/.

## Software
We use avrdude and gcc on a Linux box. Ofcourse, this could be done on a Windows machine. The following applications need to be installed:
> apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude

## First application
```
#include <avr/io.h>

int main () {
  DDRC  = 0xff;
  PORTB = 0xFF;
  while (1) {
  
  }
  
  return 0;
}
```
