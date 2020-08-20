#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Node
{
public:
    Node* son, * brother, * parent;
    int value;
    explicit Node(int value) : son(NULL), brother(NULL), parent(NULL), value(value)
    { }
};

void insert_son(Node* N, int value)
{
    N->son = new Node(value);
    N->son->parent = N;
}

void insert_brother(Node* N, int value)
{
    N->brother = new Node(value);
    N->brother->parent = N->parent;
}

int comparison(Node* first_tree, int size1, Node* second_tree, int size2);
void bfs(Node* N, int* order, int& index);
Node* search(Node* N, int value);
void bfs(Node* N, int& leaves);
int how_many_sons(Node* N);
void what_sons(Node* N, int* sons, int index);
int mast(int** table, int height, int width);
int trzyxtrzy(int** table, int height, int width);

int main()
{
    int n; // liczba drzew
    cin >> n;

    Node** root = new Node * [n];
    for (int i = 0; i < n; i++)
        root[i] = new Node(0);

    int* size = new int[n];
    for (int i = 0; i < n; i++)
        size[i] = 1;

    for (int i = 0; i < n; i++) {
        char ch;
        int id = -1;
        cin >> ch;
        while (ch != ';') {
            if (ch == '(') {
                insert_son(root[i], id);
                root[i] = root[i]->son;
                size[i] += 1;
                id -= 1;
            }
            else if (ch == ',') {
                insert_brother(root[i], id);
                root[i] = root[i]->brother;
                size[i] += 1;
                id -= 1;
            }
            else if (ch == ')')
                root[i] = root[i]->parent;
            else {
                if (ch == '1') {
                    cin.get(ch);
                    if (ch == '0') {
                        root[i]->value = 10;
                        id += 1;
                    }
                    else {
                        root[i]->value = 1;
                        id += 1;
                        continue;
                    }
                }
                else {
                    root[i]->value = (int)ch - 48;
                    id += 1;
                }
            }
            cin >> ch;
        }
    }

    int start = 1;
    for (int i = 0; i < (n - 1); i++) {
        for (int j = start; j < n; j++) {
            cout << comparison(root[i], size[i], root[j], size[j]) << endl;
        }
        start += 1;
    }

    for (int i = 0; i < n; i++)
        delete[] root[i];
    delete[] root;
    delete[] size;

    return 0;
}

int trzyxtrzy(int** table, int height, int width)
{
    int max_sum = 0;

    for (int i = 0; i < width; i++) { // dla wszystkich liczb z pierwszego wiersza
        int odp = table[0][i];
        int k = 0;
        for (int j = 1; j < height; j++, k++) {
            if (k == i)
                k += 1;
            odp += table[j][k];
        }
        if (odp > max_sum)
            max_sum = odp;
        k = 0;
        odp = table[0][i];
        for (int j = height - 1; j > 0; j--, k++) {
            if (k == i)
                k += 1;
            odp += table[j][k];
        }
        if (odp > max_sum)
            max_sum = odp;
    }

    return max_sum;
}

int mast(int** table, int height, int width)
{
    int max_sum = 0;

    if (height == 1 && width == 1)
        max_sum = table[0][0];
    else if (height == 2 && width == 1) {
        if (table[0][0] > table[1][0])
            max_sum = table[0][0];
        else
            max_sum = table[1][0];
    }
    else if (height == 1 && width == 2) {
        if (table[0][0] > table[0][1])
            max_sum = table[0][0];
        else
            max_sum = table[0][1];
    }
    else if (height == 2 && width == 2) {
        if (table[0][0] + table[1][1] > table[0][1] + table[1][0])
            max_sum = table[0][0] + table[1][1];
        else
            max_sum = table[0][1] + table[1][0];
    }
    else if (height == 3 && width == 3)
        max_sum = trzyxtrzy(table, height, width);
    else {
        int not_zeros = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (table[i][j] != 0)
                    not_zeros += 1;
            }
        }
        if (not_zeros == 1) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (table[i][j] != 0)
                        max_sum = table[i][j];
                }
            }
        }
        else {
            int how_many_numbers = (height > width ? height : width);

            int* max_numbers = new int[how_many_numbers];
            for (int i = 0; i < how_many_numbers; i++)
                max_numbers[i] = 0;

            int* x = new int[how_many_numbers - 1];
            int* y = new int[how_many_numbers - 1];
            for (int i = 0; i < (how_many_numbers - 1); i++) {
                x[i] = INT_MAX;
                y[i] = INT_MAX;
            }

            int counter = 0;
            while (counter != how_many_numbers) {
                int answer = 0;
                int index_x = INT_MAX;
                int index_y = INT_MAX;
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < (how_many_numbers - 1); j++) {
                        for (int l = 0; l < (how_many_numbers - 1); l++) {
                            if (i == x[l])
                                i += 1;
                        }
                    }
                    if (i < height) {
                        for (int j = 0; j < width; j++) {
                            for (int k = 0; k < (how_many_numbers - 1); k++) {
                                for (int l = 0; l < (how_many_numbers - 1); l++) {
                                    if (j == y[l])
                                        j += 1;
                                }
                            }
                            if (j < width) {
                                if (table[i][j] > answer) {
                                    answer = table[i][j];
                                    if (counter < (how_many_numbers - 1)) {
                                        index_x = i;
                                        index_y = j;
                                    }
                                }
                            }
                        }
                    }
                }
                if (counter < (how_many_numbers - 1)) {
                    x[counter] = index_x;
                    y[counter] = index_y;
                }
                max_numbers[counter] = answer;
                counter += 1;
            }

            for (int i = 0; i < how_many_numbers; i++)
                max_sum += max_numbers[i];

            delete[] y;
            delete[] x;
            delete[] max_numbers;
        }
    }

    return max_sum;
}

void what_sons(Node* N, int* sons, int index)
{
    N = N->son;
    sons[index] = N->value;
    index += 1;
    while (N->brother != NULL) {
        N = N->brother;
        sons[index] = N->value;
        index += 1;
    }
}

int how_many_sons(Node* N)
{
    int sons = 1; // zawsze jest jeden syn w tym przpadku
    N = N->son;
    while (N->brother != NULL) {
        N = N->brother;
        sons += 1;
    }
    return sons;
}

void bfs(Node* N, int& leaves)
{
    if (N != NULL) {
        if (N->son == NULL)
            leaves += 1;
        bfs(N->son, leaves);
        bfs(N->brother, leaves);
    }
}

Node* search(Node* N, int value) // dfs
{
    if (N == NULL)
        return NULL;
    if (N->value == value)
        return N;
    Node* n = search(N->son, value);
    if (n != NULL)
        return n;
    else
        return search(N->brother, value);
}

void bfs(Node* N, int* order, int& index)
{
    if (N != NULL) {
        if (N->son == NULL) {
            order[index] = N->value;
            index += 1;
        }
        bfs(N->son, order, index);
        bfs(N->brother, order, index);
    }
}

int comparison(Node* first_tree, int size1, Node* second_tree, int size2)
{
    int* order1 = new int[size1];
    int start = 0;
    bfs(first_tree, order1, start);
    for (int i = start; i < size1; i++) {
        if (i <= 10)
            order1[i] = 0;
        else
            order1[i] = 10 - i;
    }

    int* order2 = new int[size2];
    start = 0;
    bfs(second_tree, order2, start);
    for (int i = start; i < size2; i++) {
        if (i <= 10)
            order2[i] = 0;
        else
            order2[i] = 10 - i;
    }

    int** map = new int* [size1];
    for (int i = 0; i < size1; i++)
        map[i] = new int[size2];

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++)
            map[i][j] = 0;
    }

    // pierwsza sekcja mapy

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (order1[i] == order2[j]) {
                map[i][j] = 1;
                break;
            }
        }
    }

    // druga i trzecia sekcja mapy

    for (int i = 0; i < 10; i++) {
        map[i][10] = 1;
    }

    for (int j = 0; j < 10; j++) {
        map[10][j] = 1;
    }

    for (int i = 11; i < size2; i++) {
        Node* temp = search(second_tree, 10 - i);
        start = 0;
        bfs(temp->son, start);
        int* leaves = new int[start];
        int start1 = 0;
        bfs(temp->son, leaves, start1);
        for (int j = 0; j < start; j++) {
            for (int k = 0; k < 10; k++) {
                if (leaves[j] == order1[k]) {
                    map[k][i] = 1;
                    break;
                }
            }
        }
        delete[] leaves;
    }

    for (int i = 11; i < size1; i++) {
        Node* temp = search(first_tree, 10 - i);
        start = 0;
        bfs(temp->son, start);
        int* leaves = new int[start];
        int start1 = 0;
        bfs(temp->son, leaves, start1);
        for (int j = 0; j < start; j++) {
            for (int k = 0; k < 10; k++) {
                if (leaves[j] == order2[k]) {
                    map[i][k] = 1;
                    break;
                }
            }
        }
        delete[] leaves;
    }

    // czwarta sekcja mapy

    for (int i = size2 - 1; i >= 10; i--) {

        Node* temp2 = search(second_tree, order2[i]);
        int number_of_sons2 = how_many_sons(temp2);
        int* sons2 = new int[number_of_sons2];
        what_sons(temp2, sons2, 0);

        for (int j = size1 - 1; j >= 10; j--) {
            Node* temp1 = search(first_tree, order1[j]);
            int number_of_sons1 = how_many_sons(temp1);
            int* sons1 = new int[number_of_sons1];
            what_sons(temp1, sons1, 0);

            int** table = new int* [number_of_sons1];
            for (int k = 0; k < number_of_sons1; k++)
                table[k] = new int[number_of_sons2];
            for (int k = 0; k < number_of_sons1; k++) {
                for (int l = 0; l < number_of_sons2; l++)
                    table[k][l] = 0;
            }

            for (int l = 0; l < number_of_sons2; l++) {
                int x = 0, y = 0;
                for (int k = 0; k < size2; k++) {
                    if (order2[k] == sons2[l]) {
                        y = k;
                        break;
                    }
                }
                for (int m = 0; m < number_of_sons1; m++) {
                    for (int k = 0; k < size1; k++) {
                        if (order1[k] == sons1[m]) {
                            x = k;
                            break;
                        }
                    }
                    table[m][l] = map[x][y];
                }
            }

            int answer = mast(table, number_of_sons1, number_of_sons2);

            for (int k = 0; k < number_of_sons2; k++) {
                for (int l = 0; l < size2; l++) {
                    if (order2[l] == sons2[k]) {
                        int odp = map[j][l];
                        if (odp > answer)
                            answer = odp;
                        break;
                    }
                }
            }

            for (int k = 0; k < number_of_sons1; k++) {
                for (int l = 0; l < size1; l++) {
                    if (order1[l] == sons1[k]) {
                        int odp = map[l][i];
                        if (odp > answer)
                            answer = odp;
                        break;
                    }
                }
            }

            map[j][i] = answer;

            for (int k = 0; k < number_of_sons1; k++)
                delete[] table[k];
            delete[] table;
            delete[] sons1;
        }

        delete[] sons2;
    }

    int mast = 10 - map[10][10];

    for (int i = 0; i < size1; i++)
        delete[] map[i];
    delete[] map;
    delete[] order1;
    delete[] order2;

    return mast;
}
