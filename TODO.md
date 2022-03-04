# TODO

- Cleaning & testing
 	- Check for casting, memory, & overflow problems
 	- Documentation
 	- Check for unconsidered situations & stress test
	- Remove unecessary #include statements
- Modularize Code
	- Linux compatibility 
	- Switch from QT
		- Licensing
- Quality of Life
	- Multi window tracking
		- Use class instead of title
		- Save file
		- Associated features
- Logger improvements?
- Decrease memory usage

# KNOWN ISSUES

## WILL FIX

- If the tracked window is closed, a new window may claim its ID, and thus the timer will start to go up again

## WONT FIX

- Will not always track if window is focused for less than one second
- Overflow error if window is tracked for over 68 years
