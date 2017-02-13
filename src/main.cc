#define LINUX_REBOOT_CMD_RESTART 0x1234567
#include <unistd.h>
#include <sys/reboot.h>
#include "microcontroller.h"
#include "framedata.h"

// Error handler function; restarts if called
void restart() {
  sync();
  reboot(LINUX_REBOOT_CMD_RESTART);

}
int main() {
  // Set terminate handler to custom restart function
  // This will restart the pi if an unknown error is encountered
  std::set_terminate(restart);

  // Create object and start the system loop
  RADIANCE::Microcontroller raspberry_pi;
  raspberry_pi.Initialize();
  raspberry_pi.StartLoop();

}

