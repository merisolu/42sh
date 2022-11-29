#!/bin/sh
source 1.sh
norminette > /tmp/file1
echo $? >> /tmp/file1
cat -e author >> /tmp/file1

echo Minishell stuff.... >> /tmp/file1

echo "Fork & execve"  >> /tmp/file1
foo >> /tmp/file1 2>&1
/bin/ls >> /tmp/file1
/bin/ls -laF >> /tmp/file1
/bin/ls -l -a -F >> /tmp/file1

echo Builtins >> /tmp/file1
echo "it works" >> /tmp/file1
echo it works >> /tmp/file1
echo -n it works >> /tmp/file1
echo he"llo     'w'o"rld >> /tmp/file1
echo "" hello >> /tmp/file1

export temp $PWD
cd /Users
/bin/pwd >> /tmp/file1 
cd bocal
/bin/pwd >> /tmp/file1
cd
/bin/pwd >> /tmp/file1
cd - >> /tmp/file1
/bin/pwd >> /tmp/file1
cd ~/Documents
/bin/pwd >> /tmp/file1
cd $temp
unset temp

echo Environment management >> /tmp/file1
env >> /tmp/file1
export FOO bar
env >> /tmp/file1
echo $FOO >> /tmp/file1
/usr/bin/env >> /tmp/file1
unset FOO
env >> /tmp/file1
echo $FOO >> /tmp/file1
/usr/bin/env >> /tmp/file1

echo PATH management >> /tmp/file1
export temp $PATH
unset PATH
export PATH "/bin:/usr/bin"
ls >> /tmp/file1
unset PATH
ls >> /tmp/file1 2>&1
/bin/ls >> /tmp/file1
export PATH $temp 
unset temp

echo cmd line management >> /tmp/file1
" " >> /tmp/file1 2>&1
"	    	" >> /tmp/file1 2>&1
    /bin/ls     -l       -A  >> /tmp/file1

echo pipes: >> /tmp/file1
ls | cat -e >> /tmp/file1
ls | sort -r | cat -e >> /tmp/file1
base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g' >> /tmp/file1

echo redirections: >> /tmp/file1
echo "testing redirections," > test.txt
echo "with multiple lines" >> test.txt
wc -c < test.txt >> /tmp/file1
rm test.txt

echo separators: >> /tmp/file1
echo no newfile >> /tmp/file1; ls -1 >> /tmp/file1; touch newfile ; echo  >> /tmp/file1; echo newfile >> /tmp/file1; ls -1 >> /tmp/fil1e
rm newfile

echo A lil bit of everything: >> /tmp/file1
mkdir test ; cd test ; ls -a >> /tmp/file1 ; ls | cat | wc -c > fifi ; cat fifi >> /tmp/fil1e
cd .. ; rm -rf test

echo file descriptor aggregation >> /tmp/file1
rm nosuchfile 2>&- >> /tmp/file1
rm nosuchfile 2>&1 | cat -e >> /tmp/file1
echo "No dollar character" 1>&2 | cat -e 

diff /tmp/file tmp/file1
