#!/bin/bash

# tests 64 modules

echo "~~~ TEST 2 ~~~"

echo -e "Please ensure that you have compiled the shared librarires and executable using \"make\" in the parent directory ( :\n"

echo "This test confirms that 64 modules can be run at once"

echo -e "Example File\nwith multiple lines\nand some quotes \"\"\nfor testing" > tempFile.txt

./../src/modFormatter -p ../modules -m box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren,box,shout,quote,paren tempFile.txt

rm -f tempFile.txt

echo -e "\n\nTest is a success if all 64 modules have been loaded, called, and unloaded (de-initialized)"
echo "please refer to the ouptut above to verify this"