#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"

void decode_instruction(Instruction instruction) {
  
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  switch(instruction.opcode) {
    case 0x0: // opcode == 0x0 (SPECIAL)
      switch(instruction.rtype.funct) {
        case 0x00: // funct == 0x24 (AND)
          printf("sll\t$%d,$%d,%u\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
          break;
				case 0x02: // funct == 0x24 (AND)
					printf("srl\t$%d,$%d,%u\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
					break;
				case 0x03: // funct == 0x24 (AND)
					printf("sra\t$%d,$%d,%u\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
					break;
				case 0x08: // funct == 0x24 (AND)
					printf("jr\t$%d\n",instruction.rtype.rt);
					break;
				case 0x09: // funct == 0x24 (AND)
					printf("jalr\t$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs);
					break;
	      case 0xc: // funct == 0xc (SYSCALL)
	        printf("syscall\n");
	        break;
				case 0x10: // funct == 0x24 (AND)
					printf("mfhi\t$%d\n",instruction.rtype.rd);
					break;
				case 0x12: // funct == 0x24 (AND)
					printf("mflo\t$%d\n",instruction.rtype.rd);
					break;
				case 0x18: // funct == 0x24 (AND)
					printf("mult\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
					break;
				case 0x19: // funct == 0x24 (AND)
					printf("multu\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
					break;
				case 0x21: // funct == 0x24 (AND)
					printf("addu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;
				case 0x23: // funct == 0x24 (AND)
					printf("subu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;
				case 0x24: // funct == 0x24 (AND)
					printf("and\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;											
				case 0x25: // funct == 0x24 (AND)
					printf("or\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;					
				case 0x26: // funct == 0x24 (AND)
					printf("xor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;							
				case 0x27: // funct == 0x24 (AND)
					printf("nor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;							
				case 0x2a: // funct == 0x24 (AND)
					printf("slt\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;								
				case 0x2b: // funct == 0x24 (AND)
					printf("sltu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					break;
        default: // undefined funct
          fprintf(stderr,"%s: illegal function: %08x\n",__FUNCTION__,instruction.bits);
          exit(-1);
          break;
      }
      break;
    case 0x2: // opcode == 0x2 (J)
      printf("j\t0x%x\n",instruction.jtype.addr*4);
      break;
    case 0x3: // opcode == 0x2 (J)
      printf("jal\t0x%x\n",instruction.jtype.addr*4);
      break;
		case 0x04: // opcode == 0xd (ORI)
			printf("beq\t$%d,$%d,%d\n",instruction.itype.rs,instruction.itype.rt,instruction.itype.imm*4);
			break;
		case 0x05: // opcode == 0xd (ORI)
			printf("bne\t$%d,$%d,%d\n",instruction.itype.rs,instruction.itype.rt,instruction.itype.imm*4);
			break;
		case 0x09: // opcode == 0xd (ORI)
			printf("addiu\t$%d,$%d,%d\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0x0a: // opcode == 0xd (ORI)
			printf("slti\t$%d,$%d,%d\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0x0b: // opcode == 0xd (ORI)
			printf("sltiu\t$%d,$%d,%d\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0x0c: // opcode == 0xd (ORI)
			printf("andi\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0xd: // opcode == 0xd (ORI)
			printf("ori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0x0e: // opcode == 0xd (ORI)
			printf("xori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0x0f: // opcode == 0xd (ORI)
			printf("lui\t$%d,0x%x\n",instruction.itype.rt,instruction.itype.imm);
			break;
		case 0x20: // opcode == 0xd (ORI)
			printf("lb\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x21: // opcode == 0xd (ORI)
			printf("lh\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x23: // opcode == 0xd (ORI)
			printf("lw\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x24: // opcode == 0xd (ORI)
			printf("lbu\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x25: // opcode == 0xd (ORI)
			printf("lhu\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x28: // opcode == 0xd (ORI)
			printf("sb\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x29: // opcode == 0xd (ORI)
			printf("sh\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;
		case 0x2b: // opcode == 0xd (ORI)
			printf("sw\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm,instruction.itype.rs);
			break;										
    default: // undefined opcode
      fprintf(stderr,"%s: illegal instruction: %08x\n",__FUNCTION__,instruction.bits);
      exit(-1);
      break;
  }
}
