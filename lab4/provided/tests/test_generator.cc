#include <cstdlib>
#include <cstdint>
#include <cstdio>

#include <algorithm>
#include <chrono>
#include <random>
#include <string>

#include "../record_store.hh"
#include "../util.hh"

using namespace std;


static void generateRandomWriteFollowedByReadTest(string filename, size_t clusters,
                                                  size_t requestsPerCluster,
                                                  size_t numMemoryAreas,
                                                  size_t memoryAreaSize, // in max request size
                                                  int64_t minTicks, int64_t maxTicks,
                                                  int addressSize, int maxRequestSize)
{
    RecordStore store(filename);
    vector<Record>& records = store.getRecords();
    vector<uint64_t> addressesUsed;

    const uint64_t MAX_ADDRESS = (1ull << addressSize) - 1;
    const int LOG_REQUEST_SIZE = log2int(maxRequestSize);
    assert (MAX_ADDRESS >= maxRequestSize);

    // Create a random number generator, and seed it on the clock for less
    // deterministic results.
    default_random_engine rng;
    rng.seed(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<uint64_t> memDistribution(0,MAX_ADDRESS - memoryAreaSize * maxRequestSize);

    // Generate a table of memory addresses to use. We do this in a
    // number of memory areas, to somewhat mimic what various programs'
    // pages would look like in physical memory.
    for (size_t memArea = 0; memArea < numMemoryAreas; ++memArea) {
        const uint64_t memBase = memDistribution(rng) & ~uint64_t((1ull << LOG_REQUEST_SIZE) - 1);
        for (size_t i = 0; i < memoryAreaSize; ++i) {
            const uint64_t address = memBase + i * maxRequestSize;
            assert(address < ((uint64_t)1 << addressSize));
            assert((address &  (maxRequestSize - 1)) == 0); // naturally aligned
            addressesUsed.push_back(address);
        }
    }

    // Name the distributions for generation of Record parameters
    uniform_int_distribution<int64_t> tickDist(minTicks, maxTicks);
    uniform_int_distribution<int> sizeDist(0, LOG_REQUEST_SIZE);
    uniform_int_distribution<uint8_t> dataDist(0, 255);

    // Name a distribution for memory access
    uniform_int_distribution<size_t> addressIndexDist(0, addressesUsed.size() - 1);

    for (size_t cluster = 0; cluster < clusters; ++cluster) {
        for (size_t i = 0; i < requestsPerCluster; ++i) {
            size_t position = addressIndexDist(rng);
            if (cluster & 1) {
                const int requestSize = 1 << sizeDist(rng);
                records.push_back(Record(tickDist(rng),
                                        false,
                                        addressesUsed[position],
                                        records.size(),
                                        requestSize,
                                        {}));
            } else {
                const int requestSize = 1 << sizeDist(rng);
                vector<uint8_t> dataVec(requestSize);
                for (int dataIndex = 0; dataIndex < requestSize; ++dataIndex)
                    dataVec[dataIndex] = dataDist(rng);
                records.push_back(Record(tickDist(rng),
                                        true,
                                        addressesUsed[position],
                                        records.size(),
                                        requestSize,
                                        dataVec));
            }
        }
    }

    store.writeRecords();
}

int main() {
    generateRandomWriteFollowedByReadTest("randomSimple.txt", 2, 17, 4, 4, 5, 5, 32, 8);
    generateRandomWriteFollowedByReadTest("randomSimple10000.txt", 500, 20, 16, 256, 5, 5, 32, 8);
    generateRandomWriteFollowedByReadTest("randomStagger10000.txt", 500, 20, 16, 256, 1, 5, 32, 8);
    generateRandomWriteFollowedByReadTest("randomStagger1000000.txt", 25000, 40, 64, 8192, 1, 5, 32, 8);

    return 0;
}
