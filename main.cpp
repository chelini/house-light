#include <donotpushusername.h>
#include <hueplusplus/Bridge.h>
#include <hueplusplus/LinHttpHandler.h>
#include <iostream>

using namespace std;

int main() {
  auto handler = std::make_shared<hueplusplus::LinHttpHandler>();
  hueplusplus::BridgeFinder finder(handler);
  std::vector<hueplusplus::BridgeFinder::BridgeIdentification> bridges =
      finder.findBridges();
  if (bridges.empty()) {
    cout << "No bridges found\n";
    return 0;
  }
  cout << "bridge found\n";
  finder.addUsername(bridges[0].mac, USERNAME);
  hueplusplus::Bridge bridge = finder.getBridge(bridges[0]);

  std::vector<hueplusplus::Light> lights = bridge.lights().getAll();
  cout << "#lights: " << lights.size() << "\n";
  for (auto light : lights)
    cout << light.isOn() << "\n";

  return 0;
}
