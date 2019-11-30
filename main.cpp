#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

const size_t ARRAY_LENGTH = 10;
size_t g_iter_count = 0;

#ifdef ENABLE_LOGGING
    #define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
    #define LOG_VEC(vec, l, h, mid) pretty_print_vec(vec, l, h, mid);
#else
    #define LOG(fmt, ...)
    #define LOG_VEC(vec, l, h, mid)
#endif

std::vector<uint32_t> create_vec(int64_t rotation_amount)
{
    std::vector<uint32_t> vec(ARRAY_LENGTH);
    std::generate(vec.begin(), vec.end(), [](){
        static uint32_t v = 0;
        return v++;
    });

    // normalize rotation_amount
    int64_t normalized_rotation = llabs(rotation_amount) % vec.size();
    normalized_rotation = (rotation_amount > 0) ? (vec.size() - normalized_rotation) : normalized_rotation;

    std::rotate(vec.begin(), vec.begin() + normalized_rotation, vec.end());
    return vec;
}

void pretty_print_vec(const std::vector<uint32_t>& vec, size_t l = -1, size_t h = -1, size_t mid = -1)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        const bool is_visible = ((l == -1) && (h == -1)) || ((i >= l) && (i <= h));

        if (is_visible)
        {
            const bool is_mid = (mid != -1) && (mid == i);
            std::cout << (is_mid ? "<" : " ") << vec[i] << (is_mid ? ">" : " ");
        }
        else
            std::cout << "   ";

        if (i != vec.size() - 1)
            std::cout << ", ";
    }

    std::cout << "]" << std::endl;
}

ssize_t shifted_binary_search(const std::vector<uint32_t>& vec, uint32_t n, size_t l, size_t h)
{
    if (l > h)
    {
        return -1;
    }

    size_t mid = (l + h) / 2;

    LOG("Iteration %lu, array: ", ++g_iter_count);
    LOG_VEC(vec, l, h, mid);

    if (vec[mid] == n)
        return mid;

    if (vec[l] <= vec[mid])
    {
        LOG("The lower range is sorted (%u <= %u), ", vec[l], vec[mid]);
        if ((n >= vec[l]) && (n <= vec[mid]))
        {
            // search again in [low, mid_index-1]
            LOG("the element %u is within indices [%lu, %lu], assuming search in the lower range indices [%lu, %lu]\n\n",
                    n, l, mid, l, mid - 1);
            return shifted_binary_search(vec, n, l, mid - 1);
        }
        else
        {
            LOG("the element %u is NOT within indices [%lu, %lu], assuming search in the other HIGHER range indices [%lu, %lu]\n\n",
                    n, l, mid, mid + 1, h);
            return shifted_binary_search(vec, n, mid + 1, h);
        }
    }
    else
    {
        LOG("The HIGHER range is sorted (%u <= %u), ", vec[mid], vec[h]);
        if ((n >= vec[mid]) && (n <= vec[h]))
        {
            // search again in [mid_index + 1, high]
            LOG("the element %u is within indices [%lu, %lu], assuming search in the HIGHER range indices [%lu, %lu]\n\n",
                    n, mid, h, mid + 1, h);
            return shifted_binary_search(vec, n, mid + 1, h);
        }
        else
        {
            LOG("the element %u is within indices [%lu, %lu], assuming search in the other lower range indices [%lu, %lu]\n\n",
                n, mid, h, l, mid - 1);
            return shifted_binary_search(vec, n, l, mid - 1);
        }

    }

}

ssize_t find(/*sorted*/ const std::vector<unsigned int>& haystack, unsigned int needle)
{
    return shifted_binary_search(haystack, needle, 0, haystack.size() - 1);
}

int main()
{
    std::cout << "This is an interactive demo" << std::endl;
    std::cout << "  POSITIVE number is a RIGHT shift (>> operator equivalent)" << std::endl;
    std::cout << "  NEGATIVE number is a LEFT  shift (<< operator equivalent)" << std::endl;

    int64_t rotation_amount = 12;
    std::cout << "Rotation amount (integer): ";
    std::cin >> rotation_amount;

    uint32_t needle = 6;
    std::cout << "Element to find (unsigned integer): ";
    std::cin >> needle;

    const std::vector<uint32_t>& vec = create_vec(rotation_amount);
    const ssize_t index = find(vec, needle);
    std::cout << "DONE. Index of element " << needle << " in the array is " << index << ". ";
    std::cout << "The element is " << ((index > 0) ? "" : "not ") << "found." << std::endl;

    return 0;
}
