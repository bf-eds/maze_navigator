#include "maze_navigator.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

namespace maze
{
    using namespace std;

    struct PointHasher
    {
        size_t operator()(const Point &point) const
        {
            const hash<int> int_hasher;
            return int_hasher(point.x_) ^ int_hasher(point.y_);
        }
    };

    class MazeNavigator::Maze
    {
    public:
        enum MoveDirection
        {
            up, down, left, right,
        };

        explicit Maze(const std::string &path);

        /**
         * Навигация по лабиринту.
         * @param start Точка начала маршрута.
         * @param commands Список команд.
         * @return Конечная точка маршрута.
         */
        Point Navigate(Point start, const std::string &commands) const;
    private:
        /**
         * Сделать шаг по маршруту.
         * @param start Начальная точка для шага.
         * @param direction Направление шага.
         * @return Конечная точка.
         */
        const Point &MakeMove(const Point &start, MoveDirection direction) const;
        unordered_set<Point, PointHasher> sections_;
    };

    MazeNavigator::MazeNavigator(const char *path) : maze_{make_unique<Maze>(path)}
    {
    }

    Point MazeNavigator::Navigate(int start_x, int start_y, const char *commands) const
    {
        return maze_->Navigate({start_x, start_y}, commands);
    }

    MazeNavigator &MazeNavigator::operator=(MazeNavigator &&) noexcept = default;

    MazeNavigator::MazeNavigator(MazeNavigator &&) noexcept = default;

    MazeNavigator::~MazeNavigator() = default;


    bool operator==(const Point &lhs, const Point &rhs)
    {
        return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
    }

    MazeNavigator::Maze::Maze(const std::string &path)
    {
        ifstream ifile(path, ios::in);

        if (ifile.is_open())
        {
            // Координаты секций записаны в виде (-1, 0), (113, 54) и т.д.
            for (string line; getline(ifile, line, ')');)
            {
                line.erase(0, line.find('(') + 1);
                auto delim = line.find(',');

                istringstream iss_x(line.substr(0, delim));
                istringstream iss_y(line.substr(delim + 1));

                int x = 0;
                int y = 0;
                iss_x >> x;
                iss_y >> y;

                if (iss_x.eof() && iss_y.eof())
                {
                    sections_.insert({x, y});
                }
            }
        }
        else
        {
            cerr << "failed to open " << path << endl;
        }
    }

    Point MazeNavigator::Maze::Navigate(const Point start, const std::string &commands) const
    {
        Point current = start;

        for (auto command : commands)
        {
            MoveDirection direction;
            switch (command)
            {
                case 'u':
                    direction = up;
                    break;
                case 'd':
                    direction = down;
                    break;
                case 'r':
                    direction = right;
                    break;
                case 'l':
                    direction = left;
                    break;
                default:
                    continue;
                    break;
            }

            current = MakeMove(current, direction);
        }

        return current;
    }

    const Point &MazeNavigator::Maze::MakeMove(const Point &start, Maze::MoveDirection direction) const
    {
        Point end = start;

        switch (direction)
        {
            case MoveDirection::up:
                ++end.y_;
                break;
            case MoveDirection::down:
                --end.y_;
                break;
            case MoveDirection::right:
                ++end.x_;
                break;
            case MoveDirection::left:
                --end.x_;
                break;
            default:
                return start;
        }

        auto next_point = sections_.find(end);

        if (next_point == sections_.end())
        {
            return start;
        }
        else
        {
            return *next_point;
        }
    }
}
