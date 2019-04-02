	xdef	_vbl_isr,_hbl_isr
	xref	_do_vbl_isr
_vbl_isr:
	movem.l	d0-d2/a0-a2,-(sp)
	jsr	_do_vbl_isr
	movem.l	(sp)+,d0-d2/a0-a2
	rte
_hbl_isr:   rte
