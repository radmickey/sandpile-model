#include "sandpile.h"
#include "bmp.cpp"


std::string pair_to_str(std::pair<int, int> p) {
    return std::to_string(p.first) + "_" + std::to_string(p.second);
}
std::pair<int, int> str_to_pair(const std::string& str) {
    int x = std::stoi(str.substr(0, str.find('_')));
    int y = std::stoi(str.substr(str.find('_') + 1, str.size()));

    return std::make_pair(x, y);
}

void Sandpile::setGrains(std::pair<int, int> coord, int64_t value) {
    sandpile[pair_to_str(coord)] = value;

    if (value >= 4) {
        queue.push(coord);
    }

    max_x = std::max(max_x, coord.first);
    min_x = std::min(min_x, coord.first);

    max_y = std::max(max_y, coord.second);
    min_y = std::min(min_y, coord.second);
}

void Sandpile::printToBMP(bool freqZero) {
    int widthBMP = max_x - min_x + 1;
    int heightBMP = max_y - min_y + 1;
    Image Image(widthBMP, heightBMP);
    const Color colors[] = {Color::white(), Color::green(), Color::magenta(), Color::yellow(), Color::black()};

    for (int x = min_x; x <= max_x; x++){
        for (int y = min_y; y <= max_y; y++){
            if (sandpile[pair_to_str({x, y})] < 4 or (sandpile.find(pair_to_str({x, y})) == sandpile.end())) {
                Image.SetColor(colors[sandpile[pair_to_str({x, y})]], x - min_x, y - min_y);
            } else {
                Image.SetColor(colors[4], x - min_x, y - min_y);
            }
        }
    }

    std::string filename = out_path + "sandpile";
    if (!freqZero) {
        filename += '_' + std::to_string(name_num);
        name_num++;
    }
    filename += ".bmp";

    Image.Export(filename);
}

void Sandpile::spilling() {
    size_t queue_old_size = queue.size();
    uint64_t iter = 0;
    while (!queue.empty()) {
        if (iter == max_iter) {
            break;
        }

        int x = queue.front().first;
        int y = queue.front().second;
        queue.pop();
        if (sandpile[pair_to_str({x, y})] < 4) {
            continue;
        }
        std::pair<int, int> up = {x, y + 1};
        std::pair<int, int> down = {x, y - 1};
        std::pair<int, int> left = {x - 1, y};
        std::pair<int, int> right = {x + 1, y};

        max_x = std::max(max_x, x + 1);
        min_x = std::min(min_x, x - 1);

        max_y = std::max(max_y, y + 1);
        min_y = std::min(min_y, y - 1);

        std::pair<int, int> coords[] = {up, down, left, right};

        for (auto coord : coords) {
            sandpile[pair_to_str(coord)]++;
            sandpile[pair_to_str({x, y})]--;

            if (sandpile[pair_to_str(coord)] >= 4) {
                queue.push(coord);
            }
        }

        if (sandpile[pair_to_str({x, y})] >= 4) {
            queue.push({x, y});
        }

        queue_old_size--;
        if (queue_old_size == 0) {
            queue_old_size = queue.size();
            iter++;
            if (freq != 0 and iter % freq == 0) {
                printToBMP(freq == 0);
            }
        }
    }
    printToBMP(freq == 0);
}

void Sandpile::setFromTSV(std::string &path_file) {
    std::ifstream file(path_file);
    if (!file.is_open()){
        throw std::invalid_argument("File can't be opened.");
    }

    if (out_path.back() != '/') {
        out_path += '/';
    }

    max_x = length;
    max_y = width;

    std::string str;
    while (getline(file, str)) {
        int x = std::stoi(str.substr(0, str.find('\t')));
        int y = std::stoi(str.substr(str.find('\t') + 1, str.rfind('\t')));
        int64_t value = std::stoll(str.substr(str.rfind('\t'), str.size()));
        setGrains({x, y}, value);
    }
}
