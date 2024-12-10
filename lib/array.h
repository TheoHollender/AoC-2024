
#include <vector>

template<typename T>
std::vector<T> uncumul (std::vector<T> values) {
    std::vector<T> result(values.size() - 1);

    for (int i = 0; i < result.size(); i ++)
        result[i] = values[i + 1] - values[i];
    
    return result;
}

vector<string> split (string buffer,  string value) {
    int last = 0;
    vector<string> res;
    for (int offset = 0; offset < buffer.size(); offset ++) {
        if (buffer.substr(offset, value.size()) == value) {
            res.push_back( buffer.substr(last, offset - last) );
            offset += value.size() - 1;
            last = offset + 1;
        }
    }
    res.push_back(buffer.substr(last));
    return res;
}
template<typename T>
int index (vector<T> &values, T value) {
    for (int i = 0; i < values.size(); i ++)
        if (values[i] == value)
        return i ;
    return -1;
}
