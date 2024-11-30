#include <mioc/mioc.h>
#include "Test.h"
#include "doctest.h"

TEST_CASE("Assignment")
{
    mioc::ServiceContainerPtr containerA = mioc::ServiceContainer::New();
    mioc::ServiceContainerPtr containerB = mioc::ServiceContainer::New();

    // Register interfaces and implementations.
    containerA->AddSingleton<IA, A>();
    containerA->AddSingleton<IB, B, IA>();

    // Copy container.
    *containerB = *containerA;

    auto a1 = containerA->Resolve<IA>();
    auto a2 = containerB->Resolve<IA>();
    CHECK_EQ(a1->ToString(), a2->ToString());

    const auto b1 = containerA->Resolve<IB>();
    const auto b2 = containerB->Resolve<IB>();
    CHECK_EQ(b1->ToString(), b2->ToString());

    // Register new instance.
    const std::shared_ptr<IC> c = std::make_shared<C>(b1);
    containerA->AddSingleton(c);
    CHECK_NE(containerA->Resolve<IC>(), nullptr);
    CHECK_EQ(containerB->Resolve<IC>(), nullptr);

    // Move container.
    mioc::ServiceContainerPtr containerC = mioc::ServiceContainer::New();
    *containerC = std::move(*containerA);
    CHECK_EQ(containerC->Resolve<IA>()->ToString(), a1->ToString());
    CHECK_EQ(containerC->Resolve<IB>()->ToString(), b1->ToString());
    CHECK_EQ(containerC->Resolve<IC>(), nullptr);
}
