import sys

from phrases import synthetic_phrase, english_phrase
from streamers import random_streamer

def check_size(size):
    kib = 1000
    gib = kib * 1000 * 1000

    if size < kib or size > gib:
        print("Unusual test size. File would be generated no matter what.")

def phrase_writer(fname, size, phrase):
    with open(fname, 'w') as fout:
        pl = len(phrase)
        while size >= pl:
            fout.write(phrase)
            size = size - pl
        fout.write(phrase[0:size])

def stream_writer(fname, size, stream):
    with open(fname, 'w') as fout:
        while size > 0:
            phrase = stream()
            pl = min(len(phrase), size)
            fout.write(phrase[0:pl])
            size = size - pl

def run_synthetic(fname, size):
    phrase_writer(fname, size, synthetic_phrase())

def run_english(fname, size):
    phrase_writer(fname, size, english_phrase())

def run_random(fname, size):
    stream_writer(fname, size, random_streamer)

def failed_mode(fname, size):
    print("UNEXPECTED MODE. Run without args to see help info.")

def runner(mode):
    return {
        'synthetic': run_synthetic,
        'english': run_english,
        'random': run_random
    }.get(mode, failed_mode)

def validate_args():
    if len(sys.argv) != 4:
        print("run with arg: <mode> <filename> <sizeof test>")
        print()
        print("Modes:")
        print("synthetic")
        print("english")
        print("random")
        exit()

    check_size(int(sys.argv[3]))

if __name__ == '__main__':
    validate_args()

    mode = sys.argv[1]
    fname = sys.argv[2]
    size = int(sys.argv[3])

    run_test = runner(mode)
    run_test(fname, size)
