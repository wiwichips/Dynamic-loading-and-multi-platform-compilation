# Dynamic-loading-and-multi-platform-compilation
This assignment will let us talk aboutwriting portable, multi-platform codethat loads and uses pluggablemodules. This is a very commonsystem design pattern.Note that this is an individualassignment.

# Design
## Memory Management
Memory is managed by loading all modules into a dynamicly allocated array at the start of the program execution. After applying the functions from the modules to the 


# Testing

#### Test 1
Purpose: verify the code can properly dynamically allocate memory for a long line from a text file as well as properly free memory in all oter parts of the system such as loading and closing a dynanmic library.

**How it shows it works**: This will test if the system properly applies the function in the shared library to the text entered. Furthermore, it will test the memory management section of the assignment by showing the valgrind output after running  and applying a function to a string. 

#### Test 2
Purpose: check if multiple modules can be loaded successfully. It also tests an edge case by testing 64 modules at once (the maximum defined for the system). 

**How it shows it works**:  This checks if all four modules can be loaded and properly applied to a string send in. This also tests if multiple modules can be loaded. Also this tests if the maximum amont of modules can be loaded by loading 64. Also, this will test if the system properly applies the function in the shared library to the text entered.

#### Test 3
Purpose: check if multiple invalid modpaths separated by colon characters with a valid one in the middle will work.

**How it shows it works**: This checks if the modpath can be properly parsed. Also, this will test if the system properly applies the function in the shared library to the text entered.

