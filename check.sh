echo ""
echo "Running Diff"
echo "--------"
rm turnin.txt
rm details.txt
for f in file*.txt;
do
    f=${f#tests/}
    cat out_$f >> turnin.txt
    echo "out_$f">> details.txt
    sdiff -s key_$f out_$f >> details.txt
    if [ ${PIPESTATUS[0]} -eq 0 ];
    then
        echo "key_$f and out_$f are identical"
    else
        echo "key_$f and out_$f differ :: check details.txt for details"
    fi
done
echo "--------"
