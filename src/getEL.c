int getEL() {
    unsigned int el;
    asm("mrs %0,CurrentEL"
	: "=r"(el)
	:
	:);
    return(el>>2);
}
