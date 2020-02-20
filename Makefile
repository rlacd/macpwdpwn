#Build script for macpwdpwn

CC=gcc
CCPARAMS=-Wall

default: macpwdpwn

check:
	$(shell [ ! -e obj ] && mkdir obj)

clean:
	$(shell echo Cleaning up...)
	$(shell rm -rf obj)

macpwdpwn: check plist.o util.o strutils.o macpwdpwn.o
	$(CC) obj/plist.o obj/util.o obj/strutils.o obj/macpwdpwn.o $(CCPARAMS) -o macpwdpwn

macpwdpwn.o: src/macpwdpwn.h
	$(CC) -c src/macpwdpwn.c -o obj/macpwdpwn.o

strutils.o: src/strutils.h
	$(CC) -c src/strutils.c -o obj/strutils.o

util.o: src/util.h
	$(CC) -c src/util.c -o obj/util.o

plist.o: src/plist.h
	$(CC) -c src/plist.c -o obj/plist.o