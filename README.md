## Mini IoC

A mini IoC implementation with C++.

> ## Reference
>
> The implementation of this IoC is based on [A Miniature IOC Container in C++](https://www.codeproject.com/Articles/1029836/A-miniature-IOC-Container-in-Cplusplus).
>
> Some necessary modification is made to the source code on the website, and here is the original License: [The Code Project Open License (CPOL)](https://www.codeproject.com/info/cpol10.aspx)

---

## 1. Overview

This container provides two object lifetime - singleton and transient. Singleton object will be created only once, while transient object will be constructed every time it is resolved. What's more, for singleton objects, it by default provides lazy initialization. Of course, you can choose not enable it.

Since everything is implemented with C++ template, so there are only header files located under `mioc/include` directory. And a test file `Test.cpp` is placed under `src/` directory as an example.

To avoid pointer problems, I use `std::shared_ptr` to wrap all native pointers. 🙂

## 2. Usage

### 2.1 Test Classes

Here are the classes we use in this demonstration. Interfaces are omitted as they are really simple. We can see that, B depends on A, and C depends on B.

```cpp
class A : public IA
{
public:
    A() = default;
};

class B : public IB
{
public:
    B(std::shared_ptr<IA> a) :_a(std::move(a)) {}
private:
    std::shared_ptr<IA> _a;
};

class C : public IC
{
public:
    C(std::shared_ptr<IB> b) : _b(std::move(b)) {}
private:
    std::shared_ptr<IB> _b;
};
```

### 2.2 Create Container

You can create a container using `ServiceContainer::New()`. In this case, you have to inject this container everywhere you need. You can choose whether to enable lazy initialization for this container on, and **only on** creation. You **won't** be able to change it later. By default, lazy initialization is enabled.

```cpp
#include "ServiceContainer.h"
mioc::ServiceContainerPtr lazyContainer = mioc::ServiceContainer::New();
mioc::ServiceContainerPtr hungryContainer = mioc::ServiceContainer::New(false);
```

Or, you can use `SingletonContainer` which provides you a global scale singleton container. This container will not be created until the first time you get it. Also, on your first call, you can choose whether to enable lazy initialization for the global container.

```cpp
#include "SingletonContainer.h"
// by default, global container enables lazy initialization
mioc::ServiceContainerPtr container = mioc::SingletonContainer::GetContainer();
// or you can disable it on, and only on the first call
mioc::ServiceContainerPtr container = mioc::SingletonContainer::GetContainer(false);
```

### 2.3 Add Singleton

First, is to use type name only. You should provide its interface type, and concrete type. And all dependency types if it has.

```cpp
container->AddSingleton<IA, A>();      // without dependency
container->AddSingleton<IB, B, IA>();  // with dependencies
```

Also, you can directly add a pre-constructed instance to it. This way, you may need a pointer conversion first, which convert concrete type to its corresponding interface. You don't need to pass type name in this case. And, of course, lazy initialization matter not in this way.

```cpp
std::shared_ptr<IC> c = std::make_shared<C>(b);
container->AddSingleton(c);
```

### 2.4 Add Transient

It is simpler to add a transient object. We just need to pass type names, and they will be properly resolved later.

```cpp
container->AddTransient<IA, A>();
container->AddTransient<IB, B, IA>();
container->AddTransient<IC, C, IB>();
```

### 2.5 Resolve Instances

No matter which way you use to add objects into the container, you can always resolve a instance with the interface type you provided on adding. `nullptr` will be returned if the interface is not registered.

```cpp
std::shared_ptr<IC> c = container->Resolve<IC>();
```

## 3. Limitations

Though this mini IoC container can handle dependency injection, you have to manually specify all dependencies when you add anything. 🥲

