/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import { Descriptor, ComponentBuilderContext, Tag, RNComponentFactory,
  RNComponentContext } from '@rnoh/react-native-openharmony'
import { RNViewOverflow, VIEW_OVER_FLOW_TYPE } from './RNViewOverflow'

export type CustomComponentBuilder = (ctx: ComponentBuilderContext) => void

export class BuilderProxy {
  public static buildCustomComponent: CustomComponentBuilder
}

@Component
export struct ViewOverflowComponentFactory {
  public ctx!: RNComponentContext
  public tag: number = 0
  @BuilderParam public buildCustomComponent!: CustomComponentBuilder
  @State private componentName: string = ''
  @State private childrenTags: Tag[] = []
  private cleanupCallback?: () => void = undefined

  aboutToAppear() {
    const descriptor = this.ctx.descriptorRegistry.getDescriptor<Descriptor>(this.tag)
    if (descriptor) {
      this.setDescriptor(descriptor)
    }
    this.cleanupCallback = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(
      this.tag, (newDescriptor) => this.setDescriptor(newDescriptor)
    )
  }

  aboutToDisappear() {
    this.cleanupCallback?.()
  }

  setDescriptor(newDescriptor: Descriptor) {
    this.componentName = newDescriptor.type
    this.childrenTags = newDescriptor.childrenTags
  }

  build() {
    if (this.componentName === VIEW_OVER_FLOW_TYPE) {
      RNViewOverflow({
        ctx: this.ctx,
        tag: this.tag,
        buildCustomComponent: this.buildCustomComponent
      })
    }
  }
}

@Builder
export function viewOverflowComponentFactoryBuilder(ctx: RNComponentContext, tag: Tag, componentName: string) {
  if (componentName === VIEW_OVER_FLOW_TYPE) {
    RNViewOverflow({
      ctx: ctx,
      tag: tag,
      buildCustomComponent: BuilderProxy.buildCustomComponent
    });
  }
  else if (componentName !== '') {
    ctx.wrappedRNChildrenBuilder.builder(ctx, tag)
    // RNComponentFactory({ ctx: ctx, tag: tag, buildCustomComponent: BuilderProxy.buildCustomComponent });
  }

}