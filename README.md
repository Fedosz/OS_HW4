# Отчёт по ИДЗ №4 ОС, вариант 3 - Жуков Ф.С., БПИ218

## Программа выполненна на 7 баллов

### Условие задачи
Задача о Винни-Пухе – 2 или неправильные пчелы. N пчел
живет в улье, каждая пчела может собирать мед и сторожить улей (N > 3). Пчела не покинет улей, если кроме нее в нем нет других пчел. Каждая пчела приносит за раз одну порцию меда. Всего в улей может войти тридцать порций меда. Вини-Пух спит пока меда в улье меньше половины, но как только его становится достаточно, он просыпается и пытается достать весь мед из улья. Если в улье находится менее чем три пчелы, Вини-Пух забирает мед, убегает, съедает мед и снова засыпает. Если в улье пчел больше, они кусают Вини-Пуха, он убегает, лечит укус, и снова бежит за медом. Создать приложение, моделирующее поведение пчел и медведя. Осуществить балансировку, обеспечивающую циклическое освобождение улья от меда. Медведя и улей с пчелами представить в виде отдельных клиентов. Сервер обрабатывает поступающие от них сообщения и передает их клиентам в соответствии с установленными выше правилами.

Пример запуска программы:
./server 4
./client 4

Первым запускается server и открывет свой сокет для прослушивания. Сразу после запускается клиент, в котором находится многопоточное приложение, которое начинает общение с сервером, где каждый поток запускает свое сообщение в очередь сообщений и ждет ответа. 

Каждый процесс отправляет сообщение в формате char data[2], где 
data[0] - 1, если пчела, 2 если Винни
data[1] - 1, если пчела хочет улететь, 2, если пчела прилетает с медом

Сервер хранит в себе всю нужную информацию в виде char data[5], где
data[0] - кол-во меда / 10
data[1] - кол-во меда % 10
data[2] - кол-во пчел в улье
data[3] - кол-во укусов
data[4] - флаг для остановки программы

В обратную сторону идет сообщение в виде char answer[2], где в зависимости от получателя будет своя информация:
Если получатель Винни, то 
answer[0] - 2, если можно забирать мед, 1 если нельзя
answer[1] - 2, если в улье меньше 3 пчел, 1 если >=
Если получатель пчела, то
answer[0] - 2, если можно улетать, 1, если нельзя
answer[1] - 2, если программа завершается

Программа завершается при достижении 3 укусов.

### Пример работы программы
[Скриншоты с консольным выводом](https://github.com/Fedosz/OS_HW4/blob/main/program%20example.png)

## Выполненные критерии на 7 баллов
Был добавлен [код логгера](https://github.com/Fedosz/OS_HW4/blob/main/7/logger.c)
