#include <mioc/mioc.h>
#include "Test.h"
#include "doctest.h"

TEST_CASE("Transient 1")
{
    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New();

    // Register interfaces and implementations.
    container->AddSingleton<IA, A>();
    container->AddTransient<IB, B, IA>();
    container->AddTransient<IC, C, IB>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    const auto a2 = container->Resolve<IA>();
    CHECK_EQ(a1->ToString(), a2->ToString());

    const auto b1 = container->Resolve<IB>();
    const auto b2 = container->Resolve<IB>();
    CHECK_NE(b1->ToString(), b2->ToString());

    const auto c1 = container->Resolve<IC>();
    const auto c2 = container->Resolve<IC>();
    CHECK_NE(c1->ToString(), c2->ToString());
}

TEST_CASE("Transient 2")
{
    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New();

    // Register interfaces and implementations.
    container->AddTransient<IA, A>();
    container->AddSingleton<IB, B, IA>();
    container->AddTransient<IC, C, IB>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    const auto a2 = container->Resolve<IA>();
    CHECK_NE(a1->ToString(), a2->ToString());

    const auto b1 = container->Resolve<IB>();
    const auto b2 = container->Resolve<IB>();
    CHECK_EQ(b1->ToString(), b2->ToString());

    const auto c1 = container->Resolve<IC>();
    const auto c2 = container->Resolve<IC>();
    CHECK_NE(c1->ToString(), c2->ToString());
}
