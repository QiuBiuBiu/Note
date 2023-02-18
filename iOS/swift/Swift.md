# Swift

## 数据类型

## 标准类型
1. let用来定义一个常量
2. var用来定义一个变量

### 推断类型
```swift
    str = "Hello, Swift"
    let constStr = str
```
str和constStr都没有指定类型，并不意味它们没有类型，编译器会从它们的初始值推断它们的类型，这就叫类型推断。

### 指定类型
```swift
    var nextYear: Int
    var bodyTemp: Float
    var hasPet: Bool
    var arrayOfInts: [Int]
    var dict: [String, String]
    var set: Set<Int>
```

### 构造器
```swift
    let str = String()
    let arr = [Int]()
    let set = Set<Float>()
    let number = Int()
    let hasPet = Bool()
```

### 属性和方法
1. 如String有一个isEmpty属性
2. 如Array有一个count属性
3. 如Array有一个append(_:)方法


## 可选
Swift的类型是可选的，用类型名加上"?"表示：
```swift
    var number = Int?
    var strs = [String]?
```
1. 可选表示变量可能没有值。可选的值要么是指定类型的实例，要么是nil。
2. 读取可选类型时，要先查看值是否为nil，这个过程叫解包。解包分为：正常解包和强制解包。
    - 强制解包需要在变量名后面加一个"!"，但如果强制解包一个可选值，而正好这个可选值为nil，则会导致出错，应用停止运行。
    - 正常解包是更安全的方式。使用if-let语句，先把可选值赋值给临时的非可选常量，如果可选值有值，那么赋值有效，并使用临时常量来执行后面代码；如果可选值为nil，则在else中处理这种情况。
```swift
    if let num = number {
        print("Hello")
    } else {
        let errorStr = "number is nil"
    }
```

## 循环
Swift使用while和for-in语句来实现循环：
```swift
    for index in 1...5 {
        print("\(index) 乘于 5 为：\(index * 5)")
    }

    var someInts:[Int] = [10, 20, 30]
    for index in someInts {
        print( "index 的值为 \(index)")
    }
```

## 枚举和switch
与C++不一样，Swift只会执行明确指定条件部分的代码，执行完后不会继续执行下一个条件，如果希望执行下一个条件，需要使用fallthrough关键字。
```swift
    enum PieType: Int {
        case Apple = 0
        case Cherry
        case Pecan
    }
```

