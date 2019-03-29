	xdef	_kbd_isr
	xref	_do_kbd_isr
_kbd_isr:
	movem.l	d0-d2/a0-a2,-(sp)
	jsr	_do_kbd_isr
	movem.l	(sp)+,d0-d2/a0-a2
	rte
