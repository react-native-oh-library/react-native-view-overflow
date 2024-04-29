#pragma once

#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"
#include "RNOH/arkui/TextNode.h"
#include "RNViewOverflowComponentDescriptor.h"

namespace rnoh {
class RNViewOverflowComponentInstance
    : public CppComponentInstance<facebook::react::RNViewOverflowShadowNode>
    {
 private:
  StackNode m_stackNode{};
    
 public:
  RNViewOverflowComponentInstance(Context context);
    
  void onChildInserted(ComponentInstance::Shared const& childComponentInstance, std::size_t index) override;
  void onChildRemoved(ComponentInstance::Shared const& childComponentInstance) override;
  void onPropsChanged(SharedConcreteProps const& props) override;
  void handleCommand(std::string const& commandName, folly::dynamic const& args) override;
  ArkUINode& getLocalRootArkUINode() override;
};
} // namespace rnoh