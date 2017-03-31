---
title: 40 Meter Direct Conversion Transceiver
---
[![40m Transceiver Front](img/40mxcvrfront.jpg)](img/40mxcvrfront.jpg)

Here is a CW transceiver for 40 meters that uses a direct conversion receiver and puts out 6 watts.  I know, it is ugly and it is also simple, as you can see from the schematic below.  I built previous receivers using direct conversion and never considered them real contenders until I finally tried using a diode ring product detector.   A comparison was made by switching the direct conversion receiver of this rig between the receiver of a Kenwood TS-440S.  The 440 did not sound much better.  In fact, with the CW filter switched in on the Kenwood, it sounded more fatiguing.  The two receivers sounded, to me, about equal in sensitivity.  The direct conversion receiver also appeared to be able to discern between weak and strong signals the same as the Kenwood.  Whatever weak signal I heard on one radio, I was able to hear in the other.  The direct conversion had no broadcast or unwanted "din" to be heard.  I could not hear any hum even when using headphones.  Many other builders include some type of attenuator on the input of such a rig.  I was planning on using a 500 ohm pot on the receiver input but never got around to including it.  I really do not think I need it.  There is a hole on the lower left corner of the front panel that was intended for the attenuator pot.  The pot at the upper left is a speed control for the keyer.  The label either fell off or I never got around to making one.  There is a Lewallen Optimized Direct Conversion style low pass filter as well as a 700 Hz bandpass filter.  The two-pole bandpass filter is about the right selectivity for my ears and there is no ringing.

[![40m Transceiver Schematic](img/40mxcvrsch.png)](img/40mxcvrsch.png)

You will notice that the rig is controlled with an Arduino Pro Mini.  These things are cheap and do the job.  The VFO is an Adafruit Si5351 breakout board.  It is the most expensive component at around $8.  It is a bargain.  I have some individual Si5351 chips that cost $1.15 at Mouser, but they are super tiny.  I will stick with the breakout board.  Chinese DDS boards were used on some of my earlier rigs but I noticed that they draw more current than the Si5351.   The Si5351 has three outputs but I only used one for both transmit and receive.  My original intent was to make a tiny hiking radio that ran on a small battery pack.   That is why I tried using a direct conversion receiver in this rig in the first place.  The Arduino controller takes care of transmit/receive switching, digital display, offset tuning, sidetone generation (pseudo sine wave), controlling the VFO with tuning rates of 10 Hz, 100 Hz, and 1KHz steps, and provides an iambic keyer.

[![40m Transceiver Top](img/40mxcvrtop.jpg)](img/40mxcvrtop.jpg)

Things are even uglier on the inside.  I have actually made some pretty things in the past using etched circuit boards.  But I have been reading a lot of EMRFD which has taught me to lighten up.   Sometimes it is nice to build a circuit ugly style and have it ready for testing in only a few minutes.   This radio only took a few evenings over a period of six weeks to build.  I would go days during that period in which I did not touch the project.  Also, look at all of that beautiful grounding.  The plentious ground plane could be the reason this radio, despite its appearance, does not exhibit hum or instablility.

The controller perfboard, holding the LCD, control pots, encoder, the Arduino, and the VFO, is attached to the front panel so you are looking at it from the edge.  Down on the lower deck is, from near left, the diode ring mixer.  This is followed directly to the right by the NE5532 dual low noise opamp section.  I originally thought I would leave all of the audio filtering to that one board.  So, the LM386 audio output amplifier is the next board in line.  Later, the 700 Hz bandpass filter was soldered vertically to the back edge of the main deck.  It connects to its bretheren with lengths of RG-174 coax.   All of the sections of the receiver operate on +8V taken from an LM7808 regulator on the upper right corner of the deck.  The rig originally operated at about 1.5 watts output using the transmitter module at the rear middle of the view above.   The BD139 was the original final output transistor.   That was how it remailed for about a week until I added a 6 watt amplifier that is attached vertically above the original heatsink.   The amplifier uses an IRF510 FET final transistor.   It shares the heatsink with the BD139 original final transistor that is now a driver.   The heatsink is about 2" x 3 " of .050" aluminum.  It just gets warm to the touch during operation.  All of the transmitter circuits operate on +12V.    As for voltage distribution:    8V is sent to the Arduino on its "RAW" pin.   The Arduino has its own 5V regulator to run itself and the LCD.  5V is also sent to  the Si5351 breakout board which has its own 3.3V regulator to run the VFO.  All circuits seem to be happy with this arrangement.

This is a pleasant rig to operate.  The offset tuning is smooth and easy.  The offset frequency is displayed in Hz on the LCD as well as is the tuning rate.  When I get QRM on one side of my transmit frequency, I can quickly swing my receive frequency back to the other side.  The offset range is 2500 Hz either side of the transmit frequency in 5 Hz steps.  The LCD indicates if the offset is + or -.  The transmit frequency can only be changed by the main tuning knob and is always displayed with a 10 Hz resolution.

The built in keyer is smooth and easy.  The speed is adjustable from about 5 WPM to a near blur (to me).  The range is set by software.  The muting circuit is a simple 2N3819 FET.  There is a slight click with the break in function but it is not objectional to me.  I guess I should work on that. 

I suppose the next step in the project is to lay out a printed circuit board and make a pretty version.  If I do that, others may want to make their own version of this rig.  I will also include a way for others to download the software for the Arduino.  The software is a work in progress.  All of the software is working except I have not yet made a provision in it to use a straight key.  Guess I should not answer any more stations calling CQ SKCC until that provision is included.    One of my first contacts with 6 watts was with a French station.  The antenna is a simple 40 meter dipole at about 24 feet height.

## Downloads

### Schematic
Download a schematic of the rig in ExpressPCB format:

(Requires software availble at <expresspcb.com>)

[40 Meter Transceiver Schematic, v.1  061516](files\40 METER TRANSCEIVER 061516.sch)

### Arduino Source
Download Arduino source code:

[Arduino Source Code 082716](files\QRP_TRANSCEIVER_082716.ino)