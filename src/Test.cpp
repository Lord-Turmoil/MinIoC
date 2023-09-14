// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#include <memory>
#include "Test.h"
#include "ServiceContainer.h"

void TestSingleton();
int main()
{
    TestSingleton();

    return 0;
}

void TestSingleton()
{
    printf("========== TEST: Singleton ==========\n\n");

    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New();

    // Register singleton with no dependency.
    container->RegisterSingleton<IA, A>();
    const auto a1 = container->ResolveService<IA>();
    a1->Print();
    const auto a2 = container->ResolveService<IA>();
    a2->Print();

    // Register singleton with dependency.
    container->RegisterSingleton<IB, B, IA>();
    const auto b1 = container->ResolveService<IB>();
    b1->Print();
    const auto b2 = container->ResolveService<IB>();
    b2->Print();

    // Register a given instance.
    const std::shared_ptr<IC> c = std::make_shared<C>(b1);
    container->RegisterSingleton(c);
    const auto c1 = container->ResolveService<IC>();
    c1->Print();
    const auto c2 = container->ResolveService<IC>();
    c2->Print();

    printf("\n========== TEST END ==========\n");
}
