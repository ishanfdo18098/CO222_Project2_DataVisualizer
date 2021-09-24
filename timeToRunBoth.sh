SECONDS=0
output=$(./a.out meetingData.csv -p)
echo "your program took $SECONDS seconds"
SECONDS=0
output1=$(./samplev1 meetingData.csv -p)
echo "sameplev1 took $SECONDS seconds"
if [ "$output" = "$output1" ]; then
    echo -e "Test \033[0;32m PASS \033[0;0m"
else
    echo -e "Test \033[0;31m FAILED---------------\033[0;0m"
fi