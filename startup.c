extern void c_entry(void);

#ifdef __APPLE__
__attribute__((section("__DATA,.vectors"))) void (*const vector_table[])(void) = {
#else
__attribute__((section(".vectors"))) void (*const vector_table[])(void) = {
#endif
    (void (*)(void))0x20010000, // Initial Stack Pointer (Top of RAM)
    c_entry                     // Reset Handler (Where execution starts)
};
