.name "Liver"
  
.comment "i am alive!"
lol: lol -1 r1 %:l2  #Syntax error at token [TOKEN][004:013] REGISTER "r1"
lol: lol -1 %:l2 #Syntax error at token [TOKEN][004:013] DIRECT_LABEL "%:l2"
lol: lol -1 #Invalid instruction at token [TOKEN][004:006] INSTRUCTION "lol"
l2: aff r12
#lol