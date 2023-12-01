import os
import sys
from pathlib import Path

cwd = os.getcwd()
Path(os.path.join(cwd, sys.argv[1])).mkdir(parents=True, exist_ok=True)
open(os.path.join(cwd, sys.argv[1], f'{sys.argv[1]}.cpp'), 'a').close()
for i in range(1, (10 if len(sys.argv) <= 2 else int(sys.argv[2]))+1):
    open(os.path.join(cwd, sys.argv[1], f'{sys.argv[1]}{i}.in'), 'a').close()
    open(os.path.join(cwd, sys.argv[1], f'{sys.argv[1]}{i}.out'), 'a').close()
