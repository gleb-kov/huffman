import sys

from gen import synthetic_phrase, english_phrase, random_phrase

def check_size(size):
    kib = 1000
    gib = kib * 1000 * 1000

    if size < kib or size > gib:
        print("Unusual test size. File would be generated no matter what.")

def test_writer(fname, size, stream):
    batch = 5

    with open(fname, 'w') as fout:
        while size > 0:
            phrase = stream()
            for i in range(batch):
                pl = min(len(phrase), size)
                fout.write(phrase[0:pl])
                size = size - pl

def run_synthetic(fname, size):
    test_writer(fname, size, synthetic_phrase)

def run_english(fname, size):
    test_writer(fname, size, english_phrase)

def run_random(fname, size):
    test_writer(fname, size, random_phrase)

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
