; bed.g
; called to perform automatic bed compensation via G32

M561 ; clear any bed transform
; Probe the bed at 4 points
G30 P0 X15 Y15 H0 Z-99999
G30 P1 X15 Y1270 H0 Z-99999
G30 P2 X820 Y1270 H0 Z-99999
G30 P3 X820 Y15 H0 Z-99999 S