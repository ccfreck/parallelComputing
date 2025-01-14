#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

void PrintVector(const std::vector<uint64_t>& vec)
{
    for (const auto& val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void accumulateRange(uint64_t &sum, uint64_t start, uint64_t end)
{
    sum = 0;
    for (uint64_t i = start; i < end; i++)
    {
        sum += i;
    }
}

int main()
{
    int num_threads;
    std::cout << "Please enter the number of threads: ";
    std::cin >> num_threads;
    
    const int num_elements = 100;
    const int step = num_elements / num_threads;

    std::vector<std::thread> threads;
    std::vector<uint64_t> partial_sums (num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * step;
        int end = (i == num_threads - 1) ? num_elements: (i+1) * step;
        threads.push_back(std::thread(accumulateRange, std::ref(partial_sums[i]), start, end));
    }

    for (auto& t: threads)
    {
        t.join();
    }

    uint64_t total = std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));
    PrintVector(partial_sums);
    std::cout << "total: " << total << std::endl;

    return 0;
}