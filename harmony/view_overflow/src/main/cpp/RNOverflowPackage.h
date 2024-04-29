#include "RNOH/Package.h"

namespace rnoh {

class RNOverflowPackage : public Package {
 public:
  RNOverflowPackage(Package::Context ctx) : Package(ctx) {}

  std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override;

  std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate() override;

  ComponentJSIBinderByString createComponentJSIBinderByName() override;

  std::vector<ArkTSMessageHandler::Shared> createArkTSMessageHandlers() override;

  ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override;
};
} // namespace rnoh
