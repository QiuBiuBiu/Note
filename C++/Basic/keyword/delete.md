# delete

## delete this 合法吗？

> [Is it legal (and moral) for a member function to say delete this?](https://isocpp.org/wiki/faq/freestore-mgmt#delete-this)

合法，但：

1. 必须保证 this 对象是通过 `new`（不是 `new[]`、不是 placement new、不是栈上、不是全局、不是其他对象成员）分配的
2. 必须保证调用 `delete this` 的成员函数是最后一个调用 this 的成员函数
3. 必须保证成员函数的 `delete this ` 后面没有调用 this 了
4. 必须保证 `delete this` 后没有人使用了