# TODO

- Cleaning
	- Simplify code
 	- Fix jank code
 	- Check for dangerous code
 	- Add documentation
- Quality of Life
 	- Provide for unusual situations
 	- More accurate times
		- Check only when a window becomes (un)focused
		- Use system time instead of just counting every second
 	- Add re-detect applications button
- Stress Test

# KNOWN ISSUES

- If the program tracks a window for over 68 years, it will have an overflow error (might fix)
- If the tracked window is closed, a new window may claim its ID, and thus the timer will start to go up again (might fix)
