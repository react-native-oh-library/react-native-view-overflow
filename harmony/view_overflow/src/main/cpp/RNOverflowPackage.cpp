#include "RNOverflowPackage.h"
#include "RNOH/RNInstanceCAPI.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"
#include "OverflowTurboModuleSpec.h"
#include "RNViewOverflowComponentDescriptor.h"
#include "RNViewOverflowComponentInstance.h"

using namespace rnoh;
using namespace facebook;

class RNViewOverflowJSIBinder : public ViewComponentJSIBinder {

};

class OverflowTurboModuleFactoryDelegate : public TurboModuleFactoryDelegate {
 public:
  SharedTurboModule createTurboModule(Context ctx, const std::string& name)
      const override {
    if (name == "OverflowTurboModule") {
      return std::make_shared<NativeOverflowTurboModuleSpecJSI>(ctx, name);
    }
    return nullptr;
  };
};

std::unique_ptr<TurboModuleFactoryDelegate>RNOverflowPackage::createTurboModuleFactoryDelegate() {
  return std::make_unique<OverflowTurboModuleFactoryDelegate>();
}

std::vector<react::ComponentDescriptorProvider>RNOverflowPackage::createComponentDescriptorProviders() {
  return {
      react::concreteComponentDescriptorProvider<react::RNViewOverflowComponentDescriptor>(),
  };
}

ComponentJSIBinderByString RNOverflowPackage::createComponentJSIBinderByName() {
  return {
      {"RNViewOverflow", std::make_shared<RNViewOverflowJSIBinder>()},
  };
}

class OverflowArkTSMessageHandler : public ArkTSMessageHandler {
  void handleArkTSMessage(const Context& ctx) override {
    auto rnInstance = ctx.rnInstance.lock();
    if (rnInstance) {
      if (ctx.messageName == "Overflow_MESSAGE") {
        rnInstance->postMessageToArkTS(ctx.messageName, ctx.messagePayload);
      } else if (ctx.messageName == "BLOCK_NATIVE_RESPONDER") {
        auto rnInstanceCAPI = std::dynamic_pointer_cast<RNInstanceCAPI>(rnInstance);
        auto maybeTag = rnInstanceCAPI->findComponentInstanceTagById(ctx.messagePayload["componentInstanceId"].asString());
        if (maybeTag.has_value()) {
          auto componentInstance = rnInstanceCAPI->findComponentInstanceByTag(maybeTag.value());
          componentInstance->setNativeResponderBlocked(ctx.messagePayload["isBlocked"].asBool(), ctx.messagePayload["origin"].asString());
        }
      }
    }
  };
};

std::vector<ArkTSMessageHandler::Shared>
RNOverflowPackage::createArkTSMessageHandlers() {
  return {std::make_shared<OverflowArkTSMessageHandler>()};
}

ComponentInstanceFactoryDelegate::Shared
rnoh::RNOverflowPackage::createComponentInstanceFactoryDelegate() {
  class OverflowComponentInstanceFactoryDelegate
      : public ComponentInstanceFactoryDelegate {
   public:
    ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
            DLOG(INFO) << "liwang----c++--->OverflowPackage create:" << ctx.componentName;
      if (ctx.componentName == "RNViewOverflow") {
        return std::make_shared<RNViewOverflowComponentInstance>(ctx);
      }
      return nullptr;
    }
  };
  return std::make_shared<OverflowComponentInstanceFactoryDelegate>();
};