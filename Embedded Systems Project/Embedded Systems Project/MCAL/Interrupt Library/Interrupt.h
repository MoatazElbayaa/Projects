/*
 * Interrupt.h
 *
 * Created: 2022-09-11 6:20:23 AM
 *  Author: Moataz Elbayaa
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/*External Interrupt Request 0*/
#define EXT_INT_0 __vector_1

/*Set Global Interrupts, set The I-Bit in status Register to 1*/
#define sei() __asm__ __volatile__("sei" ::: "memory")

/*Set Global Interrupts, set The I-Bit in status Register to 1*/
#define cli() __asm__ __volatile__("cli" ::: "memory")

/*ISR definition*/
#define  ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)



#endif /* INTERRUPT_H_ */