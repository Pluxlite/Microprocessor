#include <msp430.h>

void erase_SegCD(void);
void write_SegC(void);
void copy_C2D(void);

void main(void)
{
 WDTCTL = WDTPW|WDTHOLD;

 BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
 DCOCTL = CALDCO_1MHZ;

 FCTL2 = FWKEY|FSSEL0|FN1;
 // MCLK/3 for Flash Timing Generator

 erase_SegCD(); // Erase segments C and D
 write_SegC();  // Write to segment C
 copy_C2D();    // Copy segment C to D

 while(1);
}

void erase_SegCD(void){
 char *Flash_ptrC;
 char *Flash_ptrD;

 Flash_ptrD = (char *) 0x1000;
 // Initialize Flash segment D pointer

 FCTL1 = FWKEY|ERASE; // Set Erase bit
 FCTL3 = FWKEY;  // Clear Lock bit
 *Flash_ptrC = 0;

 FCTL1 = FWKEY|ERASE; // Set Erase bit
 *Flash_ptrD = 0;   // Dummy write to erase segments
 FCTL3 = FWKEY|LOCK;  // Set LOCK bit
}

void write_SegC(void){
 char *Flash_ptrC;
 char i;

 Flash_ptrC = (char *) 0x1040;
 // Initialize Flash pointer
 FCTL3 = FWKEY;  // Clear Lock bit
 FCTL1 = FWKEY|WRT;
 // Set WRT bit for write operation

 for (i=0; i<64; i++)
 *Flash_ptrC++ = i; // Write value to flash

 FCTL1 = FWKEY;   // Clear WRT bit
 FCTL3 = FWKEY|LOCK;  // Set LOCK bit
}

void copy_C2D(void){
 char *Flash_ptrC;
 char *Flash_ptrD;
 int i;

 Flash_ptrC = (char *) 0x1040;
 // Initialize Flash segment C pointer
 Flash_ptrD = (char *) 0x1000;
 // Initialize Flash segment D pointer

 FCTL1 = FWKEY|WRT;
 // Set WRT bit for write operation
 FCTL3 = FWKEY;  // Clear Lock bit

 Flash_ptrC = (char *) 0x107F;

 for (i=0; i<64; i++)
 *Flash_ptrD++ = *Flash_ptrC--;
 // copy value segment C to segment D

 FCTL1 = FWKEY;  // Clear WRT bit
 FCTL3 = FWKEY|LOCK; // Set LOCK bit
}
