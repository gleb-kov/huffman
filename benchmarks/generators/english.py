import random
import sys

#################### build string that asymptotically okay #########

# Letter frequency
# source: https://en.wikipedia.org/wiki/Letter_frequency

# Average length of word: 5 letters
# Average length of sentence: 15 words

word_length = 5
sentence_words = 15
sentence_letters = sentence_words * (word_length + 1)
order = "etarionshdluwmfcgypbkvjxqz"
freq_arr = [8.497, 1.492, 2.202, 4.253, 11.162, 2.228, 2.015, 6.094, 7.546,
        0.153, 1.292, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 7.587, 6.327,
        9.356, 2.758, 0.978, 2.560, 0.150, 1.994, 0.077]

def validate_prec(precision):
    if precision < 0:
        return 0
    if precision > 3:
        return 3
    return precision

def get_freq(prec):
    precision = validate_prec(prec)
    k = 10 ** precision

    result = {}
    for i in range(0, 26):
        c = chr(ord('a') + i)
        result[c] = int(freq_arr[i] * k)
    return result

def get_freq_phrase():
    sl = sentence_letters
    backet = ""
    cnt = get_freq(2)

    for i in range(0, 26):
        c = chr(ord('a') + i)
        for j in range(0, cnt[c]):
            backet = backet + c

    backet = ''.join(random.sample(backet, len(backet)))
    phrase = ' '.join(backet[i:i+5] for i in range(0, len(backet), 5))
    phrase = '. '.join(phrase[i:i+sl-1] for i in range(0, len(phrase), sl))
    return phrase

####################################################################

argc = len(sys.argv)

if argc != 3:
    print("run with arg: <filename> <sizeof test>")
    exit()

fname = sys.argv[1]
num = int(sys.argv[2])

kib = 1000
gib = kib * 1000 * 1000

if num < kib or num > gib:
    print("Unusual test size. File would be generated no matter what.")

with open(fname, 'w') as fout:
    phrase = get_freq_phrase()
    pl = len(phrase)
    while num >= pl:
        fout.write(phrase)
        num = num - pl
    fout.write(phrase[0:num])
