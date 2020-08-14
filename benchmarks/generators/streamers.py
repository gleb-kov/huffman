import random

NUMBERS = '0123456789'
DLETTERS = 'abcdefghijklmnopqrstuvwxyz'
ULETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
SIGNS = '!@#$%^&* ()[]{}<>\\/?~\'`"+-=_:;,.\n\t'

SIMULATION = NUMBERS + SIGNS + ULETTERS

dletter_coef = 5

for i in range(dletter_coef):
    SIMULATION = SIMULATION + DLETTERS

def random_streamer():
    sample = ''.join(random.sample(SIMULATION, len(SIMULATION)))
    return sample[0:16]
