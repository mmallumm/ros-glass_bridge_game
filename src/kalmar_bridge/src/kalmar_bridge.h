#ifndef BRIDGE_H
#define BRIDGE_H
#include <string>

#define BRIDGE_SIZE 3

namespace ros {
class GlassBridge {
 public:
  GlassBridge();
  char At(size_t index) const;
  std::string Get();

 private:
  std::string safe_field_;
};

class KalmarBridgeGame {
 public:
  bool Play(char input, std::string& output);
  bool PlayerWon() const;

 private:
  GlassBridge bridge;
  size_t counter;
};
}  // namespace ros

#endif