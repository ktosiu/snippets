#include <iostream>
#include <cmath>
#include <string>
#include <cstdint>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

unsigned int g_FastHashTable[256];
static const unsigned int POLYNOMIAL = 0xF3C5F6A9;
void CreateHashTable()
{
    unsigned int *pHashTable = g_FastHashTable;
    unsigned int bit0;
    unsigned int byte;

    for (unsigned int i = 0; i < 256; i++)
    {
        byte = i;
        for (unsigned int j = 0; j < 8; j++)
        {
            bit0 = byte & 0x1;
            byte = byte >> 1;
            if (bit0)
            {
                byte = byte ^ POLYNOMIAL;
            }
        }
        pHashTable[i] = byte;
    }
}

void CalculateFastRicHash32(const char *pBuffer,
    unsigned int uiLength,
    unsigned int *pHashValue)
{
    unsigned int crc(*pHashValue);
    for (unsigned int i = 0; i < uiLength; ++i)
    {
        crc = crc ^ static_cast<unsigned int>(pBuffer[i]);
        unsigned int f = g_FastHashTable[(crc & 0xff)];
        crc >>= 8;
        crc ^= f;
    }
    *pHashValue = crc;
}

uint64_t CalculateDenominator(uint64_t uiMaximumHashValue,
    uint64_t uiTotalHashEntities)
{
    return static_cast<uint64_t>(
        std::ceil(static_cast<double>(uiMaximumHashValue) / uiTotalHashEntities));
}

uint64_t CalculateHashEntity(uint64_t uiHashValue,
    uint64_t uiTotalHashEntities,
    uint64_t uiMaximumHashValue)
{
    uint64_t uiDenominator = CalculateDenominator(uiMaximumHashValue, uiTotalHashEntities);
    return static_cast<uint64_t>((uiHashValue / uiDenominator) + 1);
}

char* get_cmd_option(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmd_option_exists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
    char* ric_name = get_cmd_option(argv, argv + argc, "-r");
    if (!ric_name)
    {
        std::cout << "Usage: ./calc_hash -r RICName -e MaxEntities\n";
        return -1;
    }

    char* entities = get_cmd_option(argv, argv + argc, "-e");
    uint64_t uiEntities = 0;
    if (entities)
    {
        try
        {
            uiEntities = (uint64_t)std::stoi(std::string(entities));
        }
        catch(const std::exception &e)
        {
            std::cout << "Usage: ./calc_hash -r RICName -e MaxEntities" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "Usage: ./calc_hash -r RICName -e MaxEntities\n";
    }

    CreateHashTable();

    unsigned int hash = 0;
    uint64_t max_hash_value = 0x100000000;

    CalculateFastRicHash32(ric_name, strlen(ric_name), &hash);
    uint64_t calculated_entity = CalculateHashEntity(hash, atoi(entities), max_hash_value) - 1;
    std::cout << "Hash value: " << hash << std::endl;
    std::cout << "Index: "<< calculated_entity << std::endl;
    return 0;
}
