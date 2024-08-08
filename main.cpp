/*
8. ������� ��� (�������������� �������)
��������� ����������� ���������� ���� � ������� ���. ������� ���� �������� 10 �� 10 ������. ��������� ��� ������. 
� �������� ������� �� ��� 4 ��������� ��������� �������� � ���� ������, 3 ��������� ������� �������� � ��� ������, 
2 ������� ������� �������� � ��� ������ � ���� ������� ������� �������� � ������ ������. ��� �������� ������ ���� ������������� 
�� ��������� �� 0 �� 9 � �� ����������� �� 0 �� 9. �� �� ����� ������������ ������������ ������������ ������, ����� ��� B4, C6, 
� ������ ��� �������. ������� ������ �� ������� ����������� �������, ������� � ����� ��������� � ���������� ��������. ��������� ������� 
� ���� ������ ������������� � ������� �������� ����� ������-����� �� ����, � ������� 2,1. ������� ������������ �� ���� ������ � ���� 
������������� � ������� ��������� �� ������ � �����, � �������: 0,1�0,3. ������� ����� ���� ����������� ������ ������ ����������� ��� 
�������������. ��������� ������� �� ��������� �����������, �� ���� ���� ���� �������� ������������. ���� ������� �� ����� ���� �������� 
�� �������� ������� ��-�� ����, ��� �� ��������� � ������ ������� (�������� �� ��� �������) ��� ������ �� ������� ����, �� ������ ������ 
���� ������� ��������������, ����� �������� �� ������ ����������� ������� �� ����� �������� ����������. � ����� ���������� �������� ���� 
�� �� ����� ����������� ��������������� �������� ���� � ������, � ������ ������� ������ ����� ����� ��������� ���� � ����� ��������, 
���� � �����. ����� ���� ��� ��� ������� �����������, ���������� ����. ������ �� ������� ������� ���� �����, ������� ���������� ��������. 
����� �������� � ������� ��������� ���������� � ��� ����������: ����� ��� ����. ���� ������� �������, ������, �� ������� ��� ������� 
(��� ��� ��������), ���������� � ���������� ������. ���� ������������� �����, ����� ��� ������� ����� �� ������ ����� ��������� ����������.
 ��� ������ ��� ���������, � ������� ��������� ���������� � ������� ������, ������� �������.

������ � ������������
�������� ������� ����������� ����������, �� ����� ���������� � �������.
� ��������� ���������� ����� ��� ����, �� ������ �� ������� ������.
����� ������� ��� ��������� �������: ���� ��� ���������� ������ �������, ��� ���� ��� ������ ��� ������ (��� ����� ��������� ��� �������), 
� ������ ��� ����� �� ����������. ����� ��� ����������� ��� ���������� ������� ��� ���� ��������� �������� ����:

bool field_1[10][10];
bool field_2[10][10];

��� �����������
� ������� ������������� ���������.
� ���� ����������� ��������.
� ���������� �������� � ������� ��� ������������ ��������� ����.
*/

#include <iostream>
#include <string>

using namespace std;

string check_correct_coordinates(int x, int y, bool field[10][10]){
    if (x<0 || x>9 || y<0 || y>9){
        return "���������� ������ ���� � �������� [0,9]\n";
    } 
    if (field[x][y]) {
        return "�� ������ ������ ��� ��������� ������ �������\n";
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
        return "������� ������ ����������� �� ��������� \n";
    }

    if (get_max(x1,x2) - get_min(x1,x2) != how_cell_occupy_ship-1 &&
        get_max(y1,y2) - get_min(y1,y2) != how_cell_occupy_ship-1){
            return "������� ������ �������� " + to_string(how_cell_occupy_ship) + " ������\n";
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
        cout << "������� ��� ���������� �������, ������� �������� " << how_cell_occupy_ship << " ������, ����� ������ x1 y1 x2 y2: ";
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
        cout << "������� ���������� ���������� ������� (�������� 1 ������): ";
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
        cout << "���������� ������ ���� � �������� [0,9], ������� ��� ���: ";
        cin >> x >> y;
    }

    if (field[x][y]){
        field[x][y] = false;
        cout << "�����" << endl;
        game_field[x][y] = '�';
    }
    else {
        cout << "����" << endl;
        game_field[x][y] = '�';
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


    cout << "����� � 1 ���������� ���� �������:" << endl;
    arrange_all_ship(field_1);

    cout << "����������� �������� ������ � 1:" << endl;
    print_field(field_1);

    cout << endl;

    cout << "����� � 2 ���������� ���� �������:" << endl;
    arrange_all_ship(field_2);

    cout << "����������� ������� ������ � 2:" << endl;
    print_field(field_2);

    cout << endl;
    
    cout << "���� ����������:" << endl;
    int number_player = 1;
    while (get_count_ships_player(field_1) > 0 && get_count_ships_player(field_2) > 0){
        cout << "����� � " << number_player << " ��� ���. ������� ��������� ������ ����:" << endl;
        if (number_player == 1){
            print_field(field_1);
            cout << endl;
            cout << "����� � " << number_player << " ������� ��������� ���� ���������:" << endl;
            print_game_field(game_field1);
        }
        else {
            print_field(field_2);
            cout << "����� � " << number_player << " ������� ��������� ���� ���������:" << endl;
            print_game_field(game_field2);
        }

        cout << "����� �" << number_player << ", ������� ���������� ����� ����� ������ x y: ";
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
        cout << "������� ����� � 2";
        cout << "���� ������ � 2: " << endl;
        print_field(field_2);
    }
    else {
        cout << "������� ����� � 1" << endl;
        cout << "���� ������ � 1: " << endl;
        print_field(field_1);
    }

}