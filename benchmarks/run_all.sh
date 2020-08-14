function helper {
    echo -e "First argument must be valid path to huffman binary file"
    echo -e "Second argument must be test size"
    exit 1
}

if [ -n "$1" ] && [ -n "$2" ]; then
    ./run.sh "$1" synthetic "$2"
    echo
    ./run.sh "$1" english "$2"
    echo
    ./run.sh "$1" random "$2"
else
    helper
fi
