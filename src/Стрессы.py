import os
ti = 0 # seed number
while True:
    os.system(f"python3 gen.py {ti} > .in")
    return_code = os.system("./correct < .in > .outc && ./incorrect < .in > .outi")
    if return_code:
        print("re:", ti)
        exit()
    if open(".outi").read() != open(".outc").read():
        print("wa:", ti)
        exit()
    ti+=1
    if ti % 25 == 0:
        print(ti)

import random
import sys
seed = int(sys.argv[1])
random.seed(seed)
