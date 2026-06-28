extern void c_entry(void);

// Linker symbols
extern unsigned int _sidata;
extern unsigned int _sdata;
extern unsigned int _edata;
extern unsigned int _sbss;
extern unsigned int _ebss;

void Reset_Handler(void);
void Default_Handler(void);

// Weak aliases for core Cortex-M exception handlers
void NMI_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)   __attribute__((weak, alias("Default_Handler")));

#ifdef __APPLE__
__attribute__((section("__DATA,.vectors"))) void (*const vector_table[])(void) = {
#else
__attribute__((section(".vectors"))) void (*const vector_table[])(void) = {
#endif
    (void (*)(void))0x20010000, // Initial Stack Pointer (Top of RAM)
    Reset_Handler,              // Reset Handler
    NMI_Handler,                // NMI Handler
    HardFault_Handler,          // HardFault Handler
    Default_Handler,            // MPU Fault Handler
    Default_Handler,            // Bus Fault Handler
    Default_Handler,            // Usage Fault Handler
    0, 0, 0, 0,                 // Reserved
    SVC_Handler,                // SVCall Handler
    Default_Handler,            // Debug Monitor Handler
    0,                          // Reserved
    PendSV_Handler,             // PendSV Handler
    SysTick_Handler             // SysTick Handler
};

void Reset_Handler(void) {
    // 1. Copy the data segment initializers from flash to SRAM
    unsigned int *src = &_sidata;
    unsigned int *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // 2. Zero fill the bss segment
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    // 3. Call the application's entry point
    c_entry();
}

void Default_Handler(void) {
    while (1) {
        // Loop infinitely
    }
}
