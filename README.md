Работа по курсу "Компьютерная обработка сигналов и изображений".

Одномерные сигналы для определённости имеют 1024 уровня квантования и хранятся в файлах формата csv. 
Для показа графиков одномерных сигналов используется gnuplot.
В практических работах используются полутоновые (grayscale, в градациях серого) изображения с глубиной цвета 8 бит на пиксель. 
Чтение и запись изображений осуществялется в PNG формате с помощью библиотеки pnglib.

Задание.

Написать программу:

a)	выполняющую свёртку одномерного сигнала во временной области, ядро свертки задаётся пользователем; 

b)	выполняющую свёртку изображения в пространственной области, ядро свертки задаётся пользователем;

c)	исследовать результаты работы линейных ФНЧ и ФВЧ для сигналов и изображений.