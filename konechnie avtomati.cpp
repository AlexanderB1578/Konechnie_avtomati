#include <iostream>
#include <string>

// Возможные состояния автомата
enum State {
    IDLE,          // Ожидание (ничего не происходит)
    DIALING,       // Набор номера
    CONNECTING,    // Установка соединения
    IN_CALL,       // Разговор
    ENDED,         // Завершено
    ERROR          // Ошибка (занято / нет сети)
};

// Возможные события
enum Event {
    START_CALL,    // Начать звонок
    NUMBER_ENTERED,// Номер введён
    CONNECTED,     // Соединение установлено
    HANG_UP,       // Положили трубку
    FAIL           // Ошибка соединения
};

// Функция обработки переходов
State handleEvent(State current, Event event) 
{
    switch (current) 
    {

    case IDLE:
        if (event == START_CALL) 
        {
            std::cout << "Начинаем набор номера...\n";
            return DIALING;
        }
        break;

    case DIALING:
        if (event == NUMBER_ENTERED) 
        {
            std::cout << "Номер введён, соединяем...\n";
            return CONNECTING;
        }
        break;

    case CONNECTING:
        if (event == CONNECTED) 
        {
            std::cout << "Соединение установлено!\n";
            return IN_CALL;
        }
        if (event == FAIL) 
        {
            std::cout << "Ошибка соединения (занято или нет сети)\n";
            return ERROR;
        }
        break;

    case IN_CALL:
        if (event == HANG_UP) 
        {
            std::cout << "Звонок завершён.\n";
            return ENDED;
        }
        break;

    case ERROR:
        if (event == HANG_UP) 
        {
            std::cout << "Возврат в режим ожидания.\n";
            return IDLE;
        }
        break;

    case ENDED:
        if (event == START_CALL) 
        {
            std::cout << "Новый звонок...\n";
            return DIALING;
        }
        break;
    }

    // Если переход не определён — остаёмся в том же состоянии
    return current;
}

int main() 
{
    setlocale(LC_ALL, "russian");
    State state = IDLE;

    // Симуляция работы автомата
    state = handleEvent(state, START_CALL);
    state = handleEvent(state, NUMBER_ENTERED);
    state = handleEvent(state, CONNECTED);
    state = handleEvent(state, HANG_UP);

    return 0;
}