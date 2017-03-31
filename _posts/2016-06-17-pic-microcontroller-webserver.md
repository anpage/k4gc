---
title: PIC Microcontroller Webserver
---
## Web Server for IP Remote Control

I've been wanting (needing) a way to control and monitor non-internet ready electronic equipment from a distance for a long time.  The internet is a great way to do this.   Here is a webserver that I made on perfboard that works very well.  It has a 10baseT interface that is plenty fast enough to do what I want it to do.  There are eight single pole double throw relay circuits, eight on/off inputs, and two analog inputs.    The circuit uses a PIC18F4520 microcontroller with a ENC28J60 ethernet controller.  The relay coils use unregulated 12 volts rather than the 5 volt bus to cut down on  electrical noise that may affect the logic circuits and should also run a little cooler with the higher voltage.  The relay coils are operated through a ULN2803 octal darlington driver.   The digital inputs are isolated with optical couplers.   Information found on the web indicates a PIC16F887 would work too.  However, I plan on including a secure login and maybe some other features that will require the extra memory of the '4520.

## The Project...

Here is the first rendition of the PIC IP webserver put together on perfboard.  This is the first perfboard circuit of any size that I have built in about twenty years.  It is good to be back.  Its phenolic smell reminds me of my first visit to a Radio Shack store in 1968.  They were much more than phone/gadget stores back then and smelled like real electronics.

[![PIC Webserver](img\picwebserver.jpg)](img\picwebserver.jpg)

## Schematics

[![PIC Webserver Schematic 1](img\picwebserversch1.gif)](img\picwebserversch1.gif)
[![PIC Webserver Schematic 2](img\picwebserversch2.gif)](img\picwebserversch2.gif)