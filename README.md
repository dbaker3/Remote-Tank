Remote-Tank
===========

I wrote Tank as my Senior Seminar project for my BS in Computer Science at UVA-Wise. The hardware design requires a basic radio controlled vehicle, in my case a small tank. The radio transmitter sends 4 command: forward, backward, left, right. The way the tank was designed, when the left/right buttons were pressed, only one of the tank tracks moved causing the tank to turn. This will be different for other types of automobiles.

The 4 movements of the r/c transmitter from the controller is wired to pins 2-5 of the parallel port. I used optoisolators to electrically isolate the PC's system board from the r/c tank's transmitter circuit. A sketch of the circuit is in the project_images folder.

The software basically just activates the parallel port pins causing the r/c controller to transmit the signals to move the tank. Includes: macro mode that you can write a script of moves for the tank to carry out, network mode controls tank over network, manual mode controls tank in real time from PC keyboard.

The network code is obviously roughly hacked and insecure as this project was basically just a proof of concept.
