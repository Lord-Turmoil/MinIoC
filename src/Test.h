#pragma once

#ifndef _MINIOC_TEST_H_
#define _MINIOC_TEST_H_

#include <cstdio>
#include <memory>

// Class interfaces.
class IBase
{
public:
    virtual ~IBase() = default;
    virtual void Print() = 0;
};

class IA : public IBase
{
public:
    ~IA() override = default;
};

class IB : public IBase
{
public:
    ~IB() override = default;
};

class IC : public IBase
{
public:
    ~IC() override = default;
};


// Concrete classes.
class A : public IA
{
public:
    A() = default;

    void Print() override
    {
        printf("A[%p]\n", static_cast<void*>(this));
    }
};

class B : public IB
{
public:
    B(std::shared_ptr<IA> a) :_a(std::move(a)) {}

    void Print() override
    {
        printf("A[%p]  B[%p]\n", static_cast<void*>(_a.get()), static_cast<void*>(this));
    }

private:
    std::shared_ptr<IA> _a;
};

class C : public IC
{
public:
    C(std::shared_ptr<IA> a, std::shared_ptr<IB> b) : _a(std::move(a)), _b(std::move(b)) {}

    void Print() override
    {
        printf("A[%p]  B[%p]  C[%p]\n",
            static_cast<void*>(_a.get()),
            static_cast<void*>(_b.get()),
            static_cast<void*>(this));
    }

private:
    std::shared_ptr<IA> _a;
    std::shared_ptr<IB> _b;
};

#endif
