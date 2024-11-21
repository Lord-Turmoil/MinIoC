#include <mioc.h>
#include "Test.h"
#include "doctest.h"

TEST_CASE("Singleton")
{
    const mioc::ServiceContainerPtr container = mioc::ServiceContainer::New(false);

    // Register interfaces and implementations.
    container->AddSingleton<IA, A>();
    container->AddSingleton<IB, B, IA>();

    // Resolve instances.
    const auto a1 = container->Resolve<IA>();
    const auto a2 = container->Resolve<IA>();
    CHECK_EQ(a1->ToString(), a2->ToString());

    const auto b1 = container->Resolve<IB>();
    const auto b2 = container->Resolve<IB>();
    CHECK_EQ(b1->ToString(), b2->ToString());

    // Register a given instance.
    const std::shared_ptr<IC> c1 = std::make_shared<C>(b1);
    container->AddSingleton(c1);
    const auto c2 = container->Resolve<IC>();
    CHECK_EQ(c1->ToString(), c2->ToString());
}
