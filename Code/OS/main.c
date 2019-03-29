int main()
{
	/* main game function */

	/* comes up in user mode (but Super can be called)      */
	/* comes up with interrupts masked @ 68000 (priority 7) */

	for (; ; )
		;

	return 0;     /* shouldn't return - reboots if so */
}
