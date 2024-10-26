#pragma once

class Base
{
    public:

        Base();
        ~Base();
    private:
        ;
        int val;
};

class Derived : public Base
{
    public:
        Derived();
        ~Derived();
    private:
        ;
};