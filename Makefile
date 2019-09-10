#Build script for mpwdpwn

CC=gcc
CCPARAMS=-Wall

default: mpwdpwn

check:
	$(shell [ ! -e obj ] && mkdir obj)

clean:
	$(shell echo Cleaning up...)
	$(shell rm -rf obj)

mpwdpwn: check mpwdpwn.o
	$(CC) obj/mpwdpwn.o $(CCPARAMS) -o mpwdpwn

mpwdpwn.o:
	$(CC) -c src/mpwdpwn.c -o obj/mpwdpwn.o