// main.c
volatile int counter = 0;

void c_entry(void) {
  while (1) {
    counter++;
    if (counter > 100) {
      counter = 0; // Reset point for debugging
    }
  }
}
