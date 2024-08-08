/*
8. Морской бой (дополнительное задание)
Требуется реализовать упрощённую игру в морской бой. Игровое поле размером 10 на 10 клеток. Участвуют два игрока. 
В арсенале каждого из них 4 маленьких кораблика размером в одну клетку, 3 небольших корабля размером в две клетки, 
2 средних корабля размером в три клетки и один большой корабль размером в четыре клетки. Для простоты клетки поля пронумерованы 
по вертикали от 0 до 9 и по горизонтали от 0 до 9. Мы не будем использовать классические наименования клеток, такие как B4, C6, 
а просто два индекса. Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими. Маленькие корабли 
в одну клетку расставляются с помощью указания одной клетки-точки на поле, к примеру 2,1. Корабли размерностью от двух клеток и выше 
расставляются с помощью координат их начала и конца, к примеру: 0,1–0,3. Корабли могут быть установлены только строго вертикально или 
горизонтально. Установка корабля по диагонали недопустима, об этом тоже надо сообщить пользователю. Если корабль не может быть размещён 
на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках) или выйдет за пределы поля, то игроку должно 
быть сделано предупреждение, после которого он должен переставить корабль на новые валидные координаты. В нашем упрощённом варианте игры 
мы не будем обсчитывать соприкосновения кораблей друг с другом, а потому корабли вполне можно будет размещать друг к другу вплотную, 
борт к борту. После того как все корабли расставлены, начинается игра. Игроки по очереди атакуют друг друга, называя координаты выстрела. 
После выстрела в консоль выводится информация о его результате: попал или мимо. Если выстрел успешен, клетка, на которой был корабль 
(или его фрагмент), затирается и становится пустой. Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены.
 Как только это произойдёт, в консоль выводится информация с номером игрока, который победил.

Советы и рекомендации
Действия игроков практически одинаковые, их можно объединить в функции.
В программе достаточно иметь два поля, по одному на каждого игрока.
Лучше создать три отдельные функции: одну для размещения одного корабля, еще одну как обёртку над первой (она будет размещать все корабли), 
а третью для удара по координате. Также вам потребуются два глобальных массива для двух отдельных участков моря:

bool field_1[10][10];
bool field_2[10][10];

Что оценивается
• Корабли расставляются правильно.
• Есть возможность выиграть.
• Реализован понятный и удобный для пользователя интерфейс игры.
*/

#include <iostream>
#include <string>

using namespace std;

string check_correct_coordinates(int x, int y, bool field[10][10]){
    if (x<0 || x>9 || y<0 || y>9){
        return "Координаты должны быть в пределах [0,9]\n";
    } 
    if (field[x][y]) {
        return "На данной клетке уже находится другой корабль\n";
    }
    return "correct";    
}

int get_max(int a, int b){
    if (a >= b){
        return a;
    }
    return b;
}

int get_min(int a,int b){
    if (a<=b){
        return a;
    }
    return b;
}

string check_correct_coordinates_big_ships(int x1,int y1, int x2, int y2, int how_cell_occupy_ship, bool field[10][10]){
    if (check_correct_coordinates(x1,y1,field) != "correct")
        return check_correct_coordinates(x1,y1,field);
    
    if (check_correct_coordinates(x2,y2,field) != "correct")
        return check_correct_coordinates(x2,y2,field);
    
    if (x1 != x2 && y1 != y2){
        return "Корабли нельзя расставлять по диагонали \n";
    }

    if (get_max(x1,x2) - get_min(x1,x2) != how_cell_occupy_ship-1 &&
        get_max(y1,y2) - get_min(y1,y2) != how_cell_occupy_ship-1){
            return "Корабль должен занимать " + to_string(how_cell_occupy_ship) + " клетки\n";
        }
    
    for (int i=get_min(x1,x2); i<=get_max(x1,x2); ++i){
        for (int j=get_min(y1,y2); j<=get_max(y1,y2); ++j){
            if (check_correct_coordinates(i,j,field) != "correct"){
                return check_correct_coordinates(i,j,field);
            }
        }
    }
    return "correct";
}

void arrange_ship_many_cell(int ships_count, int how_cell_occupy_ship, bool field[10][10]){
    int temp_count_ship = 0;
    while (temp_count_ship < ships_count){
        int x1,y1,x2,y2;
        cout << "Введите две координаты корабля, который занимает " << how_cell_occupy_ship << " клетки, через пробел x1 y1 x2 y2: ";
        cin >> x1 >> y1 >> x2 >> y2;
        if (check_correct_coordinates_big_ships(x1,y1,x2,y2, how_cell_occupy_ship, field) == "correct"){
            for (int i=get_min(x1,x2); i<=get_max(x1,x2); ++i){
                for (int j=get_min(y1,y2); j<=get_max(y1,y2); ++j){
                    field[i][j] = true;
                }
            }
            ++temp_count_ship;
        } else {
            cout << check_correct_coordinates_big_ships(x1,y1,x2,y2, how_cell_occupy_ship, field);
        }
    }
}

void arrange_all_ship(bool field[10][10]){
    int count_ship = 0;
    while (count_ship < 4){
        int x,y;
        cout << "Введите координаты маленького корабля (занимает 1 клетку): ";
        cin >> x >> y;
        if (check_correct_coordinates(x,y, field) == "correct"){
            field[x][y] = true;
            ++count_ship;
        }
        else {
            cout << check_correct_coordinates(x,y, field) << endl;
        }
    }

    arrange_ship_many_cell(3,2,field);
    arrange_ship_many_cell(2,3,field);
    arrange_ship_many_cell(1,4,field);
}

void print_field(bool field[10][10]){
    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
            if (field[i][j]){
                cout << "K" << "  ";
            }
            else {
                cout << "x" << "  ";
            }
        }
        cout << endl;
    }
}

int get_count_ships_player(bool field[10][10]){
    int counter = 0;
    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
            if (field[i][j]){
                ++counter;
            }
        }
    }
    return counter;
}

void attack(bool field[10][10], char game_field[10][10]){
    int x,y;
    cin >> x >> y;
    while (x<0 || x>9 || y<0 || y>9){
        cout << "Координаты должны быть в пределах [0,9], введите еще раз: ";
        cin >> x >> y;
    }

    if (field[x][y]){
        field[x][y] = false;
        cout << "Попал" << endl;
        game_field[x][y] = 'п';
    }
    else {
        cout << "Мимо" << endl;
        game_field[x][y] = 'м';
    }
}

void print_game_field(char field[10][10]){
    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
            cout << field[i][j] << "  ";
        }
        cout << endl;
    }
}

int main(){
    setlocale(LC_ALL, "Russian");

    bool field_1[10][10];
    bool field_2[10][10];
    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
            field_1[i][j] = false;
            field_2[i][j] = false;
        }
    }

    char game_field1[10][10];
    char game_field2[10][10];

    for (int i=0; i<10; ++i){
        for (int j=0; j<10; ++j){
            game_field1[i][j] = '_';
            game_field2[i][j] = '_';
        }
    }


    cout << "Игрок № 1 расставьте свои корабли:" << endl;
    arrange_all_ship(field_1);

    cout << "Расстановка кораблей игрока № 1:" << endl;
    print_field(field_1);

    cout << endl;

    cout << "Игрок № 2 расставьте свои корабли:" << endl;
    arrange_all_ship(field_2);

    cout << "Расстановка корблей игрока № 2:" << endl;
    print_field(field_2);

    cout << endl;
    
    cout << "Игра начинается:" << endl;
    int number_player = 1;
    while (get_count_ships_player(field_1) > 0 && get_count_ships_player(field_2) > 0){
        cout << "Игрок № " << number_player << " ваш ход. Текущее состояние вашего поля:" << endl;
        if (number_player == 1){
            print_field(field_1);
            cout << endl;
            cout << "Игрок № " << number_player << " текущее состояние поля соперника:" << endl;
            print_game_field(game_field1);
        }
        else {
            print_field(field_2);
            cout << "Игрок № " << number_player << " текущее состояние поля соперника:" << endl;
            print_game_field(game_field2);
        }

        cout << "Игрок №" << number_player << ", введите координаты атаки через пробел x y: ";
        if (number_player == 1){
            attack(field_2, game_field1);
            number_player = 2;
        }
        else {
            attack(field_1, game_field2);
            number_player = 1;
        }

        cout << endl;
        
    }

    if (get_count_ships_player(field_1) == 0){
        cout << "Победил игрок № 2";
        cout << "Поле игрока № 2: " << endl;
        print_field(field_2);
    }
    else {
        cout << "Победил игрок № 1" << endl;
        cout << "Поле игрока № 1: " << endl;
        print_field(field_1);
    }

}