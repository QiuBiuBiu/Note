// 实现见SparkDelegate.h

/*
概括：
中介模式的设计思想跟中间层很像，通过引入中介这个中间层，将一组对象之间的交互关系（或者依赖关系）从多对多（网状关系）转换为一对多（星状关系）。
原来一个对象要跟 n 个对象交互，现在只需要跟一个中介对象交互，从而最小化对象之间的交互关系，降低了代码的复杂度，提高了代码的可读性和可维护性。

UCF：
1）class delegate作为中介者负责管理一组entry，entry是一个函数，也可以是一个lambda表达式
1.1）重载了 delegate& operator+=(const callback_t& callback) 方法，用来加入一个entry
1.2）重载了 void operator()(Args... args) const 方法，用来通知被通知者

2）通知者(如locusManager)
2.1）维护一系列delegate，也可以称之为事件， 如ILocusManager.h：
using RequestFailedEvent = spark::delegate<void(const model::CallPtr & call, const events::requestType & requestType, const model::CallErrorPtr & error)>;
RequestFailedEvent onRequestFailed;
...

2.2）通知（触发事件）(如LocusManager::handleJoinFailure)
onRequestFailed(call, events::requestType::join, callError);

3）被通知者(如TelephonyService)
3.1）注册函数到delegate中（或者说开始监听这个事件），如(TelephonyService::initLocusManager)：
locusManager->onRequestFailed += this, &TelephonyService::notifyCallFailure;

3.2）被通知者受到通知后执行相应操作（事件触发，响应事件）：
TelephonyService::notifyCallFailure()
*/

/*
中介模式和观察者模式的共同点和区别：
1. 观察者模式和中介模式都是为了实现参与者之间的解耦，简化交互关系。
2. 两者的不同在于应用场景上：
    2.1 在观察者模式的应用场景中，参与者之间的交互比较有条理，一般都是单向的，一个参与者只有一个身份，要么是观察者，要么是被观察者。
    2.2 而在中介模式的应用场景中，参与者之间的交互关系错综复杂，既可以是消息的发送者、也可以同时是消息的接收者。
*/