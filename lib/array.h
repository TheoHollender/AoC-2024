
#include <vector>

template<typename T>
std::vector<T> uncumul (std::vector<T> values) {
    std::vector<T> result(values.size() - 1);

    for (int i = 0; i < result.size(); i ++)
        result[i] = values[i + 1] - values[i];
    
    return result;
}
