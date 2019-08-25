//
// Created by Eroshenkov Dmitrii on 25.08.2019.
//

#pragma once

#include "maze_export.h"
#include <memory>

/**
 * @brief Класс навигации по лабиринуту.
 *
 * Лабиринт представляется в виде набора секций на двумерной плоскости.
 * Положение секции определяется двумя целочисленными координатами, например секция (0, 2).
 * Если две секции расположены рядом по горизонтали или вертикали (не по диагонали), то между ними есть проход.
 * Например:
 *      * набор секций с координатами (0, 0), (0, 1), (1, 0), (1, 1) задает квадратный лабиринт 2x2.
 *      * набор секций с координатами (-1, 0), (0, 0), (1, 0), (0, 1), (0, -1) задает лабиринт из 5 секций в виде
 *      креста с центром в секции (0, 0).
 * Лабиринт может иметь произвольную форму, состоять из нескольких не связанных между собой частей.
 * Лабиринт загружается из файла, если файла нет, то в cerr выводится ошибка "failed to open <file>".
 *
 * Маршрут в лабиринте задается последовательностью шагов.
 * Шагать можно только по 4 направлениям: вверх, вниз, вправо и влево.
 * Если в направлении шага есть переход в соседнюю секцию, то текущее положение меняется на нее.
 * Если в направлении шага перехода в соседнюю секцию нет, то шаг не имеет эффекта и текущее положение не меняется.
 * Например, для лабиринта из двух секций (0, 0) и (1, 0), стартовой точки (0, 0) и маршрута "вправо, вправо, вправо", только первый шаг будет иметь эффект (0, 0) -> (1, 0). Второй и третий шаг оставят текущее положение без изменений, поскольку секции (2, 0) не существует, и конечная точка маршрута останется (1, 0).
 * Строка с командами может состоять только из 4х символов - "u"(вверх), "d"(вниз), "l"(влево), "r"(вправо).
 * Например: "udllrru". Неизвестные команды игнорируются.
 */

namespace maze
{
    struct Point
    {
        int x_;
        int y_;
    };

    class MAZE_EXPORT MazeNavigator
    {
    public:
        /**
         * Загрузка лабиринта.
         * @param path Путь к файлу с секциями лабиринта.
         */
        explicit MazeNavigator(const char *path);

        ~MazeNavigator();
        MazeNavigator(MazeNavigator &&) noexcept;
        MazeNavigator &operator=(MazeNavigator &&) noexcept;
        MazeNavigator &operator=(const MazeNavigator &) = delete;

        /**
         * Навигация по лабиринту.
         * @param start_x Координата X начала маршрута.
         * @param start_y Координата Y начала маршрута.
         * @param commands Список команд.
         * @return Конечная точка маршрута.
         */
        Point Navigate(int start_x, int start_y, const char *commands) const;

    private:
        class Maze;
        std::unique_ptr<Maze> maze_;
    };
}