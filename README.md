# GradientDescent
Это программа позволяет увидеть работу подбора корней.
Коэффиценты подбираются под уравнение вида ksin(bx). 
Синим наверху нарисован оригинальный график с коэффицентами k = 5, b = 7. 
Красным - отгаданный программой график.
Зеленым - график построенный по выбранным вами коэффицентам.

# Что за график внизу?
Внизу средне квадратичное отклонение функции с коэффицентами как у точки, тоесть 
K - ось абсцис, B - ось ординат.
Цвет означает отклонение: синее - минимальное, красное - максимальное.

# Что такое средне квадратичное?
Средне квадратичное - сумма квадратов разности значения оригинальной фукнции и функции с коэффицентами в точке.

# Как взаимодействовать с программой?
Левая кнопка мыши по нижнему графику: выбор коэффициентов по которым будет зелёным цветом построен график наверху.
Правая кнопка мыши по нижнему графику: Градиентный спуск из точки к оптимальным коэффицентам.

# Пример:
![image](https://user-images.githubusercontent.com/64206443/230208710-d25bd35a-8feb-42f2-b658-77b6587d9cb5.png)

# Технические особенности
Работает на [собственной графической библиотеке](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP)
В данной программе присутствует 4 потока
1) Главный графический поток для обработки сообщений окна
2) Поток по построению верхнего графика
3) Поток, который считает точки среднеквадратичного отклоннения
4) Поток градиентного спуска


------------------------------------------------------
# Установка программы
Чтобы запустить программу необходимо скачать её собранную версию из вкладки релизы(https://github.com/quqveik1/GRAPHICAPP/releases/tag/v0.2.3.0),
при запуске надо игнорировать сообщения антивирусов о том, что в файле содержится вирус.

В таком окне следует нажать "Подробнее" и будет доступно выбрать "Выполнить в любом случае".


<img src="https://user-images.githubusercontent.com/64206443/182945554-ed4d18c6-a25d-4d0d-a331-e268643b3031.png" width="400">

