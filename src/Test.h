#pragma once

#ifndef _MIOC_TEST_H_
#define _MIOC_TEST_H_

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <ctime>
#include <memory>
#include <string>

// Class interfaces.
class IBase
{
public:
    virtual ~IBase() = default;

    virtual std::string ToString() = 0;
    virtual void Print()
    {
        printf("%s\n", ToString().c_str());
    }
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
    A()
    {
        printf("A[%p] created.\n", static_cast<void*>(this));
    }

    std::string ToString() override
    {
        char buffer[128];
        sprintf(buffer, "A[%p]", static_cast<void*>(this));
        return buffer;
    }
};

class B : public IB
{
public:
    B(std::shared_ptr<IA> a) :_a(std::move(a))
    {
        printf("B[%p] created.\n", static_cast<void*>(this));
    }

    std::string ToString() override
    {
        char buffer[128];
        sprintf(buffer, "B[%p]", static_cast<void*>(this));
        std::string ret = _a->ToString() + "  " + buffer;
        return ret;
    }

private:
    std::shared_ptr<IA> _a;
};

class C : public IC
{
public:
    C(std::shared_ptr<IB> b) : _b(std::move(b))
    {
        printf("C[%p] created.\n", static_cast<void*>(this));
    }

    std::string ToString() override
    {
        char buffer[128];
        sprintf(buffer, "C[%p]", static_cast<void*>(this));
        std::string ret = _b->ToString() + "  " + buffer;
        return ret;
    }

private:
    std::shared_ptr<IB> _b;
};

#endif
