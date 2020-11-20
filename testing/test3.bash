#!/bin/bash

echo "~~~ TEST 3 ~~~"

echo -e "Please ensure that you have compiled the shared librarires and executable using \"make\" in the parent directory ( :\n"

echo -e "\nThis test checks if the modpath functionality works"

echo -e "Example File\nwith multiple lines\nand some quotes \"\"\nfor testing" > tempFile.txt

./../src/modFormatter -p test:/thisDirNoExist:../modules:anothertest -m box tempFile.txt

rm -f tempFile.txt

echo -e "\n\nThis test is a pass if the correct directory is found and applied to the text"