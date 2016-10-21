#ifndef RADIANCE_SRC_MICROCONTROLLER_H_
#define RADIANCE_SRC_MICROCONTROLLER_H_
namespace RADIANCE {
  class Microcontroller {
  public:
    Microcontroller();
    ~Microcontroller();
    void startLoop();
    void initialize();

  };
  
}
#endif //RADIANCE_SRC_MICROCONTROLLER_H_
