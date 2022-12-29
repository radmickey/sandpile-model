#pragma once
#include <cinttypes>
#include <iostream>
#include <unordered_map>
#include <queue>

#include <fstream>
#include <string>
#include <vector>


class Sandpile {

private:
    uint64_t name_num = 1;

    std::unordered_map<std::string, int64_t> sandpile;
    std::queue<std::pair<int, int>> queue;

    int max_x = 0;
    int min_x = 0;
    int max_y = 0;
    int min_y = 0;

public:
    std::string tsv_path;
    std::string out_path;
    int64_t max_iter;
    int64_t freq;
    int64_t length;
    int64_t width;

    void setFromTSV(std::string& path_file);

    void setGrains(std::pair<int, int>, int64_t value);

    void spilling();

    void printToBMP(bool freqZero);

};
