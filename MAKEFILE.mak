# ----------------------------
# PlayStation 1 Psy-Q MAKEFILE
# ----------------------------
all:
	
	ccpsx -Xo0x80010000 -Wall -O2 src/*.cpp -I include -o main.cpe
	cpe2x /ce main.cpe
	mkpsxiso.exe -o game.iso -y cuesheet.xml
