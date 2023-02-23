# Accessibility for UIKit


## VoiceOver
* 单击屏幕上的任意位置，VoiceOver 会大声念出项目的辅助功能属性中的识别信息 (identifying information)。
* 向左或向右轻扫 (swipe)，VoiceOver 会选择下一个可视辅助功能项目并大声念出该项目。右扫则向右向下移动，左扫移动方向相反。
* 向下轻扫可以逐个地念出每个字母（或汉字、符号等）。
* 双击选中聚焦的项目。
* 三指轻扫，向左或向右轻扫，可以在不同页面视图间前进或后退（译者注：例如网页的前进后退，或桌面左右滑动等）

## Supporting basic accessibility
以下属性的值当元素是一个标准的UIKit control时会有默认值，否则它们的值为nil或者false

- isAccessibilityElement：一个boolean类型的值，用来表明元素是否能被辅助应用程序访问。

- 标签(accessibilityLabel)：一个本地化字符串，用于标识可访问性元素。例如"Select all button"。
    - 默认值：the value is a label that derives from the control’s title.

- 特性(accessibilityTraits)：描述元素的状态、行为或用法。例如，一个按钮的特性可能是"Select all button，`Selected`"。

- 提示(accessibilityHint)：描述元素可以完成的动作。例如："双击打开Participant list"。
    - 默认值：the value is a system-provided hint that derives from the type of control.

- 值(accessibilityValue)：一个本地化字符串，包含可访问性元素的值（适用于一个固定的label和一个动态变化的value的场景，accessibilityValue用来返回这个动态变化的value）。
    - 默认值：the value of the property represents the value of the control when it differs from the label.

