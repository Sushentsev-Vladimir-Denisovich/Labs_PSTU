#include "Конвертер валют.h"
#include <Windows.h>
#include <iostream>

using namespace Final;

int main()
{
    setlocale(LC_ALL, "rus");

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyForm);
    return 0;
}
//Перевод между долларом, евро и рублями
//Отмена последней операции
//Сброс результата



//Изменить название самого окна                                                 +
//Брать информацию о курсе валют из интернета
//Увеличить шрифт в окне ввода и в окне вывода                                  +
//Использовать ToolTipы                                                         +
//Сделать 2-3 знака после запятой в выводе                                      + (3 знака)