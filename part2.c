#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "mips.h" // for execute_syscall()
#include "types.h"

void execute_instruction(Instruction instruction,Processor* processor,Byte *memory) {
  Word tmp;
	Double tmp2;
	
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  switch(instruction.opcode) {
    case 0x0: // opcode == 0x0(SPECIAL)
      switch(instruction.rtype.funct) {
				case 0x00: // sll
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] << instruction.rtype.shamt;
					processor->PC += 4;
					break;
				case 0x02: // srl
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] >> instruction.rtype.shamt;
					processor->PC += 4;
					break;
				case 0x03: // sra
					processor->R[instruction.rtype.rd] = (sWord)processor->R[instruction.rtype.rt] >> instruction.rtype.shamt;
					processor->PC += 4;
					break;
				case 0x08: // jr
					processor->PC = processor->R[instruction.rtype.rs];
					break;
				case 0x09: // jalr 
					tmp = processor->PC + 4;
					processor->PC = processor->R[instruction.rtype.rs];
					processor->R[instruction.rtype.rd] = tmp;
					break;
	      case 0xc: // funct == 0xc (SYSCALL)
	        execute_syscall(processor);
	        processor->PC += 4;
	        break;	
				case 0x10: // mfhi 
					processor->R[instruction.rtype.rd] = processor->RHI;
					processor->PC += 4;
					break;
				case 0x12: // mflo
					processor->R[instruction.rtype.rd] = processor->RLO;
					processor->PC += 4;
					break;
				case 0x18: // mult
					tmp2 = (sWord)processor->R[instruction.rtype.rs] * (sWord)processor->R[instruction.rtype.rt];
					processor->RLO = tmp2;
					processor->RHI = tmp2 >> 32;
					processor->PC += 4;
					break;
				case 0x19: // multu
					tmp2 = processor->R[instruction.rtype.rs] * processor->R[instruction.rtype.rt];
					processor->RLO = tmp2;
					processor->RLO = tmp2 >> 32;
					processor->PC += 4;
					break;
				case 0x21: // addu
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] + processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
				case 0x23: // subu
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] - processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
        case 0x24: // funct == 0x24 (AND)
          processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] & processor->R[instruction.rtype.rt];
          processor->PC += 4;
          break;
				case 0x25: // funct == 0x25 (OR)
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
				case 0x26: // funct == 0x26 (XOR)
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] ^ processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
				case 0x27: // funct == 0x27 (NOR)
					processor->R[instruction.rtype.rd] = ~(processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt]);
					processor->PC += 4;
					break;
				case 0x2a: // funct == 0x2a (SLT)
					processor->R[instruction.rtype.rd] = (sWord)processor->R[instruction.rtype.rs] < (sWord)processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
				case 0x2b: // funct == 0x2a (SLTU)
					processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] < processor->R[instruction.rtype.rt];
					processor->PC += 4;
					break;
        default: // undefined funct
          fprintf(stderr,"%s: pc=%08x,illegal function=%08x\n",__FUNCTION__,processor->PC,instruction.bits);
          exit(-1);
          break;
      }
      break;
    case 0x2: // opcode == 0x2 (J)
      processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
      break;
	  case 0x3: // opcode == 0x3 (JAL)
	    processor->R[31] = processor->PC + 4;
			processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
	    break;
		case 0x04: // opcode == 0x04 (BEQ)
			if (processor->R[instruction.itype.rs] == processor->R[instruction.itype.rt]) {
				processor->PC = processor->PC + (sHalf)(instruction.itype.imm) * 4;
			}
			processor->PC += 4;
			break;
		case 0x05: // opcode == 0xd05 (BNE)
			if (processor->R[instruction.itype.rs] != processor->R[instruction.itype.rt]) {
				processor->PC = processor->PC + (sHalf)(instruction.itype.imm) * 4;
			}
			processor->PC += 4;
			break;
		case 0x09: // opcode == 0x09 (ADDIU)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0x0a: // opcode == 0x0a (SLTI)
			processor->R[instruction.itype.rt] = (sWord)processor->R[instruction.itype.rs] < (sHalf)instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0x0b: // opcode == 0x0b (SLTIU)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] < (sHalf)instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0x0c: // opcode == 0x0c (ANDI)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] & instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0xd: // opcode == 0xd (ORI)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] | instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0x0e: // opcode == 0x0e (XORI)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] ^ instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0x0f: // opcode == 0x0f (LUI)
			processor->R[instruction.itype.rt] =  instruction.itype.imm << 16;
			processor->PC += 4;
			break;
		case 0x20: // opcode == 0x20 (LB)
			processor->R[instruction.itype.rt] = (sWord)load(memory, processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm, LENGTH_BYTE);
			processor->PC += 4;
			break;
		case 0x21: // opcode == 0x21 (LH)
			processor->R[instruction.itype.rt] = (sWord)load(memory, processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm, LENGTH_HALF_WORD);
			processor->PC += 4;
			break;
		case 0x23: // opcode == 0x23 (LW)
			processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm, LENGTH_WORD);
			processor->PC += 4;
			break;
		case 0x24: // opcode == 0x24 (LBU)
			processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm, LENGTH_BYTE);
			processor->PC += 4;
			break;
		case 0x25: // opcode == 0x25 (LHU)
			processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + (sHalf)instruction.itype.imm, LENGTH_HALF_WORD);
			processor->PC += 4;
			break;
		case 0x28: // opcode == 0x28 (SB)
			store(memory, processor->R[instruction.itype.rs] + (sWord)instruction.itype.imm, LENGTH_BYTE, processor->R[instruction.itype.rt]);
			processor->PC += 4;
			break;
		case 0x29: // opcode == 0x28 (SH)
			store(memory, processor->R[instruction.itype.rs] + (sWord)instruction.itype.imm, LENGTH_HALF_WORD, processor->R[instruction.itype.rt]);
			processor->PC += 4;
			break;
		case 0x2b: // opcode == 0x28 (SW)
			store(memory, processor->R[instruction.itype.rs] + (sWord)instruction.itype.imm, LENGTH_WORD, processor->R[instruction.itype.rt]);
			processor->PC += 4;
			break;
    default: // undefined opcode
      fprintf(stderr,"%s: pc=%08x,illegal instruction: %08x\n",__FUNCTION__,processor->PC,instruction.bits);
      exit(-1);
      break;
  }
}


int check(Address address,Alignment alignment) {
  //fprintf(stderr,"%s: entering check=%08x\n",__FUNCTION__,address);
  /* YOUR CODE HERE */
	if (alignment == 1) {
		return 1;
	}
	if (address < 1 || address >= MEMORY_SPACE) {
		return 0;
	}
	if ((alignment == 4 && address % 4) != 0) {
		return 0;
	}
	if ((alignment == 2 && address % 2) != 0) {
		return 0;
	}
	return 1;	
}

void store(Byte *memory,Address address,Alignment alignment,Word value) {
  if(!check(address,alignment)) {
    fprintf(stderr,"%s: bad write=%08x\n",__FUNCTION__,address);
    exit(-1);
  } 
  /* YOUR CODE HERE */
	switch(alignment) {
		case 1:
			*(memory + address) = (Byte)value;
			break;
		case 2:
			*(memory + address) = (Half)value;
			break;
		case 4:
			*(memory + address) = (Word)value;
			break;
	}		
}

Word load(Byte *memory,Address address,Alignment alignment) {
  if(!check(address,alignment)) {
    fprintf(stderr,"%s: bad read=%08x\n",__FUNCTION__,address);
    exit(-1);
  }  
  /* YOUR CODE HERE */
	switch(alignment) {
		case 1:
			return (Word)(*(Byte*)(memory + address));
		case 2:
			return (Word)(*(Half*)(memory + address));
		default:
			return *(Word*)(memory+address);
	} 
}
