## Logs Macros - HOWTO

# Why?

The rationale behind these log macros is to have the possibility to centrally control log macros and:
  - compile out all logs by simply commenting out one define
  - fine-grained control on which cpp files are allowed to generate logs so to reduce clutter

# How to include it in your project

Include the logmacros.pri in your project pro file. This will include the following file:

- logmacros.h, a file where all the log macros are defined.


# How to use the logs macros

Create a file called activelogs.h, I suggest in the same directory as your pro file, and add it to your project.
Copy the following content in it (or just take the one you find in the same directory as this file):

	#ifndef ACTIVE_LOGS_H
	#define ACTIVE_LOGS_H

	// comment/uncomment these to disable/enable the logs
	#define ENABLE_LOGS
	#define ENABLE_LOGS_VERBOSE

	#ifdef ENABLE_LOGS
		// comment/uncomment these to disable/enable debug/warning/critical level logs
		#define DEBUG_LEVEL_ACTIVE
		#define WARNING_LEVEL_ACTIVE
		#define CRITICAL_LEVEL_ACTIVE
		
	#endif // ENABLE_LOGS
	#endif // ACTIVE_LOGS_H

After you have included the logmacros.pri file in your project, whenever you create a new cpp file,
add at the beginning of the file the following lines:

	#include "activelogs.h"
	#ifdef YOUR_CPP_UNIQUE_MACRO
		#define ENABLE_LOG_MACROS
	#endif
	#include "logmacros.h"

where YOUR_CPP_UNIQUE_MACRO is a unique macro defined explicitly for that file
(I would suggest to use something meaningful such as the name of the class implemented in the file).

Just after copying those lines in your cpp file, create a new define in the activelogs.h file,
which will now look like this:


	#ifndef ACTIVE_LOGS_H
	#define ACTIVE_LOGS_H

	// comment/uncomment these to disable/enable the logs
	#define ENABLE_LOGS
	#define ENABLE_LOGS_VERBOSE

	#ifdef ENABLE_LOGS
		// comment/uncomment these to disable/enable debug/warning/critical level logs
		#define DEBUG_LEVEL_ACTIVE
		#define WARNING_LEVEL_ACTIVE
		#define CRITICAL_LEVEL_ACTIVE
		
		
		#define YOUR_CPP_UNIQUE_MACRO
		
	#endif // ENABLE_LOGS
	#endif // ACTIVE_LOGS_H

now it is possible to control whether that cpp file is allowed to generate logs by simply
commenting/uncommenting the relevant #define YOUR_CPP_UNIQUE_MACRO.

Per each cpp file, if the macro referring to that file is commented out,
(or the ENABLE_LOGS macro is commented out altogether) the log macros will be compiled out.



# Test it!

In the test directory you will find a simple console application which generates the powerset
given a set of input numbers (see main.cpp, you can add/remove some modifying the relevant code).
By playing with the defines in the activelogs.h you can see how the differences in the log file
generated at each run of the application.
