//
// Created by Eroshenkov Dmitrii on 25.08.2019.
//

#include "maze_navigator.h"
#include <iostream>
#include <algorithm>

static void showUsage()
{
    std::cout << "Usage: maze_demo --board <board_file> --route <route_string> "
              << "-x <x_coordinate> -y <y_coordinate>\n"
              << R"foo(For example: maze_demo --board board.txt --route "rruu" -x 0 -y 0)foo" << std::endl;
}

char *getCmdOption(char **begin, char **end, const std::string &option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}

int main(int argc, char **argv)
{
    if (argc < 9)
    {
        showUsage();
        return 0;
    }

    char *filename = getCmdOption(argv, argv + argc, "--board");
    char *commands = getCmdOption(argv, argv + argc, "--route");
    char *x_coordinate = getCmdOption(argv, argv + argc, "-x");
    char *y_coordinate = getCmdOption(argv, argv + argc, "-y");

    if (!(filename && commands && x_coordinate && y_coordinate))
    {
        showUsage();
        return 0;
    }

    int x = 0;
    int y = 0;

    if (sscanf_s(x_coordinate, "%d", &x) != 1)
    {
        std::cerr << "Wrong format of x coordinate." << std::endl;
        showUsage();
        return 0;
    }

    if (sscanf_s(y_coordinate, "%d", &y) != 1)
    {
        std::cerr << "Wrong format of y coordinate." << std::endl;
        showUsage();
        return 0;
    }

    maze::MazeNavigator mazeNavigator(filename);
    auto end = mazeNavigator.Navigate(x, y, commands);

    std::cout << "Start [" << x << ", " << y << "] -> End [" << end.x_ << ", " << end.y_ << "]"
         << std::endl;

    return 0;
}