/**
 * Программа для работы с геометрическими фигурами.
 * Разработчик - Дубинин А. В. (http://dubinin.net)
 * 08.01.2017
 */

// Подключение файлов из стандартной библиотеки
#include <iostream>
#include <vector>

// Открытие пространства имен std
using namespace std;

// Объявление констант
const string BR           = "\n\n";
const string MSG_COUNT    = "Количество геометрических фигур в коллекции = ";
const string MSG_APP_EXIT = "\nДля выхода из программы нажмите любую клавишу";

/**
 * @interface IDeletable
 * Описывает поведения удаляемой сущности.
 */
class IDeletable
{
    public:
        /**
         * Виртуальный метод free() - освобождает ресурс
         * (динамическую память), занятый объектом.
         * @return void
         */
        virtual void free() = 0;
};

/**
 * @interface IContainer
 * Описывает контейнер для хранения фигур.
 */
class IContainer
{
    public:
        /**
         * Виртуальный метод getName() - возвращает название
         * геометрической фигуры.
         * @return string
         */
        virtual string getName() = 0;
};

/**
 * @interface IShapesCollection расширяет интерфейс IDeletable.
 * Описывает коллекцию геометрических фигур.
 */
class IShapesCollection: public IDeletable
{
    public:
        /**
         * Виртуальный метод add() - добавляет экземпляр
         * геометрической фигуры в коллекцию.
         * @param IContainer*
         * @return void
         */
        virtual void add(IContainer*) = 0;

        /**
         * Виртуальный метод displayShapesList() - выводит на экран названия
         * геометрических фигур в коллекции.
         * @return void
         */
        virtual void displayShapesList() = 0;

        /**
         * Виртуальный метод clearCollection() - очищает коллекцию:
         * освобождает ресурсы (динамическую память), занятые каждым
         * элементом коллекции.
         * @return void
         */
        virtual void clearCollection() = 0;

        /**
         * Виртуальный метод getCount() - возвращает количество
         * геометрических фигур в коллекции.
         * @return int
         */
        virtual int getCount() = 0;
};

/**
 * @class BaseShape реализует интерфейсы IContainer, IDeletable.
 * Базовый класс геометрической фигуры.
 */
class BaseShape: public IContainer, public IDeletable
{
    protected:
        string name;
    public:
        string getName()
        {
            return this->name;
        }
        void free()
        {
            delete this;
            return;
        }
};

/**
 * @class Line расширяет базовый класс BaseShape.
 * Класс прямой.
 */
class Line: public BaseShape
{
    public:
        Line()
        {
            this->name = "прямая";
        }
};

/**
 * @class PolygonalChain расширяет базовый класс BaseShape.
 * Класс ломаной.
 */
class PolygonalChain: public BaseShape
{
    public:
        PolygonalChain()
        {
            this->name = "ломаная";
        }
};

/**
 * @class Rectangle расширяет базовый класс BaseShape.
 * Класс прямоугольника.
 */
class Rectangle: public BaseShape
{
    public:
        Rectangle()
        {
            this->name = "прямоугольник";
        }
};

/**
 * @class Ellipse расширяет базовый класс BaseShape.
 * Класс эллипса.
 */
class Ellipse: public BaseShape
{
    public:
        Ellipse()
        {
            this->name = "эллипс";
        }
};

/**
 * @class Polygon расширяет базовый класс BaseShape.
 * Класс многоугольника.
 */
class Polygon: public BaseShape
{
    public:
        Polygon()
        {
            this->name = "многоугольник";
        }
};

/**
 * @class ShapesCollection реализует интерфейс IShapesCollection.
 * Класс коллекции геометрических фигур.
 */
class ShapesCollection: public IShapesCollection
{
    private:
        vector <IContainer*> shapes;
    public:
        void add(IContainer* shape)
        {
            shapes.push_back(shape);
            return;
        }
        void displayShapesList()
        {
            vector <IContainer*>::iterator item = shapes.begin();
            while (item != shapes.end()) {
                IContainer* shape = *item++;
                cout << shape->getName() << endl;
            }
            return;
        }
        void clearCollection()
        {
            shapes.clear();
            return;
        }
        int getCount()
        {
            return shapes.size();
        }
        void free()
        {
            delete this;
            return;
        }
};

/**
 * @class Application
 */
class Application
{
    public:
        /**
         * Статический метод run() - запускает приложение.
         * @return void
         */
        static void run()
        {
            /**
             * Объявление и инициализация переменной collection
             * типа IShapesCollection - коллекция геометрических фигур
             */
            IShapesCollection* collection = new ShapesCollection();

            // Добавление объектов геометрических фигур в коллекцию
            collection->add(new Line());
            collection->add(new PolygonalChain());
            collection->add(new Rectangle());
            collection->add(new Ellipse());
            collection->add(new Polygon());

            // Вывод количества геометрических фигур в коллекции
            cout << MSG_COUNT << collection->getCount() << BR;

            // Вывод на экран названий геометрических фигур в коллекции
            collection->displayShapesList();

            // Очистка коллекции
            collection->clearCollection();

            // Удаление коллекции
            collection->free();

            // Вывод на экран диалога выхода из программы
            cout << MSG_APP_EXIT;
            cin.get();
            return;
        }
};

int main()
{
    // Запуск приложения
    Application::run();
}
