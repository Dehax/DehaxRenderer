#include "MainWindow.h"
#include <QApplication>

// +TODO: 1. Наличие графической БД: возможность сохранения сцены с объектами в файле.
// +TODO: 2. Читабельность БД: файл сцены должен содержать данные модели в текстовом виде.
// +TODO: 3. Возможность работы с несколькими объектами: обеспечить добавление на экран допустимого количества объектов, а также работу со всеми объектами (перемещение, панорамирование) и с одним выбранным объектом.
// +TODO: 4. Обеспечить редактирование и параметризацию объектов: возможность изменения параметров любого объекта, а также его масштабирование, перенос, поворот и удаление.
// +TODO: 5. Обеспечить центральное и параллельное проецирование: возможность переключения с одного вида проецирования на другой.
// +TODO: 6. Задание всех параметров аппарата проецирования: обеспечить наличие "камеры", задаваемой необходимыми параметрами (как минимум - точка зрения и точка цели), также возможность её перемещения вокруг объекта и поворота вокруг своей оси.
// +TODO: 7. Удаление невидимых частей объектов: обеспечить визуализацию объекта без его невидимых частей с помощью алгоритма удаления невидимых линий.
// +TODO: 8. Разработать интуитивно понятный пользовательский интерфейс: программный продукт должен обеспечивать пользователю максимально понятную и простую работу в редакторе за счёт оформления интерфейса, контекстных подсказок, горячих клавиш и предупреждений.
// +TODO: 9. При разработке графического редактора не использовать стандартные графические библиотеки (OpenGL, DirectX и т.д.).

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
