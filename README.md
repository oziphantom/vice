# vice
 my vice mods


#### Some Shortcuts restored to WINVICE shortcuts
Alt + M = Monitor
Alt + H = Mouse Capture (new)
Alt + R = Reset
Alt + Shift + R = Hard Reset
Atl + X = Quit

#### GMod2 Cart Changes
From a monitor context ( io, break points etc ) 
DEFF now returns the internal bank number 
This does not appear when accessed in code, it will still return the normal value. 
This allows you to get the GMod2 bank for break points. For example
break $8010 if @io:$DEFF == 2
to break upon the $8010 in the 2nd bank of GMod2. Note this does not detect if the cart
is enabled. So you can still get false positives.
you can now also do 
break $0810 if @$d020 == $f0 if you just want the "cpu" bank

Note that Carts are broken in x128 at the moment, they will not switch to C64 mode.

#### New Monitor Commands
_bbreak/bbk_ Break Bank (x64sc and X128 only )
bbreak <bankname> [address-<address>] <condition>
this allows you to set a break point in a specific bank
so if you want to break upon C64 KERNAL rom FFD2 and not RAM FFD2 you can do
bbreak rom $ffd2
to fix the false positives above in the GMod2 Changes you can do
bbreak cart $8010 if @io:$DEFF == 2
This is most handy in x128 as you can now do
bbreak ram1

This needs heavy testing, especially on x128 where ZP and Stack relocation make a mess 
of things.

_Verfiy|v_ (all)
v "filename" device [address]
This will load the file and compare against the machines memory and report PASSED or
FAILED if in ram contents match the file contents. 

New autoload inject data format Long Non-Linear 
"inject into RAM LNL" or -autostartprgmode 3
This is a file format exported from 64Tass ( use -n -x -X ) 
it takes the form of 
    00 len lo
    01 len hi
    02 len bank
    03 addr lo
    04 addr hi
    05 addr bank
    06 .. Len number of bytes that hold data
    XX len lo
    XX+1 len hi
    ...
    until 
    00
    00
    00

Where banks map to
    Bank 00 = RAM
    Bank 01 = RAM Bank 1
    Bank 03 = IO
    Bank 05 = Interal Function RAM
    Bank 06 = External Function RAM
    Bank 09 = VDC Memory

This allows you to direct inject code into both banks and any function roms
(attach them in mode 2 RAM ), you can also inject data into VDC memory. Or CRAM
This only works on direct inject, you can not load one from the virtual FS, or D64
