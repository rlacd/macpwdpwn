#Build script for mpwdpwn

CC=gcc
CCPARAMS=-Wall

default: mpwdpwn

mpwdpwn: mpwdpwn.o
	$(CC) obj/mpwdpwn.o $(CCPARAMS) -o mpwdpwn

mpwdpwn.o:
	$(CC) -c src/mpwdpwn.c -o obj/mpwdpwn.o