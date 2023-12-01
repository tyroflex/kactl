import os
import sys
import subprocess
import time


def run_testcase(t):
    infile = os.path.join(cwd, f'{sys.argv[1]}{t}.in')
    outfile = os.path.join(cwd, f'{sys.argv[1]}{t}.pout')
    if not os.path.exists(infile):
        return False
    if os.stat(infile).st_size == 0:
        return False
    if os.path.exists(outfile):
        os.remove(outfile)
    open(outfile, 'a').close()
    print(f'Running Test {t}')
    start = time.perf_counter()
    subprocess.Popen(
        args=[f'./{sys.argv[1]}'],
        stdin=open(infile, 'r'),
        stdout=open(outfile, 'w'),
        stderr=subprocess.PIPE,
    )
    end = time.perf_counter()
    print(f'{end-start}s')
    if (end - start) > tl:
        print(f'Time limit exceeded on test {t}')
        return True
    # substitute with FC on windows.
    code = subprocess.run(
        ['diff',
         os.path.join(cwd, f'{sys.argv[1]}{t}.out'),
         os.path.join(cwd, f'{sys.argv[1]}{t}.pout')]
    )
    if code.returncode != 0:
        print(f'Wrong answer on test {t}')
    else:
        print(f'Accepted on test {t}')
    print()
    return True


os.chdir(sys.argv[1])
tl = (int(sys.argv[2]) if len(sys.argv) > 2 else 1)
cwd = os.getcwd()
res = subprocess.run(
    ['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-Wshadow', '-o',
     os.path.join(cwd, sys.argv[1]),
     os.path.join(cwd, f'{sys.argv[1]}.cpp')]
)
if res.returncode != 0:
    exit(1)
if len(sys.argv) > 3:
    tc = map(int, sys.argv[4:])
    for i in tc:
        run_testcase(i)
else:
    for i in range(1, 9999):
        if not run_testcase(i):
            break
