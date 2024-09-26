#define REGISTER 0x3F215040


void putc(int data) {
    // Print a single character to the serial port
    // Address to print to: 0xFE215004        
    int *x = REGISTER;
    *x = data;
}

