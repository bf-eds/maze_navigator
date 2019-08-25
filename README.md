## maze_navigator
Тестовое задание для ЦРТ. Навигация по лабиринту.

### Сборка
*MSVC*

```cmake.exe  <path_to_CMakeLists.txt> -G "Visual Studio 14 2015" (или другая необходимая версия компилятора)```

```cmake.exe --build <path_to_build_dir>```

*GCC*

```cmake  <path_to_CMakeLists.txt>```

```make```

### Демо-приложение

*maze_demo*

Лабиринт представляется в виде набора секций на двумерной плоскости.
Положение секции определяется двумя целочисленными координатами, например секция (0, 2).
Если две секции расположены рядом по горизонтали или вертикали (не по диагонали), то между ними есть проход.

    Например:
       набор секций с координатами (0, 0), (0, 1), (1, 0), (1, 1) задает квадратный лабиринт 2x2.
       набор секций с координатами (-1, 0), (0, 0), (1, 0), (0, 1), (0, -1) задает лабиринт из 5 секций в виде
       креста с центром в секции (0, 0).
Лабиринт может иметь произвольную форму, состоять из нескольких не связанных между собой частей.
Лабиринт загружается из файла, если файла нет, то в cerr выводится ошибка "failed to open <file>".
 
Маршрут в лабиринте задается последовательностью шагов.
Шагать можно только по 4 направлениям: вверх, вниз, вправо и влево.
Если в направлении шага есть переход в соседнюю секцию, то текущее положение меняется на нее.
Если в направлении шага перехода в соседнюю секцию нет, то шаг не имеет эффекта и текущее положение не меняется.
Например, для лабиринта из двух секций (0, 0) и (1, 0), стартовой точки (0, 0) и маршрута "вправо, вправо, вправо", только первый шаг будет иметь эффект (0, 0) -> (1, 0). Второй и третий шаг оставят текущее положение без изменений, поскольку секции (2, 0) не существует, и конечная точка маршрута останется (1, 0).
Строка с командами может состоять только из 4х символов - "u"(вверх), "d"(вниз), "l"(влево), "r"(вправо).
Например: "udllrru". Неизвестные команды игнорируются.

#### Как запустить:

maze_demo --board <board_file> --route <route_string> -x <x_coordinate> -y <y_coordinate>

Например: maze_demo --board board.txt --route "rruu" -x 0 -y 0

board.txt - файл со списком секций лабиринта, имеет вид (-1, 0), (0, 0), (1, 0), (0, 1), (0, -1) и т.д.

route_string - строка с маршрутом перемещения по лабиринту

x_coordinate и y_coordinate - координаты начальной точки маршрута

Программа выводит в консоль начальную и конечную точки машрута. 
