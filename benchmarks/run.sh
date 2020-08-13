function helper {
    echo -e "First argument must be valid test case name:\n\nsynthetic\nenglish\nlogs\nrandom"
    exit 1
}

if [ -n "$1" ]
then
    python3 generators/main.py "$1" tmp.txt 100
#add test size
#run huffman
#check if diff is empty
#ll
else
    helper
fi

