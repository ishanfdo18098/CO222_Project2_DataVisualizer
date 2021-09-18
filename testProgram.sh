#/bin/bash


output=$(./a.out)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 1 PASS"
else
    echo "Test 1 FAILED---------------"
fi

output=$(./a.out meetingData.csv -m)
output1='
                         │░░░░░░░░░
 Namal_Perera            │░░░░░░░░░4
                         │░░░░░░░░░
                         │
                         │░░░░░░░
 Aaliya_Bruce            │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░░░░
 Raul_Oliver             │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░
 Ashley_Parry            │░░░░2
                         │░░░░
                         │
                         │░░░░
 Prabath_Silva           │░░░░2
                         │░░░░
                         │
                         │░░░░
 Jasper_Jensen           │░░░░2
                         │░░░░
                         │
                         │░░
 Bethany_William         │░░1
                         │░░
                         │
                         │░░
 Waruni_Fernando         │░░1
                         │░░
                         │
                         │░░
 Dr_Rajitha_Karunarathna │░░1
                         │░░
                         │
                         │░░
 Chamira_Perera          │░░1
                         │░░
                         │
                         └──────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 2 PASS"
else
    echo "Test 2 FAILED---------------"
fi

output=$(./a.out -l 5)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 3 PASS"
else
    echo "Test 3 FAILED---------------"
fi

output=$(./a.out -l 5 meetingData.csv)
output1='
               │░░░░░░░░░░░
 Namal_Perera  │░░░░░░░░░░░4
               │░░░░░░░░░░░
               │
               │░░░░░░░░
 Aaliya_Bruce  │░░░░░░░░3
               │░░░░░░░░
               │
               │░░░░░░░░
 Raul_Oliver   │░░░░░░░░3
               │░░░░░░░░
               │
               │░░░░░
 Ashley_Parry  │░░░░░2
               │░░░░░
               │
               │░░░░░
 Prabath_Silva │░░░░░2
               │░░░░░
               │
               └────────────────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 4 PASS"
else
    echo "Test 4 FAILED---------------"
fi

output=$(./a.out -l 5 meetingData.csv -p)
output1='
                      │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 Namal_Perera         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░215
                      │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
                      │
                      │░░░░░░
 Ashley_Parry         │░░░░░░40
                      │░░░░░░
                      │
                      │░░
 Waruni_Fernando      │░░15
                      │░░
                      │
                      │░░
 Dr_Kamal_Jayasooriya │░░14
                      │░░
                      │
                      │░
 Raul_Oliver          │░12
                      │░
                      │
                      └─────────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 5 PASS"
else
    echo "Test 5 FAILED---------------"
fi

output=$(./a.out -l -5)
output1='Invalid option(negative) for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 6 PASS"
else
    echo "Test 6 FAILED---------------"
fi

output=$(./a.out meeting)
output1='Only .csv files should be given as inputs.'
if [ "$output" = "$output1" ]; then
    echo "Test 7 PASS"
else
    echo "Test 7 FAILED---------------"
fi

output=$(./a.out -m -t)
output1='Cannot plot multiple parameters in same graph.
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 8 PASS"
else
    echo "Test 8 FAILED---------------"
fi

output=$(./a.out -l 0)
output1=''
if [ "$output" = "$output1" ]; then
    echo "Test 9 PASS"
else
    echo "Test 9 FAILED---------------"
fi

output=$(./a.out -l 100 meetingData.csv)
output1='
                         │░░░░░░░░░
 Namal_Perera            │░░░░░░░░░4
                         │░░░░░░░░░
                         │
                         │░░░░░░░
 Aaliya_Bruce            │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░░░░
 Raul_Oliver             │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░
 Ashley_Parry            │░░░░2
                         │░░░░
                         │
                         │░░░░
 Prabath_Silva           │░░░░2
                         │░░░░
                         │
                         │░░░░
 Jasper_Jensen           │░░░░2
                         │░░░░
                         │
                         │░░
 Bethany_William         │░░1
                         │░░
                         │
                         │░░
 Waruni_Fernando         │░░1
                         │░░
                         │
                         │░░
 Dr_Rajitha_Karunarathna │░░1
                         │░░
                         │
                         │░░
 Chamira_Perera          │░░1
                         │░░
                         │
                         │░░
 Wasana_Tennekoon        │░░1
                         │░░
                         │
                         │░░
 Dr_Kamal_Jayasooriya    │░░1
                         │░░
                         │
                         └──────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 10 PASS"
else
    echo "Test 10 FAILED---------------"
fi

output=$(./a.out -n)
output1='Invalid option [-n]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 11 PASS"
else
    echo "Test 11 FAILED---------------"
fi

output=$(./a.out --scaled)
output1='No input files were given
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 12 PASS"
else
    echo "Test 12 FAILED---------------"
fi

output=$(./a.out meetingData.csv meetingData.csv)
output1='
                         │░░░░░░░░░
 Namal_Perera            │░░░░░░░░░8
                         │░░░░░░░░░
                         │
                         │░░░░░░░
 Aaliya_Bruce            │░░░░░░░6
                         │░░░░░░░
                         │
                         │░░░░░░░
 Raul_Oliver             │░░░░░░░6
                         │░░░░░░░
                         │
                         │░░░░
 Ashley_Parry            │░░░░4
                         │░░░░
                         │
                         │░░░░
 Prabath_Silva           │░░░░4
                         │░░░░
                         │
                         │░░░░
 Jasper_Jensen           │░░░░4
                         │░░░░
                         │
                         │░░
 Bethany_William         │░░2
                         │░░
                         │
                         │░░
 Waruni_Fernando         │░░2
                         │░░
                         │
                         │░░
 Dr_Rajitha_Karunarathna │░░2
                         │░░
                         │
                         │░░
 Chamira_Perera          │░░2
                         │░░
                         │
                         └──────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 13 PASS"
else
    echo "Test 13 FAILED---------------"
fi

output=$(./a.out --scaled meetingData.csv)
output1='
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 Namal_Perera            │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░4
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 Aaliya_Bruce            │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░3
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 Raul_Oliver             │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░3
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
 Ashley_Parry            │░░░░░░░░░░░░░░░░░░░░░░░░░░2
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
 Prabath_Silva           │░░░░░░░░░░░░░░░░░░░░░░░░░░2
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
 Jasper_Jensen           │░░░░░░░░░░░░░░░░░░░░░░░░░░2
                         │░░░░░░░░░░░░░░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░
 Bethany_William         │░░░░░░░░░░░░░1
                         │░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░
 Waruni_Fernando         │░░░░░░░░░░░░░1
                         │░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░
 Dr_Rajitha_Karunarathna │░░░░░░░░░░░░░1
                         │░░░░░░░░░░░░░
                         │
                         │░░░░░░░░░░░░░
 Chamira_Perera          │░░░░░░░░░░░░░1
                         │░░░░░░░░░░░░░
                         │
                         └──────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 14 PASS"
else
    echo "Test 14 FAILED---------------"
fi

output=$(./a.out -l abc)
output1='Invalid options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 15 PASS"
else
    echo "Test 15 FAILED---------------"
fi

output=$(./a.out -l)
output1='Not enough options for [-l]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 16 PASS"
else
    echo "Test 16 FAILED---------------"
fi

output=$(./a.out first.csv)
output1='Cannot open one or more given files'
if [ "$output" = "$output1" ]; then
    echo "Test 17 PASS"
else
    echo "Test 17 FAILED---------------"
fi

touch testEmpty.csv
output=$(./a.out testEmpty.csv)
output1='No data to process'
if [ "$output" = "$output1" ]; then
    echo "Test 18 PASS"
else
    echo "Test 18 FAILED---------------"
fi

output=$(./a.out -p 5)
output1='Only .csv files should be given as inputs.'
if [ "$output" = "$output1" ]; then
    echo "Test 19 PASS"
else
    echo "Test 19 FAILED---------------"
fi

output=$(./a.out -123.csv)
output1='Invalid option [-123.csv]
usage: ./a.out [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..'
if [ "$output" = "$output1" ]; then
    echo "Test 20 PASS"
else
    echo "Test 20 FAILED---------------"
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
Raul_Oliver,2,2:05:05" > testcsv.csv
output=$(./a.out testcsv.csv)
output1='File/s contain wrong entries.'
if [ "$output" = "$output1" ]; then
    echo "Test 21 PASS"
else
    echo "Test 21 FAILED---------------"
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
Raul_Oliver,2,2:05:05" > testcsv.csv
output=$(./a.out testcsv.csv)
output1='
                         │░░░░░░░░░
 Namal_Perera            │░░░░░░░░░4
                         │░░░░░░░░░
                         │
                         │░░░░░░░
 Aaliya_Bruce            │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░░░░
 Raul_Oliver             │░░░░░░░3
                         │░░░░░░░
                         │
                         │░░░░
 Ashley_Parry            │░░░░2
                         │░░░░
                         │
                         │░░░░
 Prabath_Silva           │░░░░2
                         │░░░░
                         │
                         │░░░░
 Jasper_Jensen           │░░░░2
                         │░░░░
                         │
                         │░░
 Bethany_William         │░░1
                         │░░
                         │
                         │░░
 Waruni_Fernando         │░░1
                         │░░
                         │
                         │░░
 Dr_Rajitha_Karunarathna │░░1
                         │░░
                         │
                         │░░
 Chamira_Perera          │░░1
                         │░░
                         │
                         └──────────────────────────────────────────────────────'
if [ "$output" = "$output1" ]; then
    echo "Test 22 PASS"
else
    echo "Test 22 FAILED---------------"
fi
