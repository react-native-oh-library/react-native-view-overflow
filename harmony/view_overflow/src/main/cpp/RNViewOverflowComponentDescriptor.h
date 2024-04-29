#pragma once

#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>
#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

inline const char RNViewOverflowComponentName[] = "RNViewOverflow";

class RNViewOverflowProps : public ViewProps {
 public:
  RNViewOverflowProps() = default;

  RNViewOverflowProps(
      const PropsParserContext& context,
      const RNViewOverflowProps& sourceProps,
      const RawProps& rawProps)
      : ViewProps(context, sourceProps, rawProps) {}
};

class RNViewOverflowEventEmitter : public ViewEventEmitter {
 public:
  using ViewEventEmitter::ViewEventEmitter;
};

using RNViewOverflowShadowNode = ConcreteViewShadowNode<RNViewOverflowComponentName, RNViewOverflowProps, RNViewOverflowEventEmitter>;

class RNViewOverflowComponentDescriptor final
    : public ConcreteComponentDescriptor<RNViewOverflowShadowNode> {
 public:
  RNViewOverflowComponentDescriptor(ComponentDescriptorParameters const& parameters)
      : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
