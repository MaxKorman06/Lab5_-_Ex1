#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cctype>
#include <sstream>

using namespace std;

const string fileName{ "input.txt" };

int numberOfWords();//Підраховує кількість слів в файлі
void numberOfLett();//Підраховує кількість букв в файлі
void dobleOfLett(string temp);//Виключає з виводу подвоєні літери
void uniqLetter();// Виводить унікальні слова + Виключає з виводу подвоєні літери

int main()
{
    SetConsoleCP(1251); //Робимо можливим вивід кирилиці на екран
    SetConsoleOutputCP(1251);

    uniqLetter();
    numberOfLett();//Підраховує кількість букв в файлі
}

int numberOfWords()
{
    // Тут ми підрахуємо кількість слів у файлі
    unsigned int counter = 0;

    // Відкрийте файл. Файл не повинен бути вже відкритим
    ifstream input(fileName);

    // Перевірте, чи можемо ми відкрити файл
    if (input.is_open())
    {

        // Просто прочитайте всі слова та збільште counter
        string temp;
        while (input >> temp)
        {
            ++counter;
        }
    }
    else
    {

        cerr << "\nCould not open file '" << fileName << '\n';
    }
    return counter;
}
void numberOfLett()
{
    int let = 0;
    ifstream input(fileName);
    ofstream output;//Папка виводу
    output.open("output.txt");//Відкриваємо папку виводу

    if (!input.is_open() && !output.is_open()) // перевыряємо чи ці папки взагалі відкрилися
    {
        cout << "error_1\n";
    }
    else
    {
        char ch;
        while (input.get(ch))// зчитуєм посимвольно увесь файл
        {
            if (ch == '\n' || ch == ' ')// Рахуємо символ за літеру якщо він не пробіл або \n
            {
                let--;
            }
            let++;
            output << ch;
        }
    }

    input.close();// закриваємо папку вводу
    output.close();// закриваємо папку виводу
    cout << "Кількість використаних символів: " << let << '\n';
}
void dobleOfLett(string temp)
{

    string vowels{ "aeiou" };// голосні
    string result;// Строка слів з подвоєними літерами
    for (istringstream iss{ move(temp) }; iss >> temp;)// розбиваєм на слова
    {
        for (string::size_type idx{ 1 }; idx < temp.size(); ++idx) //string::size_type вміщає любий обєм числа
            if (tolower(temp[idx]) == tolower(temp[idx - 1]) &&   // Дві сосідні букви онинікові і приголосні? // tolower перетворює великі літери в маленькі
                vowels.find(temp[idx]) == string::npos) //find в нашому випадку шукає подвоєні літери + find видає npos якщо нічого не знаходить
            {
                result += temp + ' ';// додаєм словов result
                break;
            }
    }
    //cout << result;
    if ((temp + ' ') != result)
    {
        cout << temp << ' ';
    }
}
void uniqLetter()
{
    int size = numberOfWords();// Отримати кількість слів у вихідному файлі
    string* words = new string[size + 1];// Виділіть динамічний масив string. size – це кількість слів у файлі
    ifstream input(fileName);// Відкрийте вихідний файл
    if (input.is_open())// Перевірте, чи можна його відкрити
    {
        string temp; // Спочатку ми прочитаємо тимчасову змінну
        int wordCounter = 0; // Її ми підрахуємо кількість унікальних слів 
        cout << "Рядок без слів з подвоєними літерами: ";
        while (input >> temp)// Прочитайте всі слова у файлі
        {
            bool wordIsAlreadyPresent = false;// Ми будемо шукати, якщо ми вже прочитали слово раніше. Ми для початку припускаємо НІ
            for (size_t i = 0; i < wordCounter; ++i)// Перегляньте всі вже прочитані слова та перевірте, чи щойно прочитане слово вже існує
            {
                if (temp == words[i])// Перевірте, чи щойно прочитане слово вже є в масиві слів
                {
                    wordIsAlreadyPresent = true;// Так, встановіть прапорець і зупиніть цикл.
                    break;
                }
            }
            if (!wordIsAlreadyPresent)// якби цього слова ще не було
            {
                words[wordCounter] = temp;// Потім додайте щойно прочитане тимчасове слово в наш масив

                ++wordCounter;
            }

            dobleOfLett(temp);//Виключаз з виводу подвоєні літери

        }
        cout << '\n';
        cout << "Унікальні слова: ";
        for (size_t i = 0; i < wordCounter; ++i)// Показати всі прочитані унікальні слова
        {
            cout << words[i] << ' ';
        }
        cout << '\n';
    }
    else
    {
        cerr << "\nCould not open file '" << fileName << '\n';
    }
    delete[] words;
    input.close();
}