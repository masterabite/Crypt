#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//функция шифрует строку text по ключу key (теперь это просто число/сдвиг) и записывает ответ в строку crpyt
string encrypt(const string& text, int key) {


    int i = 0, j = 0;
    string crypt = "";

    //сдвиг должен находится в границах 0..25
    key %= 26;

    //шифруем строку посимвольно (перебираем i пока не встретили конец строки)
    //i указывает на позицию в шифруемом текста
    for (int i = 0; i < int(text.size()); ++i) {

        if (is_letter(text[i])) {
            char first = (text[i] >= 'a' && text[i] <= 'z' ? 'a' : 'A');
            // в данном случае text[i] - ('A'/'a') это номер i-ой буквы текста по алфавиту
            crypt += first + (text[i] - first + key) % 26;
        }
        else {
            crypt += text[i];
        }
    }
    return crypt;
}

//функция расшировывает шифр crypt по ключу key (теперь это просто сдвиг)
string decrypt(const string& crypt, int key) {


    string text = "";

    //сдвиг должен находится в границах 0..25
    key %= 26;

    //шифруем строку посимвольно (перебираем i пока не встретили конец строки)
    //i указывает на позицию в шифре
    for (int i = 0; i < int(crypt.size()); ++i) {

        if (is_letter(crypt[i])) {
            char first = (crypt[i] >= 'a' && crypt[i] <= 'z' ? 'a' : 'A');

            //расшифровываем
            //сначала определяем на сколько был сдвинут символ
            int shift = crypt[i] - first - key;

            //если сдвиг выходил за пределы алфавита, нужно это учесть
            if (shift < 0) {
                shift += 26;
            }

            //теперь можно расшифровать символ
            text += first + shift;
        }
        else {
            text += crypt[i];
        }
    }
    return text;
}


void scanline(string& str) {
    int cmd = -1;
    str = "";
    cout << "Ввод текста:\n";
    cout << "\t0- из файла\n";
    cout << "\t1- с клавиатуры\n";
    cout << "Введите команду: ";
    cin >> cmd;
    cin.get();

    if (cmd == 0) {
        string fname;
        cout << "Введите название файла: ";
        cin >> fname;
        ifstream fin(fname);
        if (!fin.is_open()) {
            cout << "Не удалось открыть файл...\n";
            return;
        }
        
        while (!fin.eof()) {
            str += fin.get();
        }

    }
    else {
        cout << "Введите текст: ";
        getline(cin, str);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string text, crypt;
    int key;

    int cmd = -1; //переменная для считывания команд

    //основной цикл меню
    while (cmd != 0) {
        printf("\nМеню:\n");
        printf("\t0- выход\n");
        printf("\t1- зашифровать\n");
        printf("\t2- расшифровать\n");
        printf("Введите команду: ");
        cin >> cmd;
        cin.get();

        if (cmd == 0) { break; }
        else if (cmd == 1) {
            scanline(text);

            printf("Введите ключ: ");
            cin >> key;
            cin.get();

            cout << encrypt(text, key);

        }
        else if (cmd == 2) {
            scanline(crypt);

            printf("Введите ключ: ");
            cin >> key;
            cin.get();

            cout << decrypt(crypt, key);

        }
    }

    return 0;
}
