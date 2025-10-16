/*========  Proforma : EEET2250 Lab Code Submission 3 OUSB class and traffic light state machine ===========
Proforma version number: 2025.001.a (updated 01-05-2025)

Document Revision Details:
			- 2025.001.a (01-05-2025) - Original version


PURPOSE:
This file is a proforma for the EEET2250 Lab Code Submission 3: OUSB class and traffic light state machine
operations with the OUSB Board. This file defines the "Code Submission Functionality" portion of the
assessment task. The total grade contribution of lab Code Submission 3 is worth 10% of the available course
grade.

You must extend this C++ program to cope with the functionality identified below in the GENERAL
SPECIFICATIONS, PROGRAM STRUCTURE and SPECIFICATIONS/FUNCTIONAL REQURMENTS and ERROR HANDLING Sections
within this document. It is highly recommended to complete the specifications/requirements in the
order that they appear in the text below. Additionally, you are required to define an OUSB Class
and use a OUSB Object to handle all OUSB functionality within your code solution. Code Submission
Functionality will be graded by the Autotester and be worth 70% of the grade for this assessment
item. The remaining 30% of will be derived from the quality of the code/class implementation as a
scaled value obtained from the functionality score. The description of the code quality component
can be found in the rubric for lab code submission 3, named: "Rubric_For_Lab_Code_Submissions_Lab3.pdf"

As an example, if the code submission scores 70%, as graded by the autotester (for functionality) and
the OUSB class and pipe code are both implemented at HD level, then the final grade will be 70%. However,
if the OUSB class and pipe code are both implemented at NN level, the final grade for the assessment
will be 49% as the autotester grade only contributes to 70% of the assessment grade.

Note: You must submit your solution as part of this file, however you can delete the comments/specifications
in your final submission if you find it easier to work within this file. Please note that you should write
your solution within this file and submit this file with the correct naming convention as there are some
formatting features and libraries included in this proforma that the autotester is expecting. You can also
ignore this note and submit this file with the comments/specifications included with your solution.

OUSB USAGE:
All submissions will be tested using the OUSB Simulator (version 1.07) that has been renamed to:
 ousb.exe
This is so all students can test their code using a version of the OUSB interface which everyone has access
too. However, DO NOT use the ousbMotorsim or ousbsim command as part of your pipe code!!!  All pipe code
must use the 'ousb' command. Make sure you have downloaded and are using the latest version of the simulator
from the canvas shell. If your code works with a Physical OUSB Board (that also has the correct LED circuit
built) and you are only using the PORTB, PORTD, PINC or ADC pin 5 (adc 5) commands, your solution should work
just as well with the simulator - However it is recommended that all students check their code with the OUSB
Simulator prior to submission given that the autotester will use the simulator in-place of a physical OUSB Board.

GOAL:
To write a C++ Windows Console Application in Visual Studio that implements access to the OUSB Board using
classes. Your program must implement a traffic light state machine class called TrafficLight as well as
an OUSB class. Failure to instantiate and use OUSB and TrafficLight objects within your solution will result
is a large marks penalty. PORTB and PORTD of the OUSB Board will be used to indicate the current traffic
light state. Your solutions should also display console text with very specific formatting perform error
checking.

To put the problem into perceptive, the lab class set of physical OUSB Boards have three LEDs (Red, Yellow
and Green) that are wired into the OUSB Board prototype area. This lab uses these LEDs to represent traffic
light lamps. The standard bank of 8 LEDs connected to PORTB will also be used to represents a simplified
troubleshooting panel inside the traffic light control box (e.g. the box that is normally on the side of the
road at an intersection). The troubleshooting (PORTB) lights will have the light states as well as other
information encoded in the 8-bit. Both PORTB and PORTD are used to control the Red, Yellow and Green prototype
LEDs.

RESOURCES:
	1. Lecture and tutorial notes.
	2. Prescribed Text book and the "Teach Yourself C++ in 21 Days" PDF ebook.
	3. The Open-USB-IO Reference manual (PDF file on canvas under the "OUSB Board Resources" page
	4. The ousbSim.exe file on canvas, which will provide the simulated OUSB Board functionality

	   Note: If you don't have a physical OUSB Board with the correct LED traffic light components, you can
	   safely use the provided ousbSim.exe file in place of the ousb.exe file. To do this you need to rename
	   the ousbSim.exe to ousb.exe and replace the original ousb.exe file. Similar to the portb.txt file, a
	   portd.txt file will be created that represents the state of PORTD.

Note: Do not use ousbSim as the command in the pipe code for the formal submission as you will lose
most of the available marks. The autotester will only have the ousb.exe file available.

WARNINGS:
Avoid losing 10% by making sure the cout statement within the if (argc==1) code block in main()
correctly executes to print out your details: incorrect student number or email will result in a penalty.

It is preferred that you include the 's' in front of your student number in the first token. Your email
address should be a valid email address based of your student number (with a leading 's' character ) in the
correct format with the correct student.rmit.edu domain address structure as per general specification G2.

If your code, when run without any command line arguments, does not print out the correct cout
statement (with your details) to the console, you will lose a flat 10% off your final mark. That is,
if your code scores 54% and the cout information is incorrect your code will be reduced by a further
10% to a final mark of 44%.

Make sure you check the output of the if (argc==1) cout statement before you submit your final submission!!!!

SUBMISSION:
You will be required to rename this *.cpp to the following format:
	Lab3_s1234567.cpp
where the numbers 1234567 are your student number.

The file should then be uploaded via Canvas before the due date and time. You are only required
to upload this submission as a *.cpp file using the correct naming convention. No report is
required - only the *.cpp file which you have created.

Note: If you re-submit your solution to Canvas, it will be automatically be renamed with -1 or -2,
etc. attached to the end of your file. You can submit multiple times, however only your last
submission will count.

Note: 10 marks (i.e. 10% of available marks) per 24-hour period penalty will apply to late submissions
(inclusive of weekends and public holidays). Therefore, if you submit 1 minutes late, a flat 10% mark
penalty will be applied. Your last submission will be the file that is assessed and that submission
time will be used to determine the late penalty.

MARKING:
Your code will not be modified at all and must compile as received. Code that fails to compile will
score 0%. Your code must use the ousb command in all the pipe commands. Penalties for late marks
and missing or erroneous if (argv==1) cout statements, the lack of not using and implementing the
required class/objects to access the traffic light and OUSB Board, and/or lack of matching
_popen(...) and _pclose(...) pipe code will be applied to the final mark generated by the autotester
will be apply to your final mark generated by the autotester. Lowest possible score is 0% - no
negative marks. (see rubric PDF for requirements regarding use of classes and pipe code).

Marking has several components-
	1. your code will be checked for functionality.
	2. your code will be tested with erroneous input.
	3. The structure of your code will be assessed (see rubric PDF).
	4. You code will be checked to confirm that you have implemented matching _popen(...) and
	   _pclose(...) statements.

PLAGIARISM:
The submission must be your code solution in its entirety. If your code is found to be similar to
another submission it will be investigated for possible Academic Misconduct. Please respect the
academic process and make sure your submission complies with RMIT's Student Conduct Policy. See:
https://www.rmit.edu.au/about/governance-and-management/policies/student-conduct-policy
*/
/*
BACKGROUND INFORMATION:

SCHEMATIC FOR TRAFFIC LIGHT LEDs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following circuitry has been already added to a standard OUSB Board which are
in the class set.

Your C++ Program     OUSB       .  Components Soldered onto Prototype Area
on the PC            Board      .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			 ________           .
			|UNL2003A|          .                     Green LED
PB3	        |4     13|          .        270 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC0         |        |   pin 27 .
			|        |          .                     Yellow LED
PD5         |2     15|          .        100 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC1A        |        |   pin 23 .
			|        |          .                     Red LED
PD4         |1     16|          .        270 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC1B        |________|   pin 21 .
								.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NOTE: Yellow LED is lower intensity, hence the lower resistor value.

NOTE: Technically it is possible to do this lab on a physical OUSB Board that does not have
this circuit implemented.  It is also possible to do this lab just using the OUSB Simulator.

___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS (Mostly common to all three EEET2250 Laboratory Code Submissions):

G1.	You must rename your file to Lab3_s1234567.cpp, where 1234567 is your student number.
Your filename MUST NEVER EVER contain any spaces.  _under_score_is_Fine.
It is preferred that you include the 's' in front of your student number. Canvas will rename your
submission by adding a -1, -2 etc. if you resubmit your solution file - This is acceptable.

G2.	Edit the name/email address string in the main() function to your student number,
student email and student name.	The format of the student ID line is CSV (Comma Separated
Variables) with NO SPACES-
student_id,student_email,student_name
When the program is run without any operands i.e. simply the name of the executable such as:
Lab3_s1234567.exe
the program MUST print student ID string in Comma Separated Values (CSV) format with no
spaces. For example the following text should be outputted to the console updated with
your student details:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

G3.	All outputs are a single error character or a numerical number, as specified by the
FUNCTIONAL REQURMENTS, followed by a linefeed ( endl or \n).

G4.	DO NOT add more than what is specified to the expected console output. Do NOT add
additional information, text or comments to the output console that are not defined within
the SPECIFICATIONS/FUNCTIONAL REQURMENTS.

G5.	DO NOT use 'cin', system("pause"), getchar(), gets(), etc. type functions. Do NOT ask
for user input from the keyboard. All input MUST be specified on the command line separated
by blank spaces (i.e. use the argv and argc input parameters).

G6. DO NOT use the characters:  * / \  : ^ ? in your command line arguments as your user
input. These are special character and may not be processed as expected, potentially
resulting in undefined behaviour of your program.

G7. All input MUST be specified on the command line separated by blank spaces (i.e. use
the argc and argv[] input parameters). All input and output is case sensitive.

G8.	You should use the Integrated Debugging Environment (IDE) to change input arguments during
the development process.

G9.	When your code exits the 'main()' function using the 'return' command, you MUST
use zero as the return value. This requirement is for exiting the 'main()' function ONLY.
A return value other than zero will indicate that something went wrong to the autotester and
no marks will be awarded.

G10. User-defined functions and/or class declarations must be written before the 'main()'
function. This is a requirement of the Autotester and failure to do so will result in your code
scoring 0% as it will not be compiled correctly by the autotester. Do NOT put any functions/class
definitions after the 'main()' function or modify the comments and blank lines at the end of this
file.

G11. You MUST run this file as part of a Project - No other *.cpp or *.h files should be added
to your solution.

G12. You are not permitted to add any other #includes statements to your solution. The only
libraries permitted to be used are the ones predefined in this file.

G13. Under no circumstances is your code solution to contain any go_to labels - Please note that
the '_' has been added to this description so that this file does not flag the Autotester. Code that
contains go_to label like syntax will score 0% and will be treated as code that does not compile.

G14. Under no circumstances is your code solution to contain any exit_(0) type functions.
Please note that the '_' has been added to this description so that this file does not flag the
Autotester. Your solution must always exit with a return 0; in main(). Code that contains
exit_(0); label like syntax will score 0% and will be treated as code that does not compile.

G15. Under no circumstances is your code solution to contain an infinite loop constructs within it.
For example usage of while(1), for(int i; ; i++) or anything similar is not permitted. Code that
contains an infinite loop will result in a score of 0% for your assessment submission and will be
treated as code that does not compile.

G16. Under no circumstances is your code solution to contain any S_l_e_e_p() or D_e_l_a_y() like
statements - Please note that the '_' has been added to this description so that this file does not
flag the Autotester. You can use such statements during your development, however you must remove
delays or sleeps from your code prior to submission. This is important, as the Autotester will only
give your solution a limited number of seconds to complete (i.e. return 0 in main()). Failure for
your code to complete the required operation/s within the allotted execution window will result in
the Autotester scoring your code 0 marks for that test. To test if your code will execute in the
allotted execution window, check that it completes within a similar time frame as the provided sample
binary.

G17. Under no circumstances is your code solution to contain any characters from the extended ASCII
character set or International typeset characters.  Although such characters may compile under a normal
system, they will result in your code potentially not compiling under the Autotester environment.
Therefore, please ensure that you only use characters: a ...  z, A ... Z, 0 ... 9 as your variable
and function names or within any literal strings defined within your code.	Literal strings can
contain '.', '_', '-', and other basic symbols.

G18. All output to console should be directed to the standard console (stdout) via cout. Do not use
cerr or clog to print to the console.

G19. The file you submit must compile without issues as a self contained *.cpp file. Code that
does not compile will be graded as a non-negotiable zero mark.

G20. All binary numbers within this document have the prefix 0b. This notation is not C++
compliant (depending on the C++ version), however is used to avoid confusion between decimal,
hexadecimal and binary number formats within the description and specification provided in
this document. For example the number 10 in decimal could be written as 0xA in hexadecimal
or 0b1010 in binary. It can equally be written with leading zeroes such as: 0x0A or
0b00001010. For output to the console screen you should only ever display the numerical
characters only and omit the 0x or 0b prefixes (unless it is specifically requested).

### The following are GENERAL SPECIFICATIONS that relate to the OUSB Board (Simulator) ###

G21. Do NOT attempt to read/write to any other OUSB Board IO port other than PORTB 0-7, PINC 0-7,
PORTD bits PD0-PD1 and PD3-PD6 (PD2 and PD7 on PORTD should remain untouched) ADC pins 0, 5 and 6
and the PWM pin 1. Other pins on the OUSB board are reserved for the autotester, RS-232 port and
the USB interface back to the computer, or are not supported by the OUSB Simulator.

G22. If an error (as per the definition in this specification) occurs, then the value on
the simulated OUSB LEDs must not to be updated.

G23. All numerical values read from / written to the OUSB Board are considered to be unsigned
and are between 0 and 255 (inclusive), except the ADC values which are 0 to 1023. You as the
programmer must ensure that you construct and send correctly formed OUSB commands to the OUSB
board via a file pipe, as well as read back the correct values.

G24. Do not attempt to read/write to any other OUSB Board IO port other than PORTB, PORTD, PINC
or the ADC pins.

G25. The conversion to binary must occur in your code, not by using the -b switch as part
of the OUSB.exe application. The '-b' flag will not be supported by the AutoTester.
_________________________________________________________________________________________________
*/
/*
_________________________________________________________________________________________________
___ PROGRAM STRUCTURE and SPECIFICATIONS/FUNCTIONAL REQURMENTS:

F1.	For situations where NO command line arguments are passed to your program:

F1.1	Your program must display your correct student details in the format:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

OUSB Board ACCESS:
F2.	Your program MUST access the OUSB Board using the OUSB class (including read from/write to PORTB
and PORTD). You must ensure that you have private class data members to store the current value of
PORTB and PORTD and include appropriate accessor methods and private methods to read from and write to
PORTB and PORTD.

F2.1 The OUSB class must be instantiated in main() and be used to access the OUSB Board. The tag name
of the class must be OUSB. You can also instantiate the OUSB class in other parts of the program if
you need too.

F2.2 Your program should accept the following command line parameters to read and write to PORTB:

- 'B' command: 'B' is the first parameter and the optional second parameter is the number to write to
PORTB.  If the 'B' parameter is use without the optional second parameter, print the current value of
PORTB (only the numeric value) to the console. If the 'B' command is used with a valid unsigned integer
between 0 and 255 as the second parameter, write the value to PORTB and print the new value on PORTB
(after the successful write) to the console.

Example 1:
Lab3_1234567.exe B     // Read from PORTB and display the number read from PORTB to the console screen
Lab3_1234567.exe B 10  // Write 10 to PORTB and display 10 to the console screen if write was successful

F2.3 Your program should accept the following command line parameters to read and write to PORTD:

- 'D' command: 'D' is the first parameter and the optional second parameter is the number to write to
PORTD.  If the 'D' parameter is use without the optional second parameter, print the current value of
PORTD (only the numeric value) to the console. If the 'D' command is used with a valid unsigned integer
between 0 and 255 as the second parameter, write the value to PORTD and print the new value on PORTD
(after the successful write) to the console. You must consider that PD7 and PD2 are special bits used
by the USB communication link and will always stay at a logic 0 (zero) regardless of what the user
wants to write to them.  Therefore PD7 and PD2 bits must always be bit cleared.

Example 2:
Lab3_1234567.exe D     // Read from PORTD and display the number read from PORTD to the console screen
Lab3_1234567.exe D 16  // Write 16 to PORTD and display 16 to the console screen if write was successful

NOTE:  As PD7 and PD2 bits in PORTD are used for USB and RS-232 support, bits: PD7, PD2 will not stick. For
example, if the command arguments were:
 Lab3_1234567.exe D 16 D 255
Bits PD7 and PD2 will stay at logic Zero. Therefore when reading back the actual value on PORTD you will
get 123 (0b01111011). Therefore the correct value your program should display to console will be: 123
as this is the actual value that is now on PORTD after writing 255 to it.

Example 3:
Lab3_1234567.exe D 255 // Write 123 to PORTD and display 123 to the console screen if write was successful
Lab3_1234567.exe D 15  // Write 11 to PORTD and display 11 to the console screen if write was successful

Example 4 (Murphy's law error example):
If your solution is executed with the following input arguments where an invalid value from the OUSB Board
is return as part of the programs algorithm (i.e. the portd.txt file contains the line "5" or "256"):
	Lab3_1234567.exe D
Your solution should read the expected 8-bit PORTD value and determine that the value return by the PORTD
subsystem is not a valid number between 0 and above 255 with bits 2 and 7 cleared or is an invalid
number/character and it will print the following line:
Z
Nothing other than 'Z' will appear on the console and your solution should return 0; and exit. No modification
of the OUSB Board's PORTD registers should occur.
Note: Similar Murphy's law errors should be detected for other OUSB IO ports.


TRAFFIC LIGHT STATE MACHINE:
F3. Your program MUST have a Traffic light state machine class. You must ensure that you have private
class data members to store the current state of the traffic light (either as a single state to represent
all three lamps, or three lamp states). Include appropriate accessor functions and methods to change the
traffic light state in the class.

F3.1 The tag name of the class must be TrafficLight. The TrafficLight class must be instantiated
in main() and be used to control the state of the traffic light. The traffic light is composed of three
lamps (LEDs): Red, Yellow, and Green. The only lamp sequence possible is: Green-->Yellow-->Red (then
back to Green and repeat). Only one lamp can be on at a time.

PB3 (PORT_B bit 3) -> Green LED
PD5 (PORT_D bit 5) -> Yellow LED
PD4 (PORT_D bit 4) -> Red LED

F3.2 Your program should accept the following command line parameters as the first and second arguments:
- 'R', 'Y' or 'G' as the first argument: The letter indicates which state to start the traffic light
  state-machine in. The corresponding LED should be illuminated if first and second argument are valid.
- The second parameter is a valid unsigned integer between 0 and 15, which indicates the number of state
  transitions the program should run for.

Note: Due to the wiring and the configuration of the OUSB Board PCB layout, when you switch on the Green
LED by writing a 1 to PORTB bit 3, the independently wired LED on the prototype area as well as the bit 3
LED on the PORTB LED array will illuminate both at the same time. The Red and Yellow LEDs are independent
as they are connected to bit4 and bit5 of PORTD, respectively.

Example 5:
Lab3_1234567 R 3  // Start the traffic light on Red and run for three transitions  i.e., R-->G-->Y-->R

F3.3 Use PORTB bits: bit0, bit1 and bit2 to indicate the Red and Yellow states of the state-machine.
In addition to the Red LED connected to PORTD being illuminated for the Red state, bit 0 of PORTB should
also be illuminated when the state machine is in the Red state. Similarly, for the Yellow state, bit 1 as
well as bit 2 of PORTB should be illuminated in conjunction with the Yellow LED when the state machine is
in the Yellow state. The second parameter (a valid unsigned integer between 0 and 15) will indicates the
number of state transitions the program should run for. Each transition should have the correct LED
illuminated with the correct LEDs on PORTB switched on for each state transition.

Example 6:
Lab3_1234567 Y 2  // Start the traffic light on Yellow - Yellow LED and bit 1 and bit 2 of PORTB will be
				  // illuminated. Then the state machine will run for two transitions i.e., Y-->R-->G
Example 7:
Lab3_1234567 G 5  // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R

Note: On exit the current state of the traffic light will be maintained on the OUSB Board and a very
specific console output sting will be required, as defined below.


F3.4 Upon completing all the state transitions, the program should print out the last value of PORTB as
an integer (in decimal) followed directly by a comma symbol (i.e. ',') and then the last value of PORTD
as an integer (in decimal), followed by a line return. There should be NO white spaces in the output line.

Example 8:
Lab3_1234567 G 5  // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R
				  // Output to console will be a single line containing the text:
1,16

Note: All examples above assume that PORTB and PORTD were both set to 0 before the examples were executed.

F3.5 Your program should accept the following command line parameters as the first and second arguments:
- "CR", "CY" or "CG" as the first argument: The first character 'C', which is common to all 3 commands
indicates that you should maintain an incrementing counter for each state machine step. The value of the
counter then should be encoded into the top 4 bits of PORTB without effecting the lower 4 bits.

Note: Bits 0, 1, 2 and 3 of PORTB are already designated to represent the different traffic light state
values of the state machine.

Example 9:
Lab3_1234567 CG 5 // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R
				  // Output to console will be a single line containing the text:
81,16
				  // The value 81 means bits 0, 4 and 6 of PORTB will be high. Bit 0 represents the
				  // final state being Red. Bits 4 and 6 equates to five (5) state machine transitions
				  // were stepped through.

Example 10:
Lab3_1234567 CG 1 // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for one transitions i.e., G-->Y
				  // Output to console will be a single line containing the text:
22,32
				  // The value 22 means bits 1, 2 and 4 of PORTB will be high. Bits 1 and 2 represents
				  // the final state being Yellow. Bit 4 equates to one (1) state machine transition was
				  // stepped through. The number 32 means bit 5 of PORTD is high, which indicates the
				  // Yellow LED is on (as the last state of the state machine was Yellow).

F3.6 All other bits on PORTB and PORTD should not be modified when individual bits in each port are set
high or cleared to zero. Therefore, when writing values to PORTB or PORTD at any time throughout your
program, you should be maintaining the current value on the port and only set or clear the bit (or bits)
of interest. For instance when modifying PORTB in response to a valid 'G', 'Y' or 'R' command, then only
the first 4 bits of PORTB should be modified and the upper 4 bits should maintain state.

Example 11:
If the OUSB Board was set-up with the value 255 on PORTB and 123 on PORTD prior to your code running
with the following command line arguments:
Lab3_1234567 G 1
The last (and only) line on the console will be:
246,107

Note: In the case of the above example, the program should have only modified bits 0, 1, 2 and 3 of PORTB
and bits 4 and 5 of PORTD.

However, when your program responses to a 'CG', 'CY' or 'CR' commands, the upper 4 bits and lower 4 bits
of PORTB be can be fully modified as the upper 4 bits of PORTB should be used to maintain a 4-bit counter.

Example 12a:
If the OUSB Board was setup with the value 128 on PORTB and 123 on PORTD prior to your code running
with the following command line arguments:
Lab3_1234567 CY 0
The last (and only) line on the console will be:
6,107

Example 12b:
If the OUSB Board was setup with the value 128 on PORTB and 123 on PORTD prior to your code running
with the following command line arguments:
Lab3_1234567 CY 1
The last (and only) line on the console will be:
17,91


Commands 'B' and 'D' can modify all 8 bits in their respective ports with the exception of bits 2 and 7 in
PORTD. Remember that bits 2 and 7 of PORTD are used for the USB interface and always read as logic 0 when
using ousb.exe commands (under normal operation).

F3.7 Other considerations:

Your program should only display a single line on the console for all specifications followed by a
newline character and then exit (with a return 0) for all cases discussed above.

Your program MUST use pipes to communicate with the OUSB Board, system calls are NOT allowed:
system("ousb -r io portb 127");   // not allowed

System calls take longer and automatically echo the result to the command shell window. If you use system calls
in your code it is very likely the code will not work properly with the autotester or meet specifications. You
will most likely lose all marks for this lab. Therefore, you MUST use the code using pipes. See the code fragments
given to you and explained in lectures and on Blackboard. Sample code to access the OUSB Board via pipes is provided.

Please remember to use good programming practice, hence every time you open a pipe you MUST close the pipe using
'_pclose(<pipename>);. Failure to not do this will result in your code being highly unreliable and you could lose
a lot of marks due to your program not behaving correctly while being tested by the autotester.

************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************
***
***  In Lab Code Submission 3 YOU MUST IMPLEMENT 2 CLASSES. One to access the OUSB Board
***  and one for the traffic light object - this will be checked and your maximum score
***  will be capped at 40% if you do not use an OUSB object and a traffic light object
***  in your solution!!!  Therefore if you code scores 80% from the autotester, your
***  actual final mark will be reduced to 40% if these objects are not used in your code.
***
***  IN Lab Code Submission 3 YOU WILL AUTOMATICALLY LOSE 20% OF YOUR MARK IF YOU
***  DO NOT HAVE MATCHING _popen(...) and _pclose(...) - this will be checked!!!
***
************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************

About pipes and _popen:
http://www.cplusplus.com/forum/windows/1341/
http://www.cplusplus.com/forum/windows/10766/

___________________________________________________________________________________________
___ ERROR HANDLING:

The following text lists errors you must detect and a priority of testing.

Note: order of testing is important as each test is slightly more difficult than the previous test.

All outputs are a single character followed by a newline ( endl or \n) and exiting the program with
a return 0; statement. DO NOT add more than what is specified, do NOT add additional information.

E1. Error precedence:
The order of errors can theoretically be checked in any order, however if multiple errors
occur during a program execution event, your program should only display one error code
followed by a newline character and then exit (with a return 0). The displayed error
codes to the console window should occur in this order:
	'I' - Incorrect input command line argument for first operand (first input parameter)
	'P' - Incorrect number of input command line arguments
	'N' - Invalid numerical command line argument (second operand or input parameter)
	'R' - The second operand argument is a numerical value that is out of range
	'Z' - MURPHY'S LAW (undefined error)
Therefore if an invalid numerical command line argument (operand 2) with an invalid first
operand are passed to the program, the first error code should be displayed to the console,
which in this case would be 'I'. Displaying 'N' or 'R' would be result in a loss of marks.


E2. NUMBER OF PARAMETERS

E2.1 If no input parameters are passed to the program, the console output MUST print student ID string
in CSV format described above and then exit. That is, when the program is run without any operands i.e.
with no command line arguments other than the name of the program.

E2.2 If 1 or more input parameters are passed to the program the first operand must be either 'B' 'D',
'R', 'Y', 'G', 'CR', 'CY' or 'CG'. For any other (case sensitive) letter or character combination or
argument string, the output shall be 'I' which signals the first input parameter is erroneous. After
outputting 'I' (and new line), your program should return 0 and exit without effecting the OUSB Board.

E2.3 If only 1 input parameter is passed to the program, and the (first) operand is 'R', 'Y', 'G',
'CR', 'CY' or 'CG', the console output must be 'P', which signals a parameter error. After outputting
'P' (and new line), your program should return 0 and exit without effecting the OUSB Board.

Note: If the first and only input operand is 'B' or 'D', this is a valid selection and your solution
should read the value of either PORTB or PORTD from the OUSB Board, as per F2.2 or F2.3, respectively.

Example 12: That is, following the program name, the command line can take two or three parameters only:
Lab3_1234567.exe  Operand1
Testples:
Lab3_1234567.exe B   		(valid)
Lab3_1234567.exe G 			(NOT valid: output: P)
Lab3_1234567.exe CG			(NOT valid: output: P)
Lab3_1234567.exe U			(NOT valid: output: I)

E2.4 If the number of input parameters is 3 or more, and the first operand is either 'B' 'D', 'R', 'Y',
'G', 'CR', 'CY' or 'CG', the output must be 'P' which signals a parameter error. Then program should
return 0 and exit without effecting the OUSB Board.

E2.5 If the number of input parameters is 3 or more, and the first operand is not 'B' 'D', 'R', 'Y',
'G', 'CR', 'CY' or 'CG', then the output must be 'I' which signals a parameter error. Then program should
return 0 and exit without effecting the OUSB Board.

E2.6 If a numerical unsigned integer is not entered as the second input parameter as required for all
commands (apart from when 'B' or 'D' are used alone), the output shall be 'N' which signals a numerical
parameter error in the third parameter. Please note, this does not include out of range values. After
outputting 'N' (and a new line), your program should return 0 and exit without effecting the OUSB Board.

Example 13: That is, following the program name, the command line can take one or two input parameters only:
Lab3_1234567.exe  Operand1 Operand2
Testples:
Lab3_1234567.exe G 1		(valid)
Lab3_1234567.exe G 1.0		(NOT valid: output: N)
Lab3_1234567.exe G -1		(NOT valid: output: N)
Lab3_1234567.exe G t1		(NOT valid: output: N)
Lab3_1234567.exe G 1t		(NOT valid: output: N)

E3.  VALID NUMBER RANGE

E3.1 If the number entered as the third parameter on the command line is not within an accepted range,
then the output shall be 'R' which signals a range error. Then program should return 0 and exit without
effecting the OUSB Board.

The accepted number ranges are:
	- 'B' and 'D' commands: Second operand must be between 0 and 255 in valid integer format
	- 'R', 'Y' or 'G' commands: Second operand must be between 0 and 15 in valid integer format
	- 'CR', 'CY' or 'CG' commands: Second operand must be between 0 and 15 in valid integer format

Example 14: That is, following the program name, the command line can take one or two input parameters only:
Lab3_1234567.exe  Operand1 Operand2
Testples:
Lab3_1234567.exe B 250		(valid)
Lab3_1234567.exe G 10		(valid)
Lab3_1234567.exe B 256		(NOT valid: output: R)
Lab3_1234567.exe G 16		(NOT valid: output: R)

Note: All numerical arguments must be an unsigned integer value, therefore if a decimal or exponential
number is provided as a second input argument, your program should responded with 'N' from previous
error check.

E4.  ANYTHING ELSE THAT CAN GO WRONG (MURPHY'S LAW TEST)
If there are any other kinds of errors not covered here, the output shall be 'Z'. That is: anything
else that can possibly go wrong and has not be explicitly tested for or covered under the tests above.
For example:
	- no OUSB Board connection.
	- disconnection during operation
	- HW dead.
	- ???? anything else Murphy can dream up.
	- everything that has not been covered elsewhere is Murphy's domain.

Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected or is disconnected
during normal operation. This message should NOT be returned by your code. The only output your code
should give is the single character: 'Z', followed by a new line and then it should return 0 and exit.

Suggestion: only worry about Hardware errors/test if you have clearly covered ALL preceding tests!

ERROR CHECKING HINTS: The basic programming rules are simple (as covered in lectures):
1) Check that the input is valid.
2) Check that the output is valid.
3) If any library function returns an error code USE IT !!! CHECK FOR IT !!! If that means more than 50%
of your code is error checking, then that's the way it has to be.

___________________________________________________________________________________________
___ GENERAL INFORMATION AND HINTS:

- This program must be in one file named Lab3_1234567.cpp where 1234567 is your
student number. Your filename MUST NEVER EVER contain any spaces.  _under_score_is_Fine.

- When text output is required you must generate EXACTLY that
output and no other output.  For Testple-
Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
Specified output: "RX"    Actual program output: " RX"     Result: zero marks.

- Use debug mode and a breakpoint at the return statement prior to program finish in main.

- What string conversion routines do you know that convert strings to numbers?
Look carefully as they will be needed to convert a command line parameter to a number and
also check for errors.

- Most conversion routines do have inbuilt error checking - USE IT !!!
That means: test for the error condition and take some action if the error is true.
If that means more than 70% of your code is error checking, then that's
the way it has to be.

- Tackle the easiest tasks first and build your program up in stages. The easiest tasks are
are normally the first tasks mentioned. Therefore has you get down to the last few tasks these
are the tasks that can trip you up or lead to issues if you have not designed your code
with an adequate structure to handle all the possible issues and combinations.

- The mark derived from the autotester will result from testing your program against a whole
range of inputs. The secret to getting a good mark is to carefully analyse all possible errors
and odd situations BEFORE you write the code so read the proforma VERY carefully. Ensure in each
circumstance you can detect the error or condition and report the appropriate result. Hint: write
test cases before you write any code.

- General OUSB commands that might be useful:
To read the value at port B:					ousb -r io portb
To write 20 to port B:  						ousb -r io portb 20
To write 16 to port D:  						ousb -r io portd 16
To read the value of the DIP switches (pinc):	ousb -r io pinc
To read the potentiometer (ADC5):				ousb -r adc 5
To set pwm-freq to 45Hz on pin 1:				ousb -r pwm-freq 1 45
To set pwm duty cycle to 50% on pin 1:			ousb -r pwm 1 50

- Description of _itoa_s() library function - Converts an integer to a string.
Prototype:
		   errno_t _itoa_s(int value, char *buffer, int radix);
Parameters:
[in] value   - Number to be converted.
[out] buffer - buffer is filled with the result of the conversions a C string.
[in]  radix  - Base of value, which must be in the range of 2-36.
Return Value - Zero if successful; an error code on failure.


- Description of strcpy_s() library function - Copies a C string.
Prototype:
		   errno_t strcpy_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Location of the destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.


- Description of strcat_s() library function - Appends a C string.
Prototype:
		   errno_t strcat_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Null-terminated destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.


- The following code is the syntax required to open a pipe to the device.
It may / may not include all of the necessary code to complete the task.

//----Start of template standalone .cpp file--------------------------------------------
#include <iostream>
#define Debug 1  			// set debug to ON
using namespace std;
int main(int argc, char* argv[])
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB 20"); // command to write 20 to OUSB Board

	if (Debug) cout << "DEBUG :" << command << endl; // print out OUSB data for debug purposes

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			if (Debug) cout << "DEBUG :" << line ; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB Board, eg:
	unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
	if (Debug) cout << "DEBUG :" << "value = " << portb << endl;

	return 0;
}
//----End of template standalone .cpp file----------------------------------------------
____________________________________________________________________________________________
*/
// These are the libraries you are allowed to use to write your solution. Do not add any
// additional libraries as the auto-tester will be locked down to the following:
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <errno.h>   
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h> // keep it here, just in case.
// Do NOT Add or remove any #include statements to this project!!
// All library functions required should be covered by the above
// include list. Do not add a *.h file for this project as all your
// code should be included in this file.

using namespace std; // Please do not remove this line

// optional: your choice if you want to use/modify these definitions for MAX-MIN-Range
const double MAXRANGE = 255;
const double MINRANGE = 0;

// optional: The class data members and methods within the provided OUSB and TrafficLight class are provided
//           as examples. The names of the data members and methods can be changed. The requirement is
//           that the class tag names (i.e. OUSB  and  TrafficLight) are not changed.

class OUSB 			// Do NOT change class tag name
{
private:
	// Example of data members (These can be changed....)
	unsigned short PORTA;
	unsigned short PORTB;
	unsigned short PORTC;
	unsigned short PORTD;
	bool MurphysLaw;
	int OUSBexeMissing;

	// Example of class Interface methods (These can be changed....)
	unsigned short runOUSBcommand(string* command);

public:
	OUSB() {
		// construct PORT A, B, C & D 
		// equal to 0? or read current values?
		MurphysLaw = false;
		OUSBexeMissing = 0;
	};  // Constructor: Remember to define this else it won't compile

	// Example of Interface methods (These can be changed....)
	unsigned short writePORTB(unsigned short newValue);
	unsigned short writePORTD(unsigned short newValue);

	unsigned short readPORTA(unsigned short pinNumber);
	unsigned short readPORTB();
	unsigned short readPORTC();
	unsigned short readPORTD();

	void set_PORTA(unsigned short val) { PORTA = val; }
	void set_PORTB(unsigned short val) { PORTB = val; }
	void set_PORTC(unsigned short val) { PORTC = val; }
	void set_PORTD(unsigned short val) { PORTD = val; }
	void set_MurphysLaw(bool Input) { MurphysLaw = Input; }

	unsigned short get_PORTA() { return PORTA; }
	unsigned short get_PORTB() { return PORTB; }
	unsigned short get_PORTC() { return PORTC; }
	unsigned short get_PORTD() { return PORTD; }
	bool get_MurphysLaw() { return MurphysLaw; }

	// you may choose to implement operator overloaded functions for read and write functions for portb
	void operator<<(const unsigned short& val); // write portb
	void operator>>(unsigned short& val);       // read portb	

	//virtual float OUSBboard() = 0;	// Turns OUSB class into an abstract class, cannot be instantiated by itself, only by its derived classes
};
// NOTE 1:
//    - OUSB Class methods can come directly after the OUSB class declaration
//    - They should be defined below the OUSB class and before the TrafficLight
//    class declaration if they are going to be used by any of the methods in the
//    TrafficLight Class.
//    - All code must be in this file (ie. no separate *.h files for autotester)

//   OUSB class methods can go here ...

unsigned short OUSB::runOUSBcommand(string* command)
{
	unsigned short returnOUSBvalue = 0;

	FILE* fpipe;
	char line[256] = {};
	fpipe = (FILE*)_popen(command->c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			// error checking
			if (strstr(line, "Fatal Exception!") != nullptr)
			{
				_pclose(fpipe);
				MurphysLaw = true; // Set to display ErrorZ
			}
			OUSBexeMissing = 1;	// Shows while loop has ran, means no error occurred
		}
		_pclose(fpipe);
	}
	if (OUSBexeMissing == 0)
	{
		MurphysLaw = true;
	}
	// Make so a value of e.g. 07 in portd.txt produces ErrorZ
	if (atoi(line) != 0 && line[0] == '0')
	{
		MurphysLaw = true;
	}

	returnOUSBvalue = strtoul(line, NULL, 10);

	//returnOUSBvalue = (unsigned short)atoi(line);
	// Debug
	//cout << "line: " << line << endl;
	//cout << "returnOUSBvalue: " << returnOUSBvalue << endl;

	return returnOUSBvalue;
}

unsigned short OUSB::writePORTB(unsigned short newValue)
{
	string command = "ousb -r io PORTB " + to_string(newValue);
	return runOUSBcommand(&command);
}

unsigned short OUSB::writePORTD(unsigned short newValue)
{
	string command = "ousb -r io PORTD " + to_string(newValue);
	return runOUSBcommand(&command);
}

unsigned short OUSB::readPORTA(unsigned short pinNumber)
{
	string command = "ousb -r ADC " + to_string(pinNumber);
	return runOUSBcommand(&command);
}

unsigned short OUSB::readPORTB()
{
	string command = "ousb -r io PORTB";
	//string command = "ousb -disconnect"; // simulate error
	return runOUSBcommand(&command);
}

unsigned short OUSB::readPORTC()
{
	string command = "ousb -r io PINC";
	return runOUSBcommand(&command);
}

unsigned short OUSB::readPORTD()
{
	string command = "ousb -r io PORTD";
	return runOUSBcommand(&command);
}

void OUSB::operator<<(const unsigned short& val)
{
	writePORTB(val);
}

void OUSB::operator>>(unsigned short& val)
{
	val = readPORTB();
}

// Traffic Light class
class TrafficLight : public OUSB // Do NOT change class tag name
{
private:
	// Example of class data members (These can be changed....)
	bool redLamp;
	bool yellowLamp;
	bool greenLamp;
public:
	TrafficLight()
	{
		//redLamp = true;
		//yellowLamp = false;
		//greenLamp = false;
	}; // Constructor: Remember to define this else it won't compile

	// Example of class Interface methods (These methods can be deleted/modified/changed.)
	void redOn();
	bool isREDon(); 	// Example Accessor function prototypes

	void yellowOn();
	bool isYELLOWon(); 	// Example Accessor function prototypes

	void greenOn();
	bool isGREENon(); 	// Example Accessor function prototypes

	void changeTrafficLightState();

	void transitionLoop(int transitions);
	void counterTransitionLoop(int transitions);
};
// NOTE 2:
//  - Write all class methods for the TrafficLight Class below this comment 
//  block and before main().
//  - OUSB methods that are not called directly by the TrafficLight class can go 
//  below this comment block too - or can be written above the TrafficLight class.
//  - All stand alone functions should be defined below this comment block too.
//  - All code must be in this file (ie. no separate *.h files for autotester)

//   TrafficLight class methods go here ...
void TrafficLight::redOn()
{
	redLamp = true;
	yellowLamp = false;
	greenLamp = false;
	// PB0 illuminated - 0b00000001 (0x01 or 1)
	// To maintain top 4 bits - AND PORTB with 0b11110000 (0xF0 or 240) then OR with 1
	unsigned short val = (readPORTB() & 0xF0) | 1;
	if (get_MurphysLaw() == true)
	{
		return;
	}
	writePORTB(val);


	//writePORTB((readPORTB() & 0xF0) | 1);
	// PD4 illuminated - 0b00010000 (0x10 or 16)
	// PD2, PD4, PD5, PD7 - 0b10110100
	// AND PORTD with 0b01001011 (0x4B or 75) to make sure PD2, PD4, PD5, PD7 are zero
	writePORTD((readPORTD() & 0x4B) | 16);
	//writePORTD((readPORTD() & 0xCF) | 16);
}

bool TrafficLight::isREDon()
{
	if (redLamp == true) return true;
	else return false;
}

void TrafficLight::yellowOn()
{
	redLamp = false;
	yellowLamp = true;
	greenLamp = false;
	// PB1 & PB2 illuminated - 0b00000110 (0x06 or 6)
	// To maintain top 4 bits - AND PORTB with 0b11110000 (0xF0 or 240) then OR with 6
	unsigned short val = (readPORTB() & 0xF0) | 6;
	if (get_MurphysLaw() == true)
	{
		return;
	}
	writePORTB(val);
	//writePORTB((readPORTB() & 0xF0) | 6);
	
	// PD5 illuminated - 0b00100000 (0x20 or 32)
	// AND PORTD with 0b01001011 (0x4B or 75) to make sure PD2, PD4, PD5, PD7 are zero
	writePORTD((readPORTD() & 0x4B) | 32);
}

bool TrafficLight::isYELLOWon()
{
	if (yellowLamp == true) return true;
	else return false;
}

void TrafficLight::greenOn()
{
	redLamp = false;
	yellowLamp = false;
	greenLamp = true;
	// PB3 illuminated - 0b00001000 (0x08 or 8)
	// To maintain top 4 bits - AND PORTB with 0b11110000 (0xF0 or 240) then OR with 8
	unsigned short val = (readPORTB() & 0xF0) | 8;
	if (get_MurphysLaw() == true)
	{
		return;
	}
	writePORTB(val);
	//writePORTB((readPORTB() & 0xF0) | 8);
	
	// What is the green LED on PORTD? There is none?
	// AND PORTD with 0b01001011 (0x4B or 75) to make sure PD2, PD4, PD5, PD7 are zero
	writePORTD((readPORTD() & 0x4B) | 0);
}

bool TrafficLight::isGREENon()
{
	if (greenLamp == true) return true;
	else return false;
}

void TrafficLight::changeTrafficLightState()
{
	if (redLamp == true) greenOn();
	else if (greenLamp == true) yellowOn();
	else if (yellowLamp == true) redOn();
}

void TrafficLight::transitionLoop(int transitions)
{
	//writePORTB(readPORTB() & 0x0F);
	while (transitions > 0)
	{
		if (isREDon() == true)
		{
			changeTrafficLightState();
		}
		else if (isGREENon() == true)
		{
			changeTrafficLightState();
		}
		else if (isYELLOWon() == true)
		{
			changeTrafficLightState();
		}
		transitions--;
	}
	//  Murphys law check here?
	if (get_MurphysLaw() == true)
	{
		//ErrorZ();	// can I call this function even without it being a member of TrafficLight and OUSB classes?
		return;
	}
	
	cout << readPORTB() << ',' << readPORTD() << endl;
}

void TrafficLight::counterTransitionLoop(int transitions)
{
	int counter = 0;
	int shiftedcounter = 0;
	while (transitions > 0)
	{
		if (isREDon() == true)
		{
			changeTrafficLightState();
		}
		else if (isGREENon() == true)
		{
			changeTrafficLightState();
		}
		else if (isYELLOWon() == true)
		{
			changeTrafficLightState();
		}
		counter++;
		shiftedcounter = counter << 4;
		// AND PORTB with 0b00001111 (0x0F or 15) to obtain bottom 4 bits then OR with shifted counter value 
		writePORTB((readPORTB() & 15) | shiftedcounter);	// Maintain bottom 4 bits of PORTB and update counter on top 4 bits of PORTB
		transitions--;
	}

	if (get_MurphysLaw() == true)
	{
		//ErrorZ();	// can I call this function even without it being a member of TrafficLight and OUSB classes?
		return;
	}

	cout << readPORTB() << ',' << readPORTD() << endl;
}

//   Any standalone functions go here ...
void ErrorI() { cout << "I" << endl; }	// Incorrect input command line argument for first operand (first input parameter)
void ErrorP() {	cout << "P" << endl; }	// Incorrect number of input command line arguments
void ErrorN() {	cout << "N" << endl; }	// Invalid numerical command line argument (second operand or input parameter)
void ErrorR() {	cout << "R" << endl; }	// The second operand argument is a numerical value that is out of range
void ErrorZ() {	cout << "Z" << endl; }	// MURPHY'S LAW (undefined error)

bool firstARGtest(char* arg)
{
	if (strcmp(arg, "B") && strcmp(arg, "D") && strcmp(arg, "R") && strcmp(arg, "Y") && strcmp(arg, "G") && strcmp(arg, "CR") && strcmp(arg, "CY") && strcmp(arg, "CG"))
	{
		return true;
	}
	return false;
}

// all function definitions and prototypes to be defined above this line
int main(int argc, char* argv[])
{
	// ALL CODE (excluding variable declarations) MUST come after the following 'if' statement
	if (argc == 1)
	{
		// When run with just the program name (no parameters) your code  MUST print 
		// student ID string in Comma Separated Version (CSV) format. i.e.
		// "studentNumber,student_email,student_name"
		// eg: "2345678,s2345678@student.rmit.edu.au,FirstName_LastName"

		// Edit string below: eg: "studentNumber,student_email,student_name"
		cout << "3943068,s3943068@student.rmit.edu.au,Jala_Seviour" << endl;

		// Failure of your program to do this cout statement correctly will result in a
		// flat 10% marks penalty!

		// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will
		//assume you have made some major error.  Leave it as zero.
		return 0;
	}

	//--- START YOUR CODE HERE - After you have modified the above cout statement with your details.
	OUSB ousb;			// Create ousb object based on OUSB class
	TrafficLight light;	// Create light object based on TrafficLight class
	//unsigned short PORTB;
	unsigned short PORTD;


	if (argc == 2)
	{
		// Check for input to be 'B' 'D', 'R', 'Y', 'G', 'CR', 'CY' or 'CG'
		if (firstARGtest(argv[1]))
		{
			ErrorI();
			return 0;
		}
		else if (!(strcmp(argv[1], "R") && strcmp(argv[1], "Y") && strcmp(argv[1], "G") && strcmp(argv[1], "CR") && strcmp(argv[1], "CY") && strcmp(argv[1], "CG")))
		{
			ErrorP();
			return 0;
		}

		if (!strcmp(argv[1], "B"))		// Read from PORTB & display value to console
		{
			//light.set_PORTB(light.readPORTB());	// can be used if TrafficLight class is derived from OUSB
			ousb.set_PORTB(ousb.readPORTB());
			// Error check for PORTB value?
			if (ousb.get_PORTB() < 0 || ousb.get_PORTB() > 255)
			{
				ErrorZ();
				return 0;
			}
			if (ousb.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			cout << ousb.readPORTB() << endl;
			return 0;
		}
		else if (!strcmp(argv[1], "D"))	// Read from PORTD & display value to console
		{
			ousb.set_PORTD(ousb.readPORTD());
			// check to make sure PD2/PD7 are zero, if not ErrorZ
			if (ousb.get_PORTD() < 0 || ousb.get_PORTD() > 255)
			{
				// outside of 0-255 for PORTD, error?
				ErrorZ();
				return 0;
			}
			else if ((ousb.get_PORTD() & 132) != 0)	// AND with 0b10000100 (0x84 or 132) to make sure PD2/PD7 are 0 within current PORTD value
			{
				ErrorZ();
				return 0;
			}
			if (ousb.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			cout << ousb.readPORTD() << endl;
			return 0;
		}

	}
	else if (argc == 3)
	{
		// Check for input to be 'B' 'D', 'R', 'Y', 'G', 'CR', 'CY' or 'CG'
		if (firstARGtest(argv[1]))
		{
			ErrorI();
			return 0;
		}

		for (int i = 0; argv[2][i] != '\0'; i++)	// Invalid 2nd parameter
		{
			if (!isdigit(argv[2][i]))
			{
				ErrorN();
				return 0;
			}
		}

		if (atoi(argv[2]) > 255 || atoi(argv[2]) < 0)	// Outside PORTB/PORTD range of 0 to 255
		{
			ErrorR();
			return 0;
		}

		if (!strcmp(argv[1], "B"))		// Write 2nd param to PORTB, display to console
		{
			ousb.writePORTB(atoi(argv[2]));
			if (ousb.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			cout << ousb.readPORTB() << endl;
			return 0;
		}
		else if (!strcmp(argv[1], "D"))	// Write 2nd param to PORTD, display to console
		{
			PORTD = atoi(argv[2]) & 123;	// Makes sure PD2/PD7 are zero
			ousb.writePORTD(PORTD);
			if (ousb.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			cout << ousb.readPORTD() << endl;
			return 0;
		}

		
		if (atoi(argv[2]) < 0 || atoi(argv[2]) > 15)	// Outside of R, Y, G, CR, CY and CG range of 0-15
		{
			ErrorR();
			return 0;
		}

		if (!strcmp(argv[1], "R"))
		{
			light.redOn();
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.transitionLoop(atoi(argv[2]));
			return 0;
		}
		else if (!strcmp(argv[1], "Y"))
		{
			light.yellowOn();
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.transitionLoop(atoi(argv[2]));
			return 0;
		}
		else if (!strcmp(argv[1], "G"))
		{
			light.greenOn();
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.transitionLoop(atoi(argv[2]));
			return 0;
		}
		else if (!strcmp(argv[1], "CR"))
		{
			unsigned short val = light.readPORTB() & 0xF0;	// obtain top 4 bits of portb to make sure they're maintained
			//light.writePORTB(light.readPORTB() & 0x0F);
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(val | 0x01);	// set PB0 to represent red light
			if ((light.readPORTD() & 132) != 0)	// AND with 0b10000100 (0x84 or 132) to make sure PD2/PD7 are 0 within current PORTD value
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(light.readPORTB() & 0x0F);
			light.redOn();
			light.counterTransitionLoop(atoi(argv[2]));
			return 0;
		}
		else if (!strcmp(argv[1], "CY"))
		{
			unsigned short val = light.readPORTB() & 0xF0;	// obtain top 4 bits of portb to make sure they're maintained
			//light.writePORTB(light.readPORTB() & 0x0F);
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(val | 0x06);	// set PB1 and PB2 to represent yellow light
			if ((light.readPORTD() & 132) != 0)	// AND with 0b10000100 (0x84 or 132) to make sure PD2/PD7 are 0 within current PORTD value
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(light.readPORTB() & 0x0F);
			light.yellowOn();
			light.counterTransitionLoop(atoi(argv[2]));
			return 0;
		}
		else if (!strcmp(argv[1], "CG"))
		{
			
			unsigned short val = light.readPORTB() & 0xF0;
			//light.writePORTB(light.readPORTB() & 0x0F);
			if (light.get_MurphysLaw() == true)
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(val | 0x08);	// set PB3 to represent green light
			if ((light.readPORTD() & 132) != 0)	// AND with 0b10000100 (0x84 or 132) to make sure PD2/PD7 are 0 within current PORTD value
			{
				ErrorZ();
				return 0;
			}
			light.writePORTB(light.readPORTB() & 0x0F);
			light.greenOn();
			light.counterTransitionLoop(atoi(argv[2]));
			return 0;
		}
	}
	else if (argc > 3)
	{
		if (firstARGtest(argv[1]))
		{
			ErrorI();
			return 0;
		}
		else if (!(strcmp(argv[1], "B") && strcmp(argv[1], "D") && strcmp(argv[1], "R") && strcmp(argv[1], "Y") && strcmp(argv[1], "G") && strcmp(argv[1], "CR") && strcmp(argv[1], "CY") && strcmp(argv[1], "CG")))
		{
			ErrorP();
			return 0;
		}
	}

		// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will
		// assume you have made some major error.  Leave it as zero.
	return 0;
}
// No code to be placed below this line - all functions to be defined above main() function.
// End of File  - DO NOT Modify this line or anything below this line



