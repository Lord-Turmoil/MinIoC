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
    container->AddSingleton<IA, A>();
    const auto a1 = container->Resolve<IA>();
    a1->Print();
    const auto a2 = container->Resolve<IA>();
    a2->Print();

    // Register singleton with dependency.
    container->AddSingleton<IB, B, IA>();
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

    printf("\n========== TEST END ==========\n");
}
