# Mini IoC

A mini IoC implementation with C++.

> ## Reference
>
> The implementation of this IoC is based on [A Miniature IOC Container in C++](https://www.codeproject.com/Articles/1029836/A-miniature-IOC-Container-in-Cplusplus).
>
> Some necessary modifications have been made to the source code on the website, and here is the original License: [The Code Project Open License (CPOL)](https://www.codeproject.com/info/cpol10.aspx)

---
[![Build](https://github.com/Lord-Turmoil/MinIoc/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)](https://github.com/Lord-Turmoil/MinIoc/actions/workflows/cmake-multi-platform.yml)

## 1. Overview

This mini IoC container provides basic adding and resolving abilities and the simplest dependency injection. It provides two lifetimes - singleton and transient. Singleton object will be created only once, while transient object will be constructed every time it is resolved. What's more, it can provide lazy initialization for singleton instances. 😁

Since everything is implemented with C++ template, only header files are located under the `mioc/include` directory. A test file, `Test.cpp` is placed under the `src/` directory as an example.

To avoid pointer problems, `std::shared_ptr` is used everywhere to wrap all native pointers. 🙂

It will be very nice for you to light up the 🌟. :)

## 2. Usage

### 2.1 Test Classes

Here are the classes we use in this demonstration. Interfaces are omitted as they are straightforward. We can see that B depends on A, and C depends on B. 🧐

```cpp
class A : public IA
{
public:
    A() = default;
};

class B : public IB
{
public:
    B(const std::shared_ptr<IA>& a) :_a(a) {}
private:
    std::shared_ptr<IA> _a;
};

class C : public IC
{
public:
    C(const std::shared_ptr<IB>& b) : _b(b) {}
private:
    std::shared_ptr<IB> _b;
};
```

### 2.2 Create Container

All required header files are included in `mioc.h`, simply include this header file, and you are ready to go!

You can create a container using `ServiceContainer::New()`. In this case, you have to inject this container everywhere you need. You can choose whether to enable lazy initialization for this container **on creation**. You **won't** be able to change it later. By default, lazy initialization is enabled.

```cpp
mioc::ServiceContainerPtr lazyContainer = mioc::ServiceContainer::New();
mioc::ServiceContainerPtr hungryContainer = mioc::ServiceContainer::New(false);
```

Or, you can use `SingletonContainer`, which provides a global-scale singleton container. This container will not be created until the first time you get it. Also, on your first call, you can choose whether to enable lazy initialization for the global container.

```cpp
// by default, the global container enables lazy initialization
mioc::ServiceContainerPtr container = mioc::SingletonContainer::GetContainer();
// or you can disable it on, and only on the first call
mioc::ServiceContainerPtr container = mioc::SingletonContainer::GetContainer(false);
```

### 2.3 Add Singleton

The first is to use the type name only. You should provide its interface type and concrete type. And all dependency types if it has.

```cpp
container->AddSingleton<IA, A>();      // without dependency
container->AddSingleton<IB, B, IA>();  // with dependencies
```

Also, you can directly add a pre-constructed instance to it. This way, you may need a pointer conversion first, which converts concrete type to its corresponding interface. You don't need to pass a type name in this case. And, of course, lazy initialization matters not in this way.

```cpp
std::shared_ptr<IC> c = std::make_shared<C>(b);
container->AddSingleton(c);
```

### 2.4 Add Transient

It is simpler to add a transient object. We need to pass type names, and they will be appropriately resolved later.

```cpp
container->AddTransient<IA, A>();
container->AddTransient<IB, B, IA>();
container->AddTransient<IC, C, IB>();
```

### 2.5 Resolve Instances

No matter how you add objects into the container, you can always resolve an instance with the interface type you provided on adding. `nullptr` will be returned if the interface is not registered.

```cpp
std::shared_ptr<IC> c = container->Resolve<IC>();
```

## 3. Limitations

Though this mini IoC container can handle dependency injection, you have to specify all dependencies when you add anything manually. 🥲

