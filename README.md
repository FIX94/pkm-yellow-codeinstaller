# pkm-yellow-codeinstaller  
This project takes up to 1122 bytes of code and uses it to generate a set of button inputs that can then be used to go from the game start up to installing that code into the game.  
Both english and german versions of pokemon yellow are supported right now, although in the future it may be possible to support more generation 1 pokemon titles.  
It firstly generates as a .bk2 file to be used in the BizHawk emulator, and with the help of a script can then be converted into a .txt that you can use with the gamecube homebrew software gameboy interface to install it onto a real cart using a gameboy player.  
Also it generates an updater .bk2 file which can be used in case the installer was already used on the cart, this can be helpful to get new code onto a real cart much faster compared to a full install (updating takes about 3 minutes vs installing taking about 16 minutes).  
To see this project actually used, I firstly made a cart dumper using the headphone out of a gameboy color and hotswapping carts:  
https://github.com/FIX94/gameboy-audio-dumper  
And also towards just pokemon yellow made a full sound test for all 50 music tracks that actually shows off the volume levels of each instrument while the music is playing using some undocumented gameboy color registers:  
https://github.com/FIX94/pkm-sound-visualizer  
