#include <iostream>
#include <array>
#include <queue>

template<unsigned boardSize = 8>
class minMoves {
    using position = std::pair<int, int>;
    using positionAndSteps = std::pair<position, int>;
    using board = std::array<std::array<bool, boardSize>, boardSize>;

    board playground;

    void cleanPlayground() {
        for (auto &col : playground)
            for (auto &pos : col)
                pos = false;
    }

    static bool equalPositions(const position &fst, const position &snd) {
        return fst.first == snd.first && fst.second == snd.second;
    }

    static bool isValidPos(const position &p) {
        return p.first >= 0 && p.second >= 0 && p.first < boardSize && p.second < boardSize;
    }

    void mark(const position &toMark) {
        playground[toMark.first][toMark.second] = true;
    }

    bool isMarked(const position &pos) const {
        return playground[pos.first][pos.second];
    }

    void pushAndMarkIfValid(std::queue<positionAndSteps> &q, const position &toPush, int steps) {
        if (isValidPos(toPush) && !isMarked(toPush)) {
            q.push({toPush, steps});
            mark(toPush);
        }
    }

    int process(const position &startPos, const position &endPos) {
        std::queue<positionAndSteps> q;

        q.push({startPos, 0});

        while (!q.empty()) {
            positionAndSteps currentPosition = q.front();

            q.pop();

            if (equalPositions(currentPosition.first, endPos))
                return currentPosition.second;

            int x = currentPosition.first.first;
            int y = currentPosition.first.second;
            int moves = currentPosition.second + 1;

            pushAndMarkIfValid(q, {x + 1, y + 2}, moves);
            pushAndMarkIfValid(q, {x - 1, y - 2}, moves);
            pushAndMarkIfValid(q, {x + 1, y - 2}, moves);
            pushAndMarkIfValid(q, {x - 1, y + 2}, moves);
            pushAndMarkIfValid(q, {x + 2, y - 1}, moves);
            pushAndMarkIfValid(q, {x + 2, y + 1}, moves);
            pushAndMarkIfValid(q, {x - 2, y + 1}, moves);
            pushAndMarkIfValid(q, {x - 2, y - 1}, moves);
        }
        return -1;
    }

public:
    minMoves() { cleanPlayground(); }

    int getMinMoves(const position &start, const position &end) {
        cleanPlayground();

        return process(start, end);
    }
};

int main() {
    minMoves m;

    std::cout << m.getMinMoves({0, 0}, {5, 3}) << std::endl;

    minMoves<12> ms;

    std::cout << ms.getMinMoves({0, 0}, {11, 11}) << std::endl;

    minMoves<2> mt;

    std::cout << mt.getMinMoves({0, 0}, {12, 212});
}