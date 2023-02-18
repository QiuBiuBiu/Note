# UIStackView
StackView是一个流线型的接口，用来布局一组要么是一行或者是一列的views
    - stackview一个强大的特性是可以嵌套。


## Initializing a stack view
### init(arrangedSubviews:)
返回一个新的stackview对象，用来管理给定的view

## managing arranged subviews
### var arrangedSubviews: [UIView] { get }
由stackview排列的视图的列表，stackview确保arrangedSubviews数组总是subviews数组的一个子集。

### func addArrangedSubview(_ view: UIView)
添加一个视图到stackview的arrangedSubviews数组的尾端。

### func removeArrangedSubview(_ view: UIView)
从stackview的arrangedSubviews数组里删除一个给定的view。

### func insertArrangedSubview(_ view: UIView, at stackIndex: Int)

## Configuring the layout
### axis
用来决定arranged views(子视图)的布局方向。
1. NSLayoutConstraint.Axis.vertical：创建一列views。
2. NSLayoutConstraint.Axis.horizontal：创建一行views。（默认值）

## spacing
用来决定stackview中两个相邻子视图的距离。
    - 对于fillProportionally这种布局，spacing的大小是严格固定的
    - 对于equalSpacing和equalCentering这两种布局，spacing的大小只是一个最小值，真实的间距可能比它大
    - 可以为负值来表示重叠(overlap)
    - 默认值是0.0

### alignment
用来决定子视图的对齐方式。
1. fill：在垂直于axis的方向上尽可能地填充。(默认值)
2. center：基于axis中心对齐。
3. leading(top)：左对齐(上对齐)
4. trailing(bottom)：右对齐(下对齐)
5. firstBaseline
6. lastBaseline

## distribution
用来决定子视图基于axis该如何布局(大小和位置)。
1. fill：如果子视图比stackview大，会根据compression resistance priority来压缩(shrinks)子视图；反之，则会根据hugging priority来拉伸(stretches)子视图。（默认）
    - hugging priority(内容变多优先级)：越高的视图越不会被拉伸。
    - content compression resistance(内容变少优先级)：越高的视图更能抵抗压缩。
2. fillEqually：用同样的尺寸来布局子视图。(这里的尺寸是stackview的总尺寸减去所有的spacing之后均分给所有子视图)
3. fillProportionally：用子视图它们本身的尺寸(their intrinsic content size)来布局。
4. equalSpacing：先按3中的方式布局，如果放不下，则根据compression resistance priority来压缩子视图；反之。
5. equalCentering



