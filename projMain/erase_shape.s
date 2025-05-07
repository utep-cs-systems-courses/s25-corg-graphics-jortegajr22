
	.global erase_shape


erase_shape:
	mov  #0, r12
	call #draw_shape
	ret
