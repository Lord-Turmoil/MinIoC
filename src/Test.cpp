// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#include <memory>
#include "Test.h"
#include <mioc/ServiceContainer.h>
#include <mioc/SingletonContainer.h>

void TestSingleton();
void TestTransient();
void TestTransient2();

int main()
{
    const auto container = mioc::SingletonContainer::GetContainer();

    container->AddSingleton<IA, A>();

    TestSingleton();
    TestTransient();
    TestTransient2();

    return 0;
}

void TestSingleton()
{
    printf("========== TEST: Singleton ==========\n\n");

    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New(false);

    // Register interfaces and implementations.
    container->AddSingleton<IA, A>();
    container->AddSingleton<IB, B, IA>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    a1->Print();
    const auto a2 = container->Resolve<IA>();
    a2->Print();

    const auto b1 = container->Resolve<IB>();
    b1->Print();
    const auto b2 = container->Resolve<IB>();
    b2->Print();

    // Register a given instance.
    const std::shared_ptr<IC> c = std::make_shared<C>(b1);
    container->AddSingleton(c);
    const auto c1 = container->Resolve<IC>();
    c1->Print();
    const auto c2 = container->Resolve<IC>();
    c2->Print();

    printf("\n========== TEST END ==========\n\n");

    const auto a = mioc::SingletonContainer::GetContainer()->Resolve<IA>();
    printf("Global: ");
    a->Print();
    putchar('\n');
}


void TestTransient()
{
    printf("========== TEST: Transient ==========\n\n");

    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New();

    // Register interfaces and implementations.
    container->AddSingleton<IA, A>();
    container->AddTransient<IB, B, IA>();
    container->AddTransient<IC, C, IB>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    a1->Print();
    const auto a2 = container->Resolve<IA>();
    a2->Print();

    const auto b1 = container->Resolve<IB>();
    b1->Print();
    const auto b2 = container->Resolve<IB>();
    b2->Print();

    const auto c1 = container->Resolve<IC>();
    c1->Print();
    const auto c2 = container->Resolve<IC>();
    c2->Print();

    printf("\n========== TEST END ==========\n\n");

    const auto a = mioc::SingletonContainer::GetContainer()->Resolve<IA>();
    printf("Global: ");
    a->Print();
    putchar('\n');
}

void TestTransient2()
{
    printf("========== TEST: Transient 2 ==========\n\n");

    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New();

    // Register interfaces and implementations.
    container->AddTransient<IA, A>();
    container->AddSingleton<IB, B, IA>();
    container->AddTransient<IC, C, IB>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    a1->Print();
    const auto a2 = container->Resolve<IA>();
    a2->Print();

    const auto b1 = container->Resolve<IB>();
    b1->Print();
    const auto b2 = container->Resolve<IB>();
    b2->Print();

    const auto c1 = container->Resolve<IC>();
    c1->Print();
    const auto c2 = container->Resolve<IC>();
    c2->Print();

    printf("\n========== TEST END ==========\n\n");

    const auto a = mioc::SingletonContainer::GetContainer()->Resolve<IA>();
    printf("Global: ");
    a->Print();
    putchar('\n');
}
