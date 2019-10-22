#! /bin/bash
#Get desired path
var=/home/$USER/fer_projekt
#Type in a number of minutes you want to check
echo "Koliko minuta zelite: " 
#Get user input and save it in variable input
read input
#Find all modified files at desired path and compress them in backup.tgz file
find $var -type f -mmin -$input > temp.txt | tar czf backup.tgz --files-from=- --null
#Print the files in terminal
cat temp.txt