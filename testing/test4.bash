#!/bin/bash

echo "~~~ TEST 4 ~~~"

echo -e "Please ensure that you have compiled the shared librarires and executable using \"make\" in the parent directory ( :\n"

echo -e "\n\nYou will be prompted to enter a string. Please enter the string: She said: \"Hello\""
echo -e "After that please enter the string: exit\n\n\n"

(./../src/modFormatter -p ../modules -m quote,paren) 2> /dev/null

echo -e "\n\nThe program should have printed the string: (\"She said \\\"Hello\\\"\") and (\"exit\")"
echo "if it did that, it was a success!"