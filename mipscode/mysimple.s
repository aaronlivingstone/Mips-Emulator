.data
.text
garply: 

addiu $sp,$sp,-4 

sw $ra, 0($sp) 

addiu $v0 $zero 0 

lbu $t0 0($a0) 

beq $t0 $zero end 

addiu $a0 $a0 1 

jal garply 

addiu $v0 $v0 1 

end: 

lw $ra, 0($sp) 

addiu $sp,$sp,4 

jr $ra 

