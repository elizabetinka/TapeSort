# Сортировка данных на магнитной ленте
Устройство хранения данных типа лента (Tape) предназначено для последовательной записи и чтения данных. Считывающая/записывающая магнитная головка неподвижна во время чтения и записи, а лента имеет возможность двигаться в обоих направлениях. Запись и чтение информации возможны в ячейку ленты, на которой в данный момент находится магнитная головка. Перемещения ленты – затратная по времени операция – лента не предназначена для произвольного доступа.
Имеется входная лента длины N (где N – велико), содержащая элементы типа integer (232). Имеется выходная лента такой же длины. Необходимо записать в выходную ленту отсортированные по возрастанию элементы с входной ленты. Есть ограничение по использованию оперативной памяти – не более M байт (M может быть < N, т.е. загрузить все данные с ленты в оперативную память не получится). Для реализации алгоритма можно использовать разумное количество временных лент, т.е. лент, на которых можно хранить какую-то временную информацию, необходимую в процессе работы алгоритма.
Необходимо создать проект С++, компилируемый в консольное приложение, которое реализует алгоритм сортировки данных с входной ленты на выходную. Необходимо сделать следующее:

- Определить интерфейс для работы с устройством типа лента.
- Написать класс, реализующий этот интерфейс и эмулирующий работу с лентой посредством обычного файла. Должно быть возможно сконфигурировать (без
перекомпиляции – например, через внешний конфигурационный файл, который будет прочитан на старте приложения) задержки по записи/чтению элемента с ленты, перемотки ленты, и сдвига ленты на одну позицию.
- Файлы временных лент можно сохранять в директорию tmp.
- Написать класс, реализующий алгоритм сортировки данных с входной ленты на выходную.
- Консольное приложение должно принимать на вход имя входного и выходного файлов и
производить сортировку.
- Желательно написать юнит-тесты.