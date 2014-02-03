Remote-Tank
===========

I wrote Tank as my Senior Seminar project for my BS in Computer Science at UVA-Wise. The hardware design requires a basic radio controlled vehicle, in my case a small tank. The radio transmitter sends 4 command: forward, backward, left, right. The way the tank was designed, when the left/right buttons were pressed, only one of the tank tracks moved causing the tank to turn. This will be different for other types of automobiles.

The 4 movements of the r/c transmitter from the controller is wired to pins 2-5 of the parallel port. I used optoisolators to electrically isolate the PC's system board from the r/c tank's transmitter circuit. A sketch of the circuit is in the project_images folder.

The software basically just activates the parallel port pins causing the r/c controller to transmit the signals to move the tank. Includes: macro mode that you can write a script of moves for the tank to carry out, network mode controls tank over network, manual mode controls tank in real time from PC keyboard.

The network code is obviously roughly hacked and insecure as this project was basically just a proof of concept.

Compiled in Linux with GCC


README
------

    tank - Execute either on machine with transmitter using manual or macro mode. Execute on remote machine using network mode (this is the client software). Must be run as root. David Baker 2004.

    Compile with: gcc tank.c control.c man_mode.c mac_mode.c net_mode.c -o tank

    The program contains three modes: manual, macro, and network.

    Manual mode execution: ./tank man

    Macro mode execution: ./tank mac MACROFILE
    where MACROFILE is the location of the macroinstruction file.

    Network mode execution: ./tank net 127.0.0.1
    where 127.0.0.1 is the IP address of the server.

    The transmitter can be switched to the on position immediately after program execution.

    Manual mode is controlled by using the number keypad. Make sure that NumLock is on. The controls are: 5-stop, 8-forward, 4-forward&left, 6-forward&right, 2-backward, 1-backward&left, 3-backward&right. 'q' exits the program from manual mode.

    Macro mode processes the specified macroinstruction file, begins execution, and exits the program after all instructions are executed or until an invalid command is encountered. NOTE: Macro files must always end with a stop command. The program will execute 50 commands in every file. If the file does not have 50 commands, the last command is executed the remainder of the times. The commands for the macro file consist of a direction (two characters) and a number of seconds to execute the direction (1-digit number). The directions are: ff - forward, bb - backward, fr - forward&right, fl - forward&left, bl - backward&left, br - backward&right, ss - stop. The time is always a single digit. An example macro file might look like this:

    ff3
    fr1
    ff2
    br1
    bb4
    fl1
    ff3
    ss0

    This file would be processed as: go forard 3 seconds, turn forward&right 1 second, go forward 2 seconds, turn backward&right 1 second, go backward 4 seconds, turn forward&left 1 second, go forward 3 seconds, stop movement.

    Network mode uses the same commands as macro mode, however they are sent one-at-a-time to the server. Simply type the command followed by the Enter key. 'q' exits network mode and closes the server on the other end. 

    The included shell script 'localnet' will run the server and client with the loopback address, which will allow one-at-a-time typed commands to be entered locally. 
