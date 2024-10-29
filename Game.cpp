#include "Game.h"

#include <algorithm>

#include "JUtils.h"

struct Game {
    std::vector<std::vector<int> > board;
    bool nextCross;
    int size;

    int crosses;
    int circles;

    enum Mark {
        Empty,
        Cross,
        Circle,
        WonCross,
        WonCircle
    };

    void update(int const &xp, int const &yp) {
        if (xp < size && yp < size) {
            if (board[yp][xp] == Empty) {
                if (nextCross) {
                    nextCross = false;
                    board[yp][xp] = Cross;
                    crosses++;
                } else {
                    nextCross = true;
                    board[yp][xp] = Circle;
                    circles++;
                }
            }
        }
    }

    void check() {
        if (crosses >= 5) {
            if (wonBy(Cross)) {
                board[0][0] = WonCross;
            }
        }

        if (circles >= 5) {
            if (wonBy(Circle)) {
                board[0][0] = WonCircle;
            }
        }
    }

private:
    template<typename T>
        static std::vector<std::vector<T> > flip45(std::vector<std::vector<T> > const &vec) {
        auto v = std::vector<std::vector<T> >();

        for (int i = 0; i < (vec.size() * 2); i++) {
            v.emplace_back();
        }

        for (int i = 0; i < v.size(); i++) {
            int size = i;
            bool reverse = false;

            if (size >= vec.size()) {
                reverse = true;
                size = vec.size() - (i - vec.size());
            }

            if (!reverse) {
                for (int x = 0, y = size; y >= 0; x++, y--) {
                    v[i].push_back(vec[x][y]);
                }
            } else {
                for (int x = vec.size() - size, y = vec.size() - 1; x < vec.size(); x++, y--) {
                    v[i].push_back(vec[x][y]);
                }
            }
        }

        return v;
    }

    template<typename T>
    static std::vector<std::vector<T> > flip(std::vector<std::vector<T> > const &vec) {
        auto v = std::vector<std::vector<T> >();

        for (int i = 0; i < vec.size(); i++) {
            v.emplace_back();
        }

        for (int i = 0; i < vec.size(); i++) {
            for (auto &r: vec) {
                v[i].push_back(r[i]);
            }
        }

        return v;
    }

    static bool checkRow(int const &val, std::vector<int> const &row) {
        int c = 0;

        int i = 0;

        if (row.size() < 5) {
            return false;
        }

        if (row.size() == 5) {
            return true;
        }

        for (auto const &v: row) {
            if (v == val) {
                c++;
                if (c == 5) {
                    return true;
                }
            } else if (v != val) {
                c = 0;
            }

            if (row.size() - i < 5 && c == 0) {
                return false;
            }

            i++;
        }

        return false;
    }

    bool checkRows(int const &val) {
        return std::ranges::any_of(board, [val](std::vector<int> const &row) {
            if (std::ranges::count(row, val) >= 5) {
                if (checkRow(val, row)) {
                    return true;
                }
            }
            return false;
        }, {});
    }

    static bool checkRows(int const &val, std::vector<std::vector<int> > const &boardF) {
        return std::ranges::any_of(boardF, [val](std::vector<int> const &row) {
            if (std::ranges::count(row, val) >= 5) {
                if (checkRow(val, row)) {
                    return true;
                }
            }
            return false;
        }, {});
    }

    bool checkCol(int const &val) {
        return checkRows(val, flip(board));
    }

    template <typename T>
    static std::vector<std::vector<T>> reverse2d(std::vector<std::vector<T>> const & vec) {
        auto v = std::vector<std::vector<T>>();

        for (auto const& row : vec) {
            v.emplace_back();
            v.push_back(std::ranges::reverse_copy(row,v[v.size()-1]));
        }

        return v;
    }

    bool checkDiag(int const& val) {
        if (checkRows(val,flip45(board))) {
            return true;
        }

        if (checkRows(val,flip45(flip(board)))) {
            return true;
        }

        return false;
    }

    bool wonBy(int const &val) {
        if (checkRows(val)) {
            return true;
        }

        if (checkCol(val)) {
            return true;
        }

        if (checkDiag(val)) {
            return true;
        }

        return false;
    }
};

static Game game;


JNIEXPORT void JNICALL Java_Game_initialize
(JNIEnv *, jobject, jint size) {
    game = Game();
    game.size = size;
    game.nextCross = true;
    game.board = std::vector<std::vector<int> >();

    int row = 0;
    int i = 0;

    while (row < static_cast<int>(size)) {
        game.board.emplace_back();
        i = 0;
        while (i < static_cast<int>(size)) {
            game.board[row].push_back(Game::Mark::Empty);
            i++;
        }
        row++;
    }
}

JNIEXPORT jobjectArray JNICALL Java_Game_fetchInternal
(JNIEnv *env, jobject, jint const jxp, jint const jyp) {
    if (jxp != -1 && jyp != -1) {
        game.update(jxp, jyp);
        game.check();
    }

    return JUtils::to_int2d_jobject_array(game.board, env);
}