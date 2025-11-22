# christmas_tree
This is Arduino code designed to control a 50 LED string of WS2811 lights on a Christmas tree. Originally written for the Infosec 716 pre-holiday party at the Bit Haven hacker space.

The lights I used: https://www.amazon.com/dp/B01AG923GI

I used a basic Arduino Uno to control the lights. Wiring instructions below:

* 5v power line to the positive input on the LED string
* Ground to the ground wire on the lights
* Arduino pin 6 to the data line on the lights
* Arduino pin 5 to a pushbutton (changes the color of the lights)
* Arduino pin 4 to a digital sound sensor (changes the color when the party noise gets loud)
* Arduino pin 3 to a pushbutton (rotates between display modes)

Display modes:
  * multiple colors, rotate forward
  * multiple colors, rotate backwards
  * multiple colors, fade and rotate
  * single color, static
  * single color, fade out and in
  * Knight Rider mode

I powered it with a typical USB charger plugged into the Arduino USB port, I don't know if that would be enough to power multiple strings of lights but it worked for one.

This was a fun little project to learn Arduino programming. I found out when it was done that the Arduino language supports switch statements, so please ignore all those else ifs. 
