#!/usr/bin/python3

import sys
import json
import os
import time
import pexpect
import shutil
import io
import subprocess
import random

# For break_type = 'admin', your program receives the name and password of a user that you should create without reading data/administration.txt
name, password = input().split(' ')

# Suppose you have somehow found the admin credential
# The sample vuln program accepts any credential, so here it is
admin_cred = 'a'

# Code below demonstrates how you can interact with the gradebook
# Note that you can start the gradebook multiple times, if needed
try:
    # Starts the gradebook
    proc = pexpect.spawn('bin/gradebook', timeout=2, encoding='ascii')
    proc.logfile = sys.stdout
    proc.ignorecase = True
    proc.delaybeforesend = None

    # Send a specific line
    proc.expect('Login or signup:')
    proc.sendline('signup')
    # Wait for a specific output - you don't always have to do this
    # Note that this is a regex
    proc.expect('Credentials:')
    proc.sendline(admin_cred)
    proc.expect('Invalid input')
    proc.expect('Student or teacher:')
    proc.sendline('student')
    proc.expect('Name:')
    proc.sendline(name)
    proc.expect('Password:')
    proc.sendline(password)
    proc.expect('100005')

    if not proc.terminate():
        if not proc.terminate(True):
            print('Oh no we cannot terminate the gradebook')
    
    # Inform the grader that we have succeeded
    print('Success')
except pexpect.TIMEOUT as etimeout:
    # If you see this, the gradebook did not output what you wait for
    print('Gradebook timed out!')
