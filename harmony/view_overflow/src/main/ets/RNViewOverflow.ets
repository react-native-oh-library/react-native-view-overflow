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

import {
  Descriptor,
  ViewBaseProps,
  RNViewBase,
  ComponentBuilderContext,
  Tag,
  RNComponentContext,
} from '@rnoh/react-native-openharmony'
import Logger from './Logger';
import { viewOverflowComponentFactoryBuilder } from './ViewOverflowComponentFactory';

export const VIEW_OVER_FLOW_TYPE: string = "RNViewOverflow";

export interface ViewPagerProps extends ViewBaseProps {

}

export type ViewPagerDescriptor = Descriptor<"RNViewOverflow", ViewPagerProps>

@Component
export struct RNViewOverflow {
  ctx!: RNComponentContext
  tag: number = 0
  @BuilderParam public renderChildren: () => void
  @BuilderParam buildCustomComponent: (ComponentBuilderContext: ComponentBuilderContext) => void
  @State descriptor: ViewPagerDescriptor = {} as ViewPagerDescriptor
  private unregisterDescriptorChangesListener?: () => void = undefined
  private cleanupCommandCallback?: () => void = undefined
  private unregisterComponentManager?: () => void = undefined


  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<ViewPagerDescriptor>(this.tag)
    Logger.info(`liwang--------------------->RNViewOverflow.aboutToAppear.props=${JSON.stringify(this.descriptor.rawProps)}`);
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.descriptor = (newDescriptor as ViewPagerDescriptor)
      }
    )
    this.cleanupCommandCallback = this.ctx.componentCommandReceiver.registerCommandCallback(
      this.tag,
      (command, args: (boolean | number)[]) => {

      });
  }

  aboutToDisappear() {
    this.cleanupCommandCallback?.();
    this.unregisterDescriptorChangesListener?.()
    this.unregisterComponentManager?.()
  }

  build() {
    RNViewBase({ ctx: this.ctx, tag: this.tag}) {
      Stack() {
        ForEach(this.descriptor.childrenTags, (tag: Tag) => {
          viewOverflowComponentFactoryBuilder(
            this.ctx,
            tag,
            this.ctx.rnInstance.getComponentNameFromDescriptorType(this.ctx.descriptorRegistry.getDescriptor(tag)?.type))
        }, (tag: Tag) => tag.toString())
      }
      .width("100%")
      .height("100%")
      .clip(true)
      .alignContent(Alignment.TopStart)
    }
  }
}