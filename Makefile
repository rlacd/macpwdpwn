#Build script for mpwdpwn

CC=gcc
CCPARAMS=-Wall

default: mpwdpwn

check:
	$(shell [ ! -e obj ] && mkdir obj)

clean:
	$(shell echo Cleaning up...)
	$(shell rm -rf obj)

mpwdpwn: check util.o strutils.o mpwdpwn.o
	$(CC) obj/util.o obj/strutils.o obj/mpwdpwn.o $(CCPARAMS) -o mpwdpwn

mpwdpwn.o: src/mpwdpwn.h
	$(CC) -c src/mpwdpwn.c -o obj/mpwdpwn.o

strutils.o: src/strutils.h
	$(CC) -c src/strutils.c -o obj/strutils.o

util.o: src/util.h
	$(CC) -c src/util.c -o obj/util.o