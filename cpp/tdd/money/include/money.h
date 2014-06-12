#pragma once

struct Dollar
{
    Dollar(int amount)
        : amount_(amount)
    {
    }

    void times(int mutltipier);

    int amount_;
};
