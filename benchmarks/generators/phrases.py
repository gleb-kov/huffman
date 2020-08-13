import random

# This phrases would be written into file

################################### SYNTHETIC ############################

def synthetic_phrase():
    return 'a'

################################### ENGLISH ##############################

# building random string that requires main constraints of english text

# letter frequency. source: https://en.wikipedia.org/wiki/Letter_frequency
# Average length of word: 5 letters
# Average length of sentence: 15 words

word_length = 5
sentence_words = 15
sentence_letters = sentence_words * (word_length + 1)

freq_arr = [8.497, 1.492, 2.202, 4.253, 11.162, 2.228, 2.015, 6.094, 7.546,
        0.153, 1.292, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 7.587, 6.327,
        9.356, 2.758, 0.978, 2.560, 0.150, 1.994, 0.077]

def get_freq_map(precision):
    def validate_prec(prec):
        if prec < 0:
            return 0
        if prec > 3:
            return 3
        return prec

    precision = validate_prec(precision)
    k = 10 ** precision

    result = {}
    for i in range(0, 26):
        c = chr(ord('a') + i)
        result[c] = int(freq_arr[i] * k)
    return result

def english_phrase():
    sl = sentence_letters
    backet = ""
    cnt = get_freq_map(2)

    for i in range(0, 26):
        c = chr(ord('a') + i)
        for j in range(0, cnt[c]):
            backet = backet + c

    backet = ''.join(random.sample(backet, len(backet)))
    phrase = ' '.join(backet[i:i+5] for i in range(0, len(backet), 5))
    phrase = '. '.join(phrase[i:i+sl-1] for i in range(0, len(phrase), sl))
    return phrase
