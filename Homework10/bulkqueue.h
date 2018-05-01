#pragma once

#include <queue>
#include <vector>

using strVector = std::vector<std::string>;

struct BulkQueue
{
    std::string timestamp;
    std::queue<strVector> bulk;
};