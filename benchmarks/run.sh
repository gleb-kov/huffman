function helper {
    echo -e "First argument must be valid test case name:\n\nsynthetic\nenglish\nlogs\nrandom"
    exit 1
}

if [ -n "$1" ]
then
    case $1 in
        synthetic)
	    echo "1"
            ;;
        english)
            echo "2"
            ;;
        logs)
            echo "3"
            ;;
        random)
            echo "4"
            ;;
        *)
            helper
    esac	   
#run generator with filename
#run huffman
#check if diff is empty
#ll
else
    helper
fi

