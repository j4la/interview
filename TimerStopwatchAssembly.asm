;
; MajorProjectASM.asm
;
; Created: 1/10/2024 1:59:27 PM
; Author : Jala Seviour S3943068, Anthony Blazek-Pollard S3946058
;
; A (12) for TimerMode
; B (13) for StopwatchMode
; * (10) for Confirm
; # (11) for Clear

.def final5 = R2			; Constant (5) for final 5 seconds of timer
.def multiplier = R3		; Constant (10) for multiplication of secs/mins in 10's
.def onetest = R4			; Constant (1) to test against 1
.def modetest = R5			; Constant (13) to test for A (12) (0x7E on keypad) and B (13) (0x7D on keypad) input for mode
.def confirmcleartest = R6	; Constant (11) to test for * (10) (0xE7 on keypad) and # (11) (0xB7 on keypad) input for confirm/clear
.def dkey = R7				; Constant (15) to test for D (15) (0x77 on keypad) input
.def validnumber = R8		; Constant (9) to test for keypad inputs 0-9, if not invalid numerical input
.def minuteselection = R9	; Illuminated bit to show minutes r being inputted

.def temp = R16			; Updated frequently
.def counter = R17		; Updated frequently

.def key = R18			; Updated frequently for keypress
.def firstkey = R19		; First input for secs/mins
.def secondkey = R20	; Second input for secs/mins
.def savedkey = R21		; To save keypress value
.def minutes = R22		; Minutes value
.def seconds = R23		; Seconds value

.equ SP = 0xDF			; Assigns value 0xDF to SP

CLR R0
CLR R1
;*****************************************************
reset:
	RJMP start

start:
    LDI temp, SP
	OUT 0x3D, temp			; Output 0xDF to SPL (0x3D)
    
	CALL Init				; Call intialisation subroutine
;*****************************************************
loop:
	CALL ReadKey			; Read keypress from keypad
	MOV savedkey, key		; Move keypress value into savedkey register
	CALL keyrelease			; Wait until key is released to continue

	CLR temp
	ADD temp, modetest		; Add 13 to temp
	CP modetest, savedkey	; Compare 13 with keypress 
	BRLT InvalidMode		; Branch if <0, removes 14 (C) & 15 (D)

	SUB temp, savedkey		; 13 - keypress
	CP onetest, temp		; Compare 1 with (13-keypress)
	BRLT InvalidMode		; Branch if <0, invalidates 0 to 11 keypresses

	CP onetest, temp		; 1 CP with (13-keypress)		
	BRNE Timer				; If 13 (B Key) was entered goes to Timer

	RJMP Stopwatch			; If 12 (A Key) was entered goes to Stopwatch (RJMP used as only keypress option left)

again:
	RJMP loop				; Jump to loop
InvalidMode:
	CALL ConfirmError		; Call confirmerror subroutine
	RJMP loop				; Jump to loop
;*****************************************************
Timer:
	CALL TimerSelected		; Call subroutine to show Timer has been selected
	TimerFirstMinutesInput:			; First minutes input (tens)
		OUT PORTB, minuteselection	; Illuminate 7th LED to show minutes
		CALL ReadKey				; Read keypress
		CLR firstkey				; Clear firstkey reg
		ADD firstkey, key			; Add keypress value to firstkey reg
		CALL keyrelease				; Wait until key has been released until moving forward
		; Validate its 0-9
		CP validnumber, firstkey	; Compare keypress val with 9
		BRLT InvalidFirstMinuteNumber	; If <0 invalid keypress, error
		; Illuminate first minutes input on LEDs with MSB signifying minutes
		CLR temp					; Clr temp reg
		ADD temp, firstkey			; Add firstkey press to temp
		OR temp, minuteselection	; Make temp have 7th bit illuminated to show minute selection
		OUT PORTB, temp				; Illuminate LEDs 
		RJMP TimerSecondMinutesInput; Move to 2nd minute input

	InvalidFirstMinuteNumber:
		CALL ConfirmError			; Show error due to invalid input
		RJMP TimerFirstMinutesInput	; Jump back to receive valid input again

	TimerSecondMinutesInput:		; Second minutes input (ones)
		CALL ReadKey
		CLR secondkey
		ADD secondkey, key
		CALL keyrelease
		; Validate its 0-9
		CP validnumber, secondkey
		BRLT InvalidSecondMinuteNumber
		; Illuminate total minutes input
		MUL firstkey, multiplier	; Multiply first input to represent tens
		CLR minutes
		ADD minutes, R0				; Add MUL result to minutes reg
		ADD minutes, secondkey		; Add second mins input to mins reg
		CLR firstkey
		ADD firstkey, minutes		; Add mins to firstkey reg
		CLR temp
		ADD temp, minutes
		OR temp, minuteselection
		OUT PORTB, temp				; Illuminate LEDs with mins val
		CALL Delay					; Call Delay subroutine to show mins
		CALL Delay
		CALL Delay
		CALL Delay
		CALL Delay
		CLR R0
		RJMP TimerFirstSecondsInput	; Jmp to first seconds input

	InvalidSecondMinuteNumber:
		CALL ConfirmError
		RJMP TimerSecondMinutesInput

	TimerFirstSecondsInput:		; First seconds input (tens)
		CLR temp
		OUT PORTB, temp			; To show next input is ready
		CALL ReadKey
		CLR firstkey
		ADD firstkey, key
		CALL keyrelease
		; Validate its 0-9
		CP validnumber, firstkey
		BRLT InvalidFirstSecondsNumber	; If <0 invalid keypress
		CLR temp
		ADD temp, firstkey
		OUT PORTB, temp			; Illuminate first seconds input on LEDs
		RJMP TimerSecondSecondsInput	; 2nd seconds input

	InvalidFirstSecondsNumber:
		CALL ConfirmError
		RJMP TimerFirstSecondsInput

	TimerSecondSecondsInput:	; 2nd seconds input (ones)
		CALL ReadKey
		CLR secondkey
		ADD secondkey, key
		CALL keyrelease
		; Validate its 0-9
		CP validnumber, secondkey
		BRLT InvalidSecondSecondsNumber
		MUL firstkey, multiplier
		CLR seconds
		ADD seconds, R0
		ADD seconds, secondkey
		CLR secondkey
		ADD secondkey, seconds
		OUT PORTB, seconds		; Illuminate LEDs with seconds val
		RJMP CheckSecsMins		; Jmp to check if mins is >0 and secs=0

	InvalidSecondSecondsNumber:
		CALL ConfirmError
		RJMP TimerSecondSecondsInput

	CheckSecsMins:				; Check if mins >0 and secs = 0
		CLR temp
		ADD temp, minutes
		ADD temp, seconds
		CP temp, minutes
		BREQ ZeroSecondsInput	; Branch to adjust for secs = 0
		RJMP TimerRun			; Jmp to running timer

	ZeroSecondsInput:
		LDI temp, 0x3D			; load 61 into temp to adjust seconds from 0
		CLR seconds
		ADD seconds, temp
		CLR temp
		ADD temp, minuteselection
		OR temp, minutes
		OUT PORTB, temp
		DEC minutes

	TimerRun:
		CALL TimerOneSecond		; Call hardware timer subroutine for running

	TimerDisplay:
		CLR temp
		CP temp, minutes
		BREQ FinalMinute		; branch if final minute

		CLR temp
		CP temp, seconds
		BREQ MinuteDisplay		; branch if seconds = 0 to show minutes on LEDs

		OUT PORTB, seconds		; Illuminate LEDs with seconds value
		RJMP TimerRun			; Jmp to timerrun subroutine

	MinuteDisplay:
		ADD temp, minutes
		OR temp, minuteselection
		OUT PORTB, temp			; illuminate LEDs with mins val
		DEC minutes				; decrement minutes
		CALL TimerOneSecond		; run hardware timer subroutine
		LDI seconds, 0x3B		; Load 59 into seconds once minute passed (seconds hits zero)
		RJMP TimerDisplay		; Jmp to timerdisplay subroutine

	FinalMinute:
		CLR temp
		ADD temp, final5
		ADD temp, onetest
		CP seconds, temp
		BRLT FinalSecs			; Branch if <0 for final 5 secs section
		OUT PORTB, seconds		; Illuminate LEDs with seconds val
		CALL TimerOneSecond
		RJMP FinalMinute		; Jmp to run finalminute again
	FinalSecs:
		LDI temp, 0xFF
		OUT PORTB, temp			; Illuminate all LEDs for final 5 seconds
		CALL TimerOneSecond		; Hardware timer 1 second

		CLR temp
		OUT PORTB, temp			; clear LEDs for flashing in final 5 secs
		CALL Delay
		CALL Delay
		CALL Delay
		CALL Delay

		CP temp, seconds
		BREQ TimerFinish		; if seconds is 0 timer is finished
		RJMP FinalSecs			; repeat flashing LEDs if secs not yet 0

	TimerFinish:
		LDI temp, 0xFF
		OUT PORTB, temp			; Illuminate all LEDs to show timer finish
		CALL ReadKey
		CALL keyrelease
		LDI temp, 0xAA			; Illuminate green LEDs to show next mode input is ready
		OUT PORTB, temp
		RJMP loop				; jmp back to run program again
;*****************************************************
Stopwatch:
	CLR seconds
	CALL StopwatchSelected		; Call subroutine to show stopwatch selected
	StopwatchStart:
		CALL StopWatchOneSecond	; Subroutine for hardware timer 1 second
		LDI temp, 0x3C
		CP temp, seconds		; check if 59 seconds
		BREQ MinuteElapsed		; at 60 seconds minute val display
		
		OUT PORTB, seconds		; display seconds on LEDs
		RJMP StopwatchStart		; jmp back to keep running stopwatch

	MinuteElapsed:
		INC minutes				; +1 to mins
		CLR temp
		CLR seconds
		ADD temp, minutes
		OR temp, minuteselection
		OUT PORTB, temp			; display mins with 7th bit illuminated
		RJMP StopwatchStart		; jmp back to keep running stopwatch
;*****************************************************
ConfirmError:
	LDI temp, 0x55
	OUT PORTB, temp				; Light red LEDs
	CALL ReadKey				; Receive keypress to pass through error
	CALL keyrelease
	LDI temp, 0xAA
	OUT PORTB, temp				; Light green LEDs to show next input is ready
	RET
;*****************************************************
ReadKey:
	CALL ReadKP
	LDI temp, 0xFF
	CP key, temp
	BREQ ReadKey
	RET
;*****************************************************
ReadKP:
	LDI key, 0xFF		; Load immediate 0xFF into key
	CLR R18				; Clear R18

	LDI temp, 0xEF		; temp = col1
	OUT PORTC, temp		; PORTC = col1
	
	CALL Delay			; Call delay routine

	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key		; Branch if not equal to find_key routine

	LDI temp, 0xDF		; temp = col2
	OUT PORTC, temp		; PORTC = col2
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key		; Branch if not equal to find_key routine

	LDI temp, 0xBF		; temp = col3
	OUT PORTC, temp		; PORTC = col3
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key		; Branch if not equal to find_key routine

	LDI temp, 0x7F		; temp = col4
	OUT PORTC, temp		; PORTC = col4
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key		; Branch if not equal to find_key routine

	LDI key, 0xFF		; Load immediate 0xFF into key
;*****************************************************
end:
	RET
;*****************************************************
find_key:
	LDI ZH, high(Table << 1)	; Load immediate high byte of Table into high byte of Z register
	LDI ZL, low(Table << 1)		; Load immedaite low byte of Table into low byte of Z register
	ADD ZL, key					; Add key to low byte of Z register
	ADC ZH, R1					; Add carry bit to high bite of Z register
	LPM key, Z					; Load program memory from Z into key
	RJMP end					; Jump to end routine
;*****************************************************
TimerOneSecond:
	CALL startTimer
	
	TimerOverflow:
		IN temp, TIFR			; Read interrupt flag register value
		ANDI temp, (1 << TOV0)	; Isolate bit 0
		CP onetest, temp		; 
		BRNE TimerOverflow		; If overflow flag not set keep checking

		IN temp, TCCR0
		ANDI temp, ~((1 << CS02) | (1 << CS01) | (1 << CS00))	; Disable Timer0
		OUT TCCR0, temp
		IN temp, TIFR
		ORI temp, (1 << TOV0)
		OUT TIFR, temp			; Clear timer overflow flag

		INC counter
		LDI temp, 0x2E
		CP counter, temp
		BRNE TimerOneSecond		; Continue overflowing until 46
		
		DEC seconds
		CLR counter

		CALL ReadKey2			; Check for keypress to pause
		LDI temp, 0xFF
		CP temp, key
		BRNE TimerPaused		; if key pressed pause
		RET

startTimer:
	PUSH R16
	PUSH R17
	LDI R16, 0					
	OUT TCNT0, R16						; Set starting value of Timer0
		
	IN R17, TCCR0						; Read Timer0 control register
	ORI R17, (1 << CS02) | (1 << CS00)	; Prescaler set to 1024
	ANDI R17, ~(1 << CS01)

	OUT TCCR0, R17						; Write back to Timer0 control register

	POP R17
	POP R16
	RET
TimerPaused:
	CALL keyrelease
	CALL ReadKey

	LDI temp, 0x0A 						; * to clear
	CP temp, key
	BREQ ResetTimerToModeSelect			; Reset timer and go back to mode select

	CALL keyrelease
	RJMP TimerOneSecond					; Unpause timer

ResetTimerToModeSelect:
	LDI temp, 0xAA
	OUT PORTB, temp						; Light green LEDs to show next input ready
	CALL keyrelease
	RJMP loop
;*****************************************************
StopWatchOneSecond:
	CALL startStopwatchTimer
	
	StopwatchTimerOverflow:
		IN temp, TIFR			; Read interrupt flag register value
		ANDI temp, (1 << TOV0)	; Isolate bit 0
		CP onetest, temp
		BRNE StopwatchTimerOverflow		; If overflow flag not set keep checking

		IN temp, TCCR0
		ANDI temp, ~((1 << CS02) | (1 << CS01) | (1 << CS00))	; Disable Timer0
		OUT TCCR0, temp
		IN temp, TIFR
		ORI temp, (1 << TOV0)
		OUT TIFR, temp			; Clear timer overflow flag

		INC counter
		LDI temp, 0x2E
		CP counter, temp
		BRNE StopWatchOneSecond				; Continue overflowing until 46
		
		INC seconds
		CLR counter

		CALL ReadKey2
		LDI temp, 0xFF
		CP temp, key						; Check for keypress for pause
		BRNE StopwatchPaused				; If keypressed pause stopwatch

		RET
	
startStopwatchTimer:
	PUSH R16
	PUSH R17
	LDI R16, 0					
	OUT TCNT0, R16						; Set starting value of Timer0
		
	IN R17, TCCR0						; Read Timer0 control register
	ORI R17, (1 << CS02) | (1 << CS00)	; Prescaler set to 1024
	ANDI R17, ~(1 << CS01)

	OUT TCCR0, R17						; Write back to Timer0 control register

	POP R17
	POP R16
	RET
StopwatchPaused:
	CALL keyrelease
	CALL ReadKey
	LDI temp, 0x0B 		; # to clear
	CP temp, key
	BREQ ClearStopwatch	; clear current stopwatch time and start stopwatch again

	LDI temp, 0x0A		; * to go back to mode selection
	CP temp, key
	BREQ ModeFromStopwatch	; go back to mode selection

	CALL keyrelease
	RJMP StopWatchOneSecond

ClearStopwatch:
	CALL keyrelease
	CLR minutes
	RJMP Stopwatch

ModeFromStopwatch:
	CALL keyrelease
	LDI temp, 0xAA
	OUT PORTB, temp
	RJMP loop
;*****************************************************
Delay:
	PUSH R16		; Save R16 and 17 as we're going to use them
	PUSH R17		; as loop counters
	PUSH R0			; we'll also use R0 as a zero value
	CLR R0
	CLR R16			; Init inner counter
	CLR R17			; and outer counter
L1: 
	DEC R16         ; Counts down from 0 to FF to 0
	CPSE R16, R0    ; equal to zero?
	RJMP L1			; If not, do it again
	CLR R16			; reinit inner counter
L2: 
	DEC R17
    CPSE R17, R0    ; Is it zero yet?
    RJMP L1			; back to inner counter

	POP R0          ; Done, clean up and return
	POP R17
	POP R16
    RET
;*****************************************************
keyrelease:
	keyreleaseloop:
		CALL Delay
		CALL ReadKey2
		LDI temp, 0xFF
		CP key, temp
		BRNE keyreleaseloop
	RET
;*****************************************************
ReadKey2:
	CALL ReadKP2
	RET

ReadKP2:
	LDI key, 0xFF		; Load immediate 0xFF into key
	CLR R18				; Clear R18

	LDI temp, 0xEF		; temp = col1
	OUT PORTC, temp		; PORTC = col1
	
	CALL Delay			; Call delay routine

	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key2		; Branch if not equal to find_key routine

	LDI temp, 0xDF		; temp = col2
	OUT PORTC, temp		; PORTC = col2
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key2		; Branch if not equal to find_key routine

	LDI temp, 0xBF		; temp = col3
	OUT PORTC, temp		; PORTC = col3
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key2		; Branch if not equal to find_key routine

	LDI temp, 0x7F		; temp = col4
	OUT PORTC, temp		; PORTC = col4
	CALL Delay			; Call delay routine
	IN key, PINC		; Input PINC value to key
	CP key, temp		; Compare value in temp with key to set flags
	BRNE find_key2		; Branch if not equal to find_key routine

	LDI key, 0xFF		; Load immediate 0xFF into key

	RJMP end

;*****************************************************
find_key2:
	LDI ZH, high(Table << 1)	; Load immediate high byte of Table into high byte of Z register
	LDI ZL, low(Table << 1)		; Load immedaite low byte of Table into low byte of Z register
	ADD ZL, key					; Add key to low byte of Z register
	ADC ZH, R1					; Add carry bit to high bite of Z register
	LPM key, Z					; Load program memory from Z into key
	RJMP end					; Jump to end routine
;*****************************************************
TimerSelected:
	LDI temp, 0x80
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0xC0
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x60
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x30
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x18
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x0C
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x06
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x03
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x01
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0xFF
	OUT PORTB, temp
	CALL Delay
	RET
;*****************************************************
StopwatchSelected:
	LDI temp, 0x01
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x03
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x06
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x0C
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x18
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x30
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x60
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0xC0
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0x80
	OUT PORTB, temp
	CALL Delay
	LDI temp, 0xFF
	OUT PORTB, temp
	CALL Delay
	RET
;*****************************************************
Init:
	LDI temp, 0x05				; 5
	MOV final5, temp			; 

	LDI temp, 0x0A				; 10
	MOV multiplier, temp		;

	LDI temp, 0x01				; 1
	MOV onetest, temp			;

	LDI temp, 0x0D				; 13
	MOV modetest, temp			;

	LDI temp, 0x0B				; 11
	MOV confirmcleartest, temp	;

	LDI temp, 0x0F				; 15
	MOV dkey, temp				;

	LDI temp, 0x09				; 9
	MOV validnumber, temp		;

	LDI temp, 0x80				; 1000 0000
	MOV minuteselection, temp

	LDI temp, 0x2E				; 46 overflows = 1 second
	MOV counter, temp
	
	LDI temp, 0xF0	; Load immediate 0xF0 into temp
	OUT DDRC, temp	; Output value in temp (R16) to DDRC (first 4 pins set to output)

	LDI temp, 0x0F	; Load immediate value 0x0F into temp (R16)
	OUT PORTC, temp	; Output value in temp (R16) to PORTC 

	LDI temp, 0xFF	; Load immediate 0xFF into temp
	OUT DDRB, temp	; Output value in temp to DDRB (all pins set to output)

	LDI temp, 0x00	; Load immediate 0x00 into temp
	OUT PORTB, temp	; Output value in temp to PORTB

  	RET
;*****************************************************
Table:	; 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 0
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 1
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 2
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 3
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 4
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 5
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 6
	.DB 255, 255, 255, 255, 255, 255, 255,  15, 255, 255, 255,  14, 255,  13,  12, 255	; 7
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 8
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; 9
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; A
	.DB 255, 255, 255, 255, 255, 255, 255,  11, 255, 255, 255,   9, 255,   6,   3, 255	; B
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; C
	.DB 255, 255, 255, 255, 255, 255, 255,   0, 255, 255, 255,   8, 255,   5,   2, 255	; D
	.DB 255, 255, 255, 255, 255, 255, 255,  10, 255, 255, 255,   7, 255,   4,   1, 255	; E
	.DB 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255	; F