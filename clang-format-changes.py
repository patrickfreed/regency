#!/usr/bin/python

import os
import subprocess
import re

# files = subprocess.check_output("git status | grep 'modified\\|new file' | cut -d' ' -f4", shell=True).split("\n")

git = subprocess.check_output("git status", shell=True)
files = re.finditer(r"(?:modified|new file):\s*([\w/\.]*)", git)

for match in files:
    f = match.group(1)
    if len(f) > 4 and f.endswith((".hpp", "cpp", ".hh", ".h")):
        subprocess.check_output("clang-format -i " + f, shell=True)
        print "formatted " + f

