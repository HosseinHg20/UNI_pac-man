#ifndef SCORE_HPP
#define SCORE_HPP

#include <fstream>

namespace memory
{
    void saveHighestScore(int s)
    {
        std::ofstream file("DB/the_highest_score.dat", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
        if (!file.is_open())
            throw 1;
        file.write((char*)&s, sizeof(int));
        file.close();
    }
    int getHighestScore()
    {
        int s;
        std::ifstream file("DB/the_highest_score.dat", std::ios_base::in |  std::ios_base::binary);
        file.read((char*)&s, sizeof(int));
        file.close();
        return s;
    }
} // namespace memory

#endif // SCORE_HPP