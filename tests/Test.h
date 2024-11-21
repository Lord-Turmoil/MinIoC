#pragma once

#ifndef _MIOC_TEST_H_
#define _MIOC_TEST_H_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Class interfaces.
class IBase
{
public:
    virtual ~IBase() = default;

    virtual std::string ToString() = 0;

    virtual void Print()
    {
        std::cout << ToString() << std::endl;
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
        std::cout << "A[" << this << "] created." << std::endl;
    }

    std::string ToString() override
    {
        std::stringstream ss;
        ss << "A[" << this << "]";
        return ss.str();
    }
};

class B : public IB
{
public:
    explicit B(const std::shared_ptr<IA>& a) : _a(a)
    {
        std::cout << "B[" << this << "] created." << std::endl;
    }

    std::string ToString() override
    {
        std::stringstream ss;
        ss << "B[" << this << "]";
        return ss.str();
    }

private:
    std::shared_ptr<IA> _a;
};

class C : public IC
{
public:
    explicit C(const std::shared_ptr<IB>& b) : _b(b)
    {
        std::cout << "C[" << this << "] created." << std::endl;
    }

    std::string ToString() override
    {
        std::stringstream ss;
        ss << "C[" << this << "]";
        return ss.str();
    }

private:
    std::shared_ptr<IB> _b;
};

#endif
