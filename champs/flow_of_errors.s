.comment                        "seb"

	.name                                                             "sebc"
and r1, %:lol, r2 # here we go with comma trouble:
					# in my opinion firstly we check num of parameters if it's == 1 || 2 || 3
					#

#4, r3, ld,
st 									r1, %1 #<- first, but indeed last (invalid argument for command "st" - logical)
st,	r2, 1 										# <- the middle one (syntax)
:												# the last but the first(lexical)
	ld %1, r2
lol:
#	ld	%:a,	r3
	ld 4, r3
#a:live%1
#		r2, r3, ld # WTF IS GOING ON?!
#:%asd, st, 1
#and3, 4, r2
.name"opa"