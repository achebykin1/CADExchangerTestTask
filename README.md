# CADExchangerTestTask
Test task for application to the job

Тестовое задание я выполнял с помощью Ubuntu 22.04, код написан в VSCode с использованием Cmake-a проект сторился с помощью: GCC 11.4.0 x86_64-linux-gnu.
#
Для постройки проекта нужно написать:
```sh
sh build.sh
```
После создаться директория ```./build``` в которой будет 
исполняемый файл ```GeometricShapes``` который выполняет поставленное задание

# _Пояснения к решению задания_
Так как при поворотах геометрических фигур имеет важность порядок поворота, то стоит сказать что мой порядок
- Сначало поворот относительно оси Oz
- Потом относительно оси Oy
- И после относительно оси Ox
#### Так же возможно лишние
В пукте задания 4, 5, 6 требовалось найти только окружности и отсортировать их пор радиусу после чего найти сумму радиусов.
Нигде не просилось их вывести на экран. Но в ```main``` в ```main.cpp``` есть несколько закомментированных строк на их вывод.
В случае надобности и наглядного рассмотрения их можно раскомментировать.
