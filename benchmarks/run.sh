function helper {
    echo -e "First argument must be valid path to huffman binary file"
    echo -e "Second argument must be valid test case name:\n\nsynthetic\nenglish\nrandom"
    echo -e "Third argument must be test size"
    exit 1
}

if [ -n "$1" ] && [ -n "$2" ] && [ -n "$3" ]; then
    echo "-------------------------- Generate test -------------------------"
    echo "Mode: $2"
    python3 generators/main.py "$2" test.txt "$3"
    echo "-------------------------- Run compress --------------------------"
    eval "$1" --verbose --compress test.txt encoded.txt
    echo "------------------------- Run decompress -------------------------"
    eval "$1" --verbose --decompress encoded.txt decoded.txt
    echo "--------------------------- Check diff ---------------------------"
    DIFFSIZE=$(diff test.txt decoded.txt | wc -l)
    if [ "$DIFFSIZE" -eq 0 ]; then
        echo "Everything is OK. Check saved space (ls -lh dump):"
        ls -lh test.txt encoded.txt
        rm -r test.txt encoded.txt decoded.txt generators/__pycache__
    else
        echo "FAILED. Diff:"
        diff test.txt decoded.txt
    fi
    echo "------------------------------------------------------------------"
else
    helper
fi

