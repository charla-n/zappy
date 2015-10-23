#!/usr/bin/python2

import signal
import time
import socket
import sys
import subprocess
import os
import random
import time
import random

def connect_to():
    try :
        fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        fd.connect(("127.0.0.1", 1337))
        #fd.connect(("127.0.0.1", 1337))
        return (fd)
    except socket.error:
        print "cannot connect, sorry"
        sys.exit(0)

def usage():
    print "\nUsage   : ./mouli --all | [1-10] ..."
    print "Example : ./mouli 1 3 5 will execute tests 1, 3 and 5"
    print "\t  ./mouli 1 -> stress test"
    print "\t  ./mouli 2 -> random actions (10 clients)"
    print "\t  ./mouli 3 -> Broadcast leak-test(use when server is run with:"
    print "\t\tvalgrind --leak-check=full --show-reachable=yes ./server[...])"

def test1():
    fd = {}
    for i in range(0, 10):
        for j in range(0, 1000):
            fd[j] = connect_to()
            if fd[j].recv(4096) != "BIENVENUE\n":
                print "ERROR"
            fd[j].send("coucou\n")
        for j in range(0, 1000):
            fd[j].close()

def test2():
    array = ["avance", "droite", "gauche", "voir", "inventaire",
             "prend", "pose", "expulse", "broadcast", "incantation",
             "fork", "connect_nbr"]
    objects = ["nourriture", "linemate", "deraumere", "sibur", "mendiane",
               "phiras", "thystame"]
    fd = {}
    for i in range (0, 100):
        fd[i] = connect_to()
        if fd[i].recv(4096) != "BIENVENUE\n":
            print "ERROR"
        fd[i].send("coucou\n")
    while 1:
        for i in range (0, 10):
            string = array[random.randint(0, len(array) - 1)]
            if (string == "prend") or (string == "pose"):
                string += " " + objects[random.randint(0, len(objects) - 1)]
            try:
                fd[i].send(string + "\n")
                time.sleep(1/10.0)
            except socket.error:
                print "Socket error"

def test3():
    fd = {}
    for i in range (0, 5):
        fd[i] = connect_to()
        if fd[i].recv(4096) != "BIENVENUE\n":
            print "ERROR"
        fd[i].send("coucou\n")
    while 1:
        for j in range (0, 5):
            print "test fd[" + str(j) + "]"
            try:
                fd[j].send("broadcast" + "\n")
                time.sleep(1/10.0)
            except socket.error:
                print "Socket error"
        # if (j == 4):
        #     for k in range (0, 5):
        #         fd[k].close()
        #     for k in range (0, 5):
        #         fd[k] = connect_to()
        #         fd[k].send("coucou\n")

def test4():
    fd = connect_to()
    fd.send("coucou\ninventaire\nfork\nvoir\ninventaire\navance\navance\n")
    fd.send("blabla\ncoucou\nincantation\nincantation\n")
    time.sleep(5)

def init_pointers():
    pointers = {0 : test1,
                1 : test2,
                2 : test3,
                3 : test4}
    return pointers

def all_tests(pointers):
    for i in range(0, len(pointers)):
        pointers[i]()

def main(argv):
    signal.signal(signal.SIGPIPE, signal.SIG_IGN)
    pointers = init_pointers();
    if sys.argv[1] == "--all":
        all_tests(pointers)
    else :
        for i in range(1, len(argv)):
            pointers[int(argv[i]) - 1]()

"Launch server with ./server -n coucou marcha -x 5 -y 5 -c 10000"

if len(sys.argv) == 1 :
    usage()
    sys.exit(0)
else:
    main(sys.argv)
