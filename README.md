# Will Pringle - A3 - cis 3050
~
# Dynamic-loading-and-multi-platform-compilation
This assignment will let us talk aboutwriting portable, multi-platform codethat loads and uses pluggablemodules. This is a very commonsystem design pattern.Note that this is an individualassignment.

# Design

This program follows the design given for the assignment. It takes in a colon (or semi colon on Windows) list of module paths, a comma seperated list of modules, and either a file name or if no file name is passed it takes in user input with a triple chevron prompt (>>>). 

The system starts by loading each module into an array data structure (discussed more in the memory management section). Then it iterates through each line of the file or from STDIN and applies a tranformation function unique to each module to the string line. It will apply these transformation functions in the same order as, and for the number of, modules that were passed when the program was started. Then it will print the lines to the screen.

Refer to the memory management section for details on how the memory i

## Memory Management
Memory is managed by creating a dynamicly sized array based on the number of modules passed, once it has opened all of the modules, they are placed in the array. Then the program is executed. During this phase any temporary memory alocated (for example for each line of a text file) is freed directly after use. Finally, after completion, the dynamic array of modules is iterated through a loop that closes each library, and then frees the array data structure.


# Testing

Run individual tests by typing ./testN.bash where N represents the test number. For example ./test1.bash

There are 5 tests, test1.bash, test2.bash, test3.bash, test4.bash, test5.bash

#### Test 1
Purpose: verify the code can properly dynamically allocate memory for a long line from a text file as well as properly free memory in all oter parts of the system such as loading and closing a dynanmic library.

**How it shows it works**: This will test if the system properly applies the function in the shared library to the text entered. Furthermore, it will test the memory management section of the assignment by showing the valgrind output after running  and applying a function to a string. Ensure reading from a file works properly.

#### Test 2
Purpose: check if multiple modules can be loaded successfully. It also tests an edge case by testing 64 modules at once (the maximum defined for the system). 

**How it shows it works**:  This checks if all four modules can be loaded and properly applied to a string send in. This also tests if multiple modules can be loaded. Also this tests if the maximum amont of modules can be loaded by loading 64. Also, this will test if the system properly applies the function in the shared library to the text entered. Ensure reading from a file works properly.

#### Test 3
Purpose: check if multiple invalid modpaths separated by colon characters with a valid one in the middle will work. Ensure reading from a file works properly.

**How it shows it works**: This checks if the modpath can be properly parsed. Also, this will test if the system properly applies the function in the shared library to the text entered.

#### Test 4
Purpose: ensure the user input works

**How it shows it works**: This will check if the user input prompt works. This will also check if quote functionality from the quote module works properly. 

#### Test 5
Purpose: Ensure the modules are applied in the correct order.

**How it shows it works**: This will check if paren, quote, box, and shout are applied in the correct order. Shout is idempotent and associative - so this test checks if shout works in general. This also tests if the initialization and finalization (de-initialization) works. THis also tests if the paren, quote, box, and all work properly.

