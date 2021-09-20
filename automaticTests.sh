#/bin/bash

echo ""

FILE=18098_project2.c
if test -f "$FILE"; then
    gcc 18098_project2.c -Wall
    echo "Compiled $FILE"
fi

echo "Ashley_Parry,25,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26
Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv

output=$(./a.out)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test  1 \033[0;32m PASS \033[0;0m no inputs"
else
    echo -e "Test  1 \033[0;31m FAILED---------------\033[0;0m no inputs"
fi

output=$(./a.out meetingData.csv -m)
output1=$(./samplev1 meetingData.csv -m)
if [ "$output" = "$output1" ]; then
    echo -e "Test  2 \033[0;32m PASS \033[0;0m meetingData.csv -m"
else
    echo -e "Test  2 \033[0;31m FAILED---------------\033[0;0m meetingData.csv -m"
fi

output=$(./a.out -l 5)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test  3 \033[0;32m PASS \033[0;0m -l 5"
else
    echo -e "Test  3 \033[0;31m FAILED---------------\033[0;0m -l 5"
fi

output=$(./a.out -l 5 meetingData.csv)
output1=$(./samplev1 -l 5 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test  4 \033[0;32m PASS \033[0;0m -l 5 meetingData.csv"
else
    echo -e "Test  4 \033[0;31m FAILED---------------\033[0;0m -l 5 meetingData.csv"
fi

output=$(./a.out -l 5 meetingData.csv -p)
output1=$(./samplev1 -l 5 meetingData.csv -p)
if [ "$output" = "$output1" ]; then
    echo -e "Test  5 \033[0;32m PASS \033[0;0m -l 5 meetingData.csv -p"
else
    echo -e "Test  5 \033[0;31m FAILED---------------\033[0;0m -l 5 meetingData.csv -p"
fi

output=$(./a.out -l -5)
output1='Invalid option(negative) for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test  6 \033[0;32m PASS \033[0;0m -l -5"
else
    echo -e "Test  6 \033[0;31m FAILED---------------\033[0;0m -l -5"
fi

output=$(./a.out meeting)
output1='Only .csv files should be given as inputs.'
if [ "$output" = "$output1" ]; then
    echo -e "Test  7 \033[0;32m PASS \033[0;0m meeting"
else
    echo -e "Test  7 \033[0;31m FAILED---------------\033[0;0m meeting"
fi

output=$(./a.out -m -t)
output1='Cannot plot multiple parameters in same graph.
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test  8 \033[0;32m PASS \033[0;0m -m -t"
else
    echo -e "Test  8 \033[0;31m FAILED---------------\033[0;0m -m -t"
fi

output=$(./a.out -l 0)
output1=''
if [ "$output" = "$output1" ]; then
    echo -e "Test  9 \033[0;32m PASS \033[0;0m -l 0"
else
    echo -e "Test  9 \033[0;31m FAILED---------------\033[0;0m -l 0"
fi

output=$(./a.out -l 100 meetingData.csv)
output1=$(./samplev1 -l 100 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 10 \033[0;32m PASS \033[0;0m -l 100 meetingData.csv"
else
    echo -e "Test 10 \033[0;31m FAILED---------------\033[0;0m -l 100 meetingData.csv"
fi

output=$(./a.out -n)
output1='Invalid option [-n]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 11 \033[0;32m PASS \033[0;0m -n"
else
    echo -e "Test 11 \033[0;31m FAILED---------------\033[0;0m -n"
fi

output=$(./a.out --scaled)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 12 \033[0;32m PASS \033[0;0m --scaled"
else
    echo -e "Test 12 \033[0;31m FAILED---------------\033[0;0m --scaled"
fi

output=$(./a.out meetingData.csv meetingData.csv)
output1=$(./samplev1 meetingData.csv meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 13 \033[0;32m PASS \033[0;0m meetingData.csv meetingData.csv"
else
    echo -e "Test 13 \033[0;31m FAILED---------------\033[0;0m meetingData.csv meetingData.csv"
fi

output=$(./a.out --scaled meetingData.csv)
output1=$(./samplev1 --scaled meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 14 \033[0;32m PASS \033[0;0m --scaled meetingData.csv" 
else
    echo -e "Test 14 \033[0;31m FAILED---------------\033[0;0m --scaled meetingData.csv"
fi

output=$(./a.out -l abc)
output1='Invalid options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 15 \033[0;32m PASS \033[0;0m -l abc"
else
    echo -e "Test 15 \033[0;31m FAILED---------------\033[0;0m -l abc"
fi

output=$(./a.out -l)
output1='Not enough options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 16 \033[0;32m PASS \033[0;0m -l"
else
    echo -e "Test 16 \033[0;31m FAILED---------------\033[0;0m -l"
fi

output=$(./a.out first.csv)
output1='Cannot open one or more given files'
if [ "$output" = "$output1" ]; then
    echo -e "Test 17 \033[0;32m PASS \033[0;0m first.csv"
else
    echo -e "Test 17 \033[0;31m FAILED---------------\033[0;0m first.csv"
fi

rm meetingData.csv
touch meetingData.csv
output=$(./a.out meetingData.csv)
output1='No data to process'
if [ "$output" = "$output1" ]; then
    echo -e "Test 18 \033[0;32m PASS \033[0;0m empty file"
else
    echo -e "Test 18 \033[0;31m FAILED---------------\033[0;0m empty file"
fi
echo "Ashley_Parry,25,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26
Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv

output=$(./a.out -p 5)
output1='Only .csv files should be given as inputs.'
if [ "$output" = "$output1" ]; then
    echo -e "Test 19 \033[0;32m PASS \033[0;0m -p 5"
else
    echo -e "Test 19 \033[0;31m FAILED---------------\033[0;0m =p 5"
fi

output=$(./a.out -123.csv)
output1='Invalid option [-123.csv]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 20 \033[0;32m PASS \033[0;0m -123.csv" 
else
    echo -e "Test 20 \033[0;31m FAILED---------------\033[0;0m -123.csv"
fi

echo "Ashley_Parry,25,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26

Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv
output=$(./a.out meetingData.csv)
output1='File/s contain wrong entries.'
if [ "$output" = "$output1" ]; then
    echo -e "Test 21 \033[0;32m PASS \033[0;0m file with empty line"
else
    echo -e "Test 21 \033[0;31m FAILED---------------\033[0;0m file with empty line"
fi

echo "Ashley_Parry,25a,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26
Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv
output=$(./a.out meetingData.csv)
output1=$(./samplev1 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 22 \033[0;32m PASS \033[0;0m Ashley_Parry,25a,1:38:06"
else
    echo -e "Test 22 \033[0;31m FAILED---------------\033[0;0m Ashley_Parry,25a,1:38:06"
fi

echo "Ashley_Parry,25,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26
Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv

output=$(./a.out meetingData.csv -t)
output1=$(./samplev1 meetingData.csv -t)
if [ "$output" = "$output1" ]; then
    echo -e "Test 23 \033[0;32m PASS \033[0;0m meetingData.csv -t"
else
    echo -e "Test 23 \033[0;31m FAILED---------------\033[0;0m meetingData.csv -t"
fi

output=$(./a.out meetingData.csv -t --scaled)
output1=$(./samplev1 meetingData.csv -t --scaled)
if [ "$output" = "$output1" ]; then
    echo -e "Test 24 \033[0;32m PASS \033[0;0m meetingData.csv -t --scaled"
else
    echo -e "Test 24 \033[0;31m FAILED---------------\033[0;0m meetingData.csv -t --scaled"
fi

output=$(./a.out meetingData.csv  meetingData.csv  meetingData.csv)
output1=$(./samplev1 meetingData.csv  meetingData.csv  meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 25 \033[0;32m PASS \033[0;0m meetingData.csv  meetingData.csv  meetingData.csv"
else
    echo -e "Test 25 \033[0;31m FAILED---------------\033[0;0m meetingData.csv  meetingData.csv  meetingData.csv"
fi


echo "Ashley_Parryasfasdfasfasfasdfasfasfasdfasdfasdfsafsadfasfsafasdfasfadfasasdfsafasfasdfasfdfasfsa,25,1:38:06" > meetingData.csv
output=$(./a.out meetingData.csv)
output1=$(./samplev1 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 26 \033[0;32m PASS \033[0;0m very long name"
else
    echo -e "Test 26 \033[0;31m FAILED---------------\033[0;0m very long name"
fi

echo "Ashley_Parryasfasdfasfasfasdfasfasfasdfasdfasdfsafsadfasfsafasdfasfadfasasdfsafasfasdfasfdfasfsa,25,1:38:06" > meetingData.csv
output=$(./a.out meetingData.csv -t)
output1='
                                                                                                  │
 Ashley_Parryasfasdfasfasfasdfasfasfasdfasdfasdfsafsadfasfsafasdfasfadfasasdfsafasfasdfasfdfasfsa │98
                                                                                                  │
                                                                                                  │
                                                                                                  └'
if [ "$output" = "$output1" ]; then
    echo -e "Test 27 \033[0;32m PASS \033[0;0m long name -t"
else
    echo -e "Test 27 \033[0;31m FAILED---------------\033[0;0m long name -t"
fi


echo "Ashley_Parryasfasdfasfasfasdfasfasfasdfasdfasdfsafsadfasfsafasdfasfadfasasdfsafasfasdfasfdfasfsa,25,1:38:06" > meetingData.csv
output=$(./a.out meetingData.csv -p)
output1='
                                                                                                  │
 Ashley_Parryasfasdfasfasfasdfasfasfasdfasdfasdfsafsadfasfsafasdfasfadfasasdfsafasfasdfasfdfasfsa │25
                                                                                                  │
                                                                                                  │
                                                                                                  └'
if [ "$output" = "$output1" ]; then
    echo -e "Test 28 \033[0;32m PASS \033[0;0m long name -p"
else
    echo -e "Test 28 \033[0;31m FAILED---------------\033[0;0m long name -p"
fi


output=$(./a.out meetingData.csv --scaledd)
output1='Invalid option [--scaledd]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 29 \033[0;32m PASS \033[0;0m meetingData.csv --scaledd"
else
    echo -e "Test 29 \033[0;31m FAILED---------------\033[0;0m meetingData.csv --scaledd"
fi

output=$(./a.out -h)
output1='Invalid option [-h]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 30 \033[0;32m PASS \033[0;0m -h"
else
    echo -e "Test 30 \033[0;31m FAILED---------------\033[0;0m -h"
fi

output=$(./a.out -file.csv)
output1='Invalid option [-file.csv]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 31 \033[0;32m PASS \033[0;0m -file.csv"
else
    echo -e "Test 31 \033[0;31m FAILED---------------\033[0;0m -file.csv"
fi

output=$(./a.out -someotherFile.csv)
output1='Invalid option [-someotherFile.csv]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 32 \033[0;32m PASS \033[0;0m -someotherFile.csv"
else
    echo -e "Test 32 \033[0;31m FAILED---------------\033[0;0m -someotherFile.csv"
fi

output=$(./a.out 10 -l)
output1='Not enough options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 33 \033[0;32m PASS \033[0;0m 10 -l"
else
    echo -e "Test 33 \033[0;31m FAILED---------------\033[0;0m 10 -l"
fi

output=$(./a.out unnamedFile.csv -l)
output1='Not enough options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo -e "Test 34 \033[0;32m PASS \033[0;0m unnamedFile.csv -l"
else
    echo -e "Test 34 \033[0;31m FAILED---------------\033[0;0m unnamedFile.csv -l"
fi

output=$(./a.out -l 2 MEETINGDATA.CSV)
output1='Only .csv files should be given as inputs.'
if [ "$output" = "$output1" ]; then
    echo -e "Test 35 \033[0;32m PASS \033[0;0m -l 2 MEETINGDATA.CSV"
else
    echo -e "Test 35 \033[0;31m FAILED---------------\033[0;0m -l 2 MEETINGDATA.CSV"
fi

output=$(./a.out meetingData.csv)
output1=$(./samplev1 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 36 \033[0;32m PASS \033[0;0m meetingData.csv"
else
    echo -e "Test 36 \033[0;31m FAILED---------------\033[0;0m meetingData.csv"
fi

echo "Ashley_Parry,2513:38:06" > meetingData.csv
output=$(./a.out meetingData.csv)
output1=$(./samplev1 meetingData.csv)
if [ "$output" = "$output1" ]; then
    echo -e "Test 37 \033[0;32m PASS \033[0;0m no time given in csv"
else
    echo -e "Test 37 \033[0;31m FAILED---------------\033[0;0m no time given in csv"
fi

echo "Ashley_Parry,25,13:38:abc" > meetingData.csv
output=$(./a.out meetingData.csv -t)
output1=$(./samplev1 meetingData.csv -t )
if [ "$output" = "$output1" ]; then
    echo -e "Test 37 \033[0;32m PASS \033[0;0m abc for seconds, -t"
else
    echo -e "Test 37 \033[0;31m FAILED---------------\033[0;0m abc for seconds, -t"
fi

echo "Ashley_Parry,25,13:38:123,,,,,," > meetingData.csv
output=$(./a.out meetingData.csv -t)
output1=$(./samplev1 meetingData.csv -t )
if [ "$output" = "$output1" ]; then
    echo -e "Test 38 \033[0;32m PASS \033[0;0m more commas at the end"
else
    echo -e "Test 38 \033[0;31m FAILED---------------\033[0;0m more commas at the end"
fi

echo "Ashley_Parry,,,,,25,13:38:123" > meetingData.csv
output=$(./a.out meetingData.csv -t)
output1=$(./samplev1 meetingData.csv -t )
if [ "$output" = "$output1" ]; then
    echo -e "Test 39 \033[0;32m PASS \033[0;0m more commas in the middle"
else
    echo -e "Test 39 \033[0;31m FAILED---------------\033[0;0m more commas in the middle"
fi






echo "Ashley_Parry,25,1:38:06
Namal_Perera,12,2:24:56
Namal_Perera,197,2:04:01
Prabath_Silva,6,0:16:46
Bethany_William,9,1:49:12
Ashley_Parry,15,1:33:26
Namal_Perera,3,0:04:26
Aaliya_Bruce,2,0:03:37
Aaliya_Bruce,2,0:00:59
Prabath_Silva,2,0:32:26
Waruni_Fernando,15,2:38:42
Raul_Oliver,7,1:12:20
Aaliya_Bruce,2,0:00:54
Dr_Rajitha_Karunarathna,3,0:15:16
Raul_Oliver,3,0:02:10
Jasper_Jensen,4,0:32:05
Jasper_Jensen,4,0:08:37
Namal_Perera,3,1:37:40
Chamira_Perera,3,0:46:35
Wasana_Tennekoon,8,0:40:13
Dr_Kamal_Jayasooriya,14,0:51:41
Raul_Oliver,2,2:05:05" > meetingData.csv