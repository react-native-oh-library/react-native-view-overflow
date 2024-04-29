#include "RNViewOverflowComponentInstance.h"

namespace rnoh {

RNViewOverflowComponentInstance::RNViewOverflowComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    m_stackNode.setClip(true);
}

void RNViewOverflowComponentInstance::onChildInserted(ComponentInstance::Shared const& childComponentInstance, std::size_t index) {
  CppComponentInstance::onChildInserted(childComponentInstance, index);
  m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index + 1);
}

void RNViewOverflowComponentInstance::onChildRemoved(ComponentInstance::Shared const& childComponentInstance) {
  CppComponentInstance::onChildRemoved(childComponentInstance);
  m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
}

void RNViewOverflowComponentInstance::onPropsChanged(SharedConcreteProps const& props) {
    CppComponentInstance::onPropsChanged(props);
}

void RNViewOverflowComponentInstance::handleCommand(std::string const& commandName, folly::dynamic const& args) {
    CppComponentInstance::handleCommand(commandName, args);
}

ArkUINode& RNViewOverflowComponentInstance::getLocalRootArkUINode() {
  return m_stackNode;
}

} // namespace rnoh
