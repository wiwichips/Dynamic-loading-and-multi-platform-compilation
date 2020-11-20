#!/bin/bash

echo "~~~ TEST 5 ~~~"

echo -e "Please ensure that you have compiled the shared librarires and executable using \"make\" in the parent directory ( :\n"

echo -e "\n\nThis will test if the modules are applied in teh correct order as specified."

echo -e "hello world" > tempFile.txt

./../src/modFormatter -p ../modules -m paren,quote,box,shout tempFile.txt

rm -f tempFile.txt

echo -e "\n\nThe program should have printed the string: [\"(HELLO WORLD)\"]"
echo "if it did that (inbetween the initialization and finalization print statements) it was a success!"