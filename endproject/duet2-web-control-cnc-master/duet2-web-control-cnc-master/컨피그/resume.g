; resume.g
; called before a print from SD card is resumed

G54
G0 Z94
G55  Select work 1 coordinates
G1 R1 X0 Y0       ; go to directly above position of the last print move
G1 R1 X0 Y0 Z0        ; go back to the last print move