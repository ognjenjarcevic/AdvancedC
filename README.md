Author: Ognjen Jarcevic

# Task of this assignment

Make a module that represents linked list data structure. Build the module as a dynamic library. Create a module that represents a delta encoded list, building on top of the list module. Implement the following functionality: Make the user capable of adding a new element to the delta list, placing it automatically in the right spot. C17 (C standard revision) is to be used.

# Design notes:
- Generally, const parameters aren't used in function declarations as much as they should, as they make the calls more messy and cumbersome to perform. Oftentimes they decrease the code readability.
- Many guard clauses are present in the list modules, as the code is supposed to be safe to execute and use. Most of them connected to function's input parameters.
- list.h module implement a mechanism for porting to other platforms: MODULE SETTINGS section. Those settings are used by list modules in order to make change of types easy, fast, and more resistant to errors.

## main.c
- The file is just a test case playground, as the main task of this project is demonstrating how to build a safe, portable software library. The file is there to try to mess with the library, and test its safety limits. It doesn't adhere to safe coding practices. It doesn't call the functions as it should, using bare ints for the calls instead of proper types that should be used

# Adhering and deviations from MISRA-C 2004 standard:

These common warnings and errors occur when running checks to compare the source code of this project to MISRA-C 2004 standard:

## main.c
- warning: (MISRA-C:2004 20.9/R) The input/output library <stdio.h> shall not be used in production code.
 	- This warning must occur as this is a test module, this file isn't a part of production code

## list.h
- Declaration of typedef List: List and ListStruct are named differently due to MISRA standard not allowing for the same name to be used for both.
- warning: (MISRA-C:2004 2.2/R) Source code shall only use /* ... */ style comments
	- MISRA-C:2012 (which covers C99) DOES allow // style comments.
- warning: (MISRA-C:2004 19.4/R) C macros shall only expand to a braced initialiser, a constant, a string literal, a parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct
	- This occurs due to the feature of module settings, which help with multiplatform portability and support. These warnings can be easily removed by replacing every macro occurence with its actual contents upon finalization of the port to the target platform.
- warning: (MISRA-C:2004 6.3/A) typedefs that indicate size and signedness should be used in place of the basic numerical types
	- This occurs due to all functions returning regular ints. int is used for easier error handling for the function caller. Those values can be changed to another type if neccessary.

## list.c
- warning: (MISRA-C:2004 12.5/R) The operands of a logical && or || shall be primary-expressions
	- Happens due to overleliance on operand priority
- errors: type name is not allowed, expected a ";", error: identifier "i" is undefined
	- Declaring a variable inside for loop, it is covered by C17 standard
- warning: (MISRA-C:2004 17.4/R) Array indexing shall be the only allowed form of pointer arithmetic
	- General use of \[i+1\] or \[i-1\] produces these warnings
- warning: (MISRA-C:2004 14.7/R)A function shall have a single point of exit at the end of the function
	- Happens due to guard clauses being present in all functions

## delta_list.h and delta_list.c
Similar warnings occur as in list.h and list.c

# Build instructions (dynamic library):

## Manually:

1. Open command line tool of choice
1. Position to *list* directory
2. Run: `gcc list.c -fpic -c`
3. Run: `gcc -shared -o liblist.so list.o`
4. Position to *delta_list* directory
5. Run: `gcc delta_list.c -I ../list/ -fpic -c`
6. Run: `gcc -shared -o libdelta_list.so delta_list.o`
7. Position to main directory, where *list* and *delta_list* directories are located.
8. Run: `gcc -I list/ -I delta_list/ -L list/ -L delta_list/ main.c -l list -l delta_list -o main.o`

## Automatically
Performs the same build process as the manual method, but automatically in its entirety using a bash script.

Run: `bash build.sh` from the main directory.

# Run instructions (dynamic library):

Due to the dynamic library specifics additional environment variable must be added before running the final .o file
0. Run from the main directory (one time only).
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/list:$PWD/delta_list`
1. Run `./main.o` to start the program