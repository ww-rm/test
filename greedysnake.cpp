/*****************************/
/*                           */
/*    ����c++����������!!!    */
/*                           */
/*****************************/

#include <stdio.h>                 //ͷ�ļ�
#include <conio.h>                 //
#include <stdlib.h>                //
#include <Windows.h>               //
#include <time.h>                  //
#define random(n) (rand() % n + 1) //�������[1,n]
#define DIRECTIONKEY -32           //�����������
#define UP 72                      //
#define LEFT 75                    //
#define RIGHT 77                   //
#define DOWN 80                    //

void initScreen();                  //���ˣ����ǳ�
void initSnake(int, int, int, int); //
void printSnake();                  //
void createFood();                  //
int getHighestScore();              //
void updateScore();                 //
void updateHighestScore();          //
void clearSnake(int);               //
void delSnake();                    //
struct SnakeBody;                   //�边����������
struct SnakeHead;                   //
void _lengthenSnake();              //
void _moveSnake();                  //
void changeDirection(char);         //
bool eatSnakeBody();                //
bool eatWall();                     //
bool eatFood();                     //
void autoMoveSnake1();              //
void autoMoveSnake2();              //
void gameMode(int);                 //
int selectGameModeNumber();         //
void mainLoopSnake();               //

HANDLE screen_out = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼���̨
CONSOLE_CURSOR_INFO cursor_info = {25, 0};           //�����Ϣ
COORD position = {0, 0};                             //���λ��
int COLUMN = 30;                                     //��������
int ROW = 25;                                        //��������
int RAW_X = 16;                                      //��Ϸ����ƫ����
int RAW_Y = 1;                                       //
int FOOD_X;                                          //ʳ������
int FOOD_Y;                                          //
bool FOOD;                                           //��ǰʳ���Ƿ����
SnakeHead *head;                                     //��ͷָ��
SnakeBody *rear;                                     //��βָ��
FILE *rank;                                          //�ļ�ָ��

int main()
{
    mainLoopSnake(); //������ѭ������
    return 0;
}

struct SnakeBody //����
{
    int x;           //����
    int y;           //
    SnakeBody *last; //��һ��
    SnakeBody *next; //��һ��
};

struct SnakeHead //��ͷ
{
    int x;           //����
    int y;           //
    int direction;   //ǰ������
    int speed;       //ǰ���ٶ�
    int length;      //���ȣ�����ͷ
    int score;       //�÷�
    SnakeBody *next; //����
};

int getHighestScore() //�ӱ��ػ�ȡ��߷�����¼
{
    int score = 0;
    rank = fopen("greedysnake.dat", "r");
    if (rank != NULL)
    {
        fread(&score, sizeof(int), 1, rank);
    }
    fclose(rank);
    return score;
}

void updateHighestScore() //�򱾵ظ�����߷�����¼
{
    int history = getHighestScore();
    if (head->score > history)
    {
        rank = fopen("greedysnake.dat", "w");
        fwrite(&head->score, sizeof(int), 1, rank);
        fclose(rank);
    }
}

int selectGameModeNumber()
{
    char key;       //ѡ��ģʽ����
    int modenumber; //
    system("cls");
    SetConsoleCursorInfo(screen_out, &cursor_info);
    position.X = COLUMN - 1 + RAW_X - 8;
    position.Y = ROW / 2 + RAW_Y - 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("����ѡ��Enter������Ϸ");
    position.X = COLUMN - 1 + RAW_X;
    position.Y = ROW / 2 + RAW_Y;
    SetConsoleCursorPosition(screen_out, position);
    printf("��սģʽ");
    position.Y += 1;
    SetConsoleCursorPosition(screen_out, position);
    printf("Χǽģʽ");
    position.X -= 4;
    position.Y -= 1;
    SetConsoleCursorPosition(screen_out, position);
    printf("��");
    modenumber = 1; //1����ս��2��Χǽ
    while (true)
    {
        if (_kbhit())
        {
            key = getch();
            if (key == 13)
            {
                system("cls");
                return modenumber;
            }
            else if (key == DIRECTIONKEY)
            {
                key = getch();
                if (key == UP)
                {
                    SetConsoleCursorPosition(screen_out, position);
                    printf("  ");
                    int temp = modenumber;
                    if (modenumber == 1)
                        position.Y += 1;
                    else
                        position.Y -= 1;
                    SetConsoleCursorPosition(screen_out, position);
                    printf("��");
                    if (modenumber == 1)
                        modenumber = 2;
                    else
                        modenumber = 1;
                }
                else if (key == DOWN)
                {
                    SetConsoleCursorPosition(screen_out, position);
                    printf(" ");
                    int temp = modenumber;
                    if (modenumber == 2)
                        position.Y -= 1;
                    else
                        position.Y += 1;
                    SetConsoleCursorPosition(screen_out, position);
                    printf("��");
                    if (modenumber == 1)
                        modenumber = 2;
                    else
                        modenumber = 1;
                }
            }
            else
                continue;
        }
    }
}

void initScreen() //���һ����
{
    system("cls");                                  //����
    char wall[4] = "��";                             //ǽ�á�Χ����
    SetConsoleCursorInfo(screen_out, &cursor_info); //���ù�����ԣ�����
    position.X = -1 + RAW_X;                        //��ʼ�������ƫ����
    position.Y = 0 + RAW_Y;                         //
    for (int i = 0; i <= COLUMN; i++)               //��
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X += 2;
    }
    for (int i = 0; i <= ROW; i++) //��
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y++;
    }
    for (int i = 0; i <= COLUMN; i++) //��
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X -= 2;
    }
    for (int i = 0; i <= ROW; i++) //��
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y--;
    }
    position.X = 2 * COLUMN + 3 + RAW_X; //����÷�����
    position.Y = 0 + RAW_Y;
    for (int i = 0; i <= 8; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X += 2;
    }
    for (int i = 0; i <= (int)ROW / 2 - 1; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y++;
    }
    for (int i = 0; i <= 8; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X -= 2;
    }
    for (int i = 0; i <= (int)ROW / 2 - 1; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y--;
    }
    position.X += 2;
    position.Y += (int)ROW / 8 - 1;
    SetConsoleCursorPosition(screen_out, position);
    printf("    ��ǰ�÷�");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("       00");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("    ��ʷ���");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("       %02d", getHighestScore()); //��ȡ��ʷ��߷�
    position.X = 2 * COLUMN + 3 + RAW_X;      //�����ʾ��
    position.Y = (int)ROW / 2 + 1 + RAW_Y;
    for (int i = 0; i <= 8; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X += 2;
    }
    for (int i = 0; i <= (int)ROW / 2; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y++;
    }
    for (int i = 0; i <= 8; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.X -= 2;
    }
    for (int i = 0; i <= (int)ROW / 2; i++)
    {
        SetConsoleCursorPosition(screen_out, position);
        printf(wall);
        position.Y--;
    }
    position.X += 2;
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf(" �������ʼ��Ϸ");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf(" ����������ƶ�");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("'p'��ͣ/������Ϸ");
    position.Y += 2;
    SetConsoleCursorPosition(screen_out, position);
    printf("  'q'�˳���Ϸ");
}

void initSnake(int speed, int length, int raw_x, int raw_y) //��ʼ����
{
    SnakeBody *p;
    head = (SnakeHead *)malloc(sizeof(SnakeHead));
    rear = (SnakeBody *)malloc(sizeof(SnakeBody));
    head->direction = RIGHT;              //Ĭ���ҷ���
    head->speed = speed;                  //Ĭ���ٶ� 1��/200����
    head->length = length;                //��ʼ����Ϊ4
    head->score = 0;                      //�÷�Ϊ��
    head->next = rear;                    //ָ����һ��
    head->x = raw_x;                      //���ó�ʼ��ͷλ��
    head->y = raw_y;                      //
    rear->last = NULL;                    //�ÿ�
    rear->next = NULL;                    //
    rear->x = raw_x - 1;                  //���ó�ʼֵ
    rear->y = raw_y;                      //
    for (int i = 0; i <= length - 3; i++) //����length��ʼ���ߵĳ��ȣ�β�巨
    {
        p = rear;
        rear->next = (SnakeBody *)malloc(sizeof(SnakeBody));
        rear = rear->next;
        p->next = rear;
        rear->last = p;
        rear->next = NULL;
        rear->x = p->x - 1;
        rear->y = p->y;
    }
}

void delSnake() //ɾ����
{
    SnakeBody *p;
    while (rear != NULL) //ɾ������
    {
        p = rear;
        rear = rear->last;
        free(p);
    }
    free(head); //ɾ����ͷ
}

void printSnake()
{
    SnakeBody *p = head->next;
    position.X = 2 * head->x - 1 + RAW_X;           //��ͷ�����ƫ����
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //������ͷ����
    printf("��");                                    //��ͷ
    while (p != NULL)                               //�������
    {
        position.X = 2 * p->x - 1 + RAW_X;
        position.Y = p->y + RAW_Y;
        SetConsoleCursorPosition(screen_out, position);
        printf("��");
        p = p->next;
    }
}

void clearSnake(int speed) //�������
{
    SnakeBody *p = head->next;
    position.X = 2 * head->x - 1 + RAW_X;           //��ͷ�����ƫ����
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //������ͷ����
    putchar(' ');                                   //�����ͷ
    while (p != NULL)                               //�������
    {
        position.X = 2 * p->x - 1 + RAW_X;
        position.Y = p->y + RAW_Y;
        SetConsoleCursorPosition(screen_out, position);
        Sleep(speed);
        putchar(' ');
        p = p->next;
    }
}

void _lengthenSnake() //�ӳ�һ������ͷ�巨
{
    SnakeBody *p = head->next;
    head->length++;                                      //���ȼ�һ
    head->next = (SnakeBody *)malloc(sizeof(SnakeBody)); //����ͷλ�ñ�Ϊ����
    head->next->last = NULL;                             //��ʼ��������
    head->next->x = head->x;                             //
    head->next->y = head->y;                             //
    head->next->next = p;                                //����ԭ����
    p->last = head->next;                                //
    switch (head->direction)                             //�����������ͷ����
    {
    case UP:
        head->y = ((head->y - 2 + ROW) % ROW) + 1;
        break;
    case RIGHT:
        head->x = (head->x % COLUMN) + 1;
        break;
    case DOWN:
        head->y = (head->y % ROW) + 1;
        break;
    case LEFT:
        head->x = ((head->x - 2 + COLUMN) % COLUMN) + 1;
        break;
    }
}

void updateScore() //���·���
{
    position.X = 2 * COLUMN + 5 + RAW_X;
    position.Y = 2 + (int)ROW / 8 - 1 + RAW_Y;
    SetConsoleCursorPosition(screen_out, position);
    printf("       %02d", head->score);
}

void _moveSnake() //�ӳ�������ɾȥ��β
{
    _lengthenSnake();
    head->length--;
    SnakeBody *p = rear; //ɾ��ԭ��β
    rear = rear->last;   //βָ��ǰ��
    rear->next = NULL;   //�ÿ�
    free(p);
}

void changeDirection(char direction) //�ı���ͷ����
{
    switch (direction)
    {
    case UP:
        if (head->direction != DOWN)
        {
            head->direction = UP;
        }
        break;
    case DOWN:
        if (head->direction != UP)
        {
            head->direction = DOWN;
        }
        break;
    case LEFT:
        if (head->direction != RIGHT)
        {
            head->direction = LEFT;
        }
        break;
    case RIGHT:
        if (head->direction != LEFT)
        {
            head->direction = RIGHT;
        }
        break;
    }
}

void createFood() //�������ʳ��
{
    srand(time(NULL)); //�����������
    SnakeBody *p;
    SnakeHead *p1;
    bool flag = true; //�Ƿ�����ɹ�
    while (flag)
    {
        flag = false;
        FOOD_X = random(COLUMN); //���������[1,COLUMN]
        FOOD_Y = random(ROW);    //���������[1,ROW]
        p = head->next;
        if (FOOD_X == head->x && FOOD_Y == head->y) //�ж��Ƿ�����ͷ�غ�
        {
            flag = true;
            continue;
        }
        while (p != NULL) //�ж��Ƿ��������غ�
        {
            if (FOOD_X == p->x && FOOD_Y == p->y)
            {
                flag = true;
                break;
            }
            p = p->next;
        }
    }
    position.X = 2 * FOOD_X - 1 + RAW_X; //���ù��λ��
    position.Y = FOOD_Y + RAW_Y;
    SetConsoleCursorPosition(screen_out, position);
    printf("��"); //���ʳ��
    FOOD = true; //��ǰʳ�����
}

bool eatSnakeBody() //��һ���Ƿ�Ϊ����
{
    int next_x;
    int next_y;
    SnakeBody *p = head->next;
    switch (head->direction)
    {
    case UP:
        next_x = head->x;
        next_y = ((head->y - 2 + ROW) % ROW) + 1;
        break;
    case RIGHT:
        next_x = (head->x % COLUMN) + 1;
        next_y = head->y;
        break;
    case DOWN:
        next_x = head->x;
        next_y = (head->y % ROW) + 1;
        break;
    case LEFT:
        next_x = ((head->x - 2 + COLUMN) % COLUMN) + 1;
        next_y = head->y;
        break;
    }
    while (p != NULL)
    {
        if (p->x == next_x && p->y == next_y) //ͨ�������ж�
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool eatWall() //�Ƿ�ײǽ
{
    int next_x;
    int next_y;
    SnakeBody *p = head->next;
    switch (head->direction)
    {
    case UP:
        next_x = head->x;
        next_y = head->y - 1;
        break;
    case RIGHT:
        next_x = head->x + 1;
        next_y = head->y;
        break;
    case DOWN:
        next_x = head->x;
        next_y = head->y + 1;
        break;
    case LEFT:
        next_x = head->x - 1;
        next_y = head->y;
        break;
    }
    if (head->direction == UP && next_y == 0)
    {
        return true;
    }
    if (head->direction == DOWN && next_y == ROW + 1)
    {
        return true;
    }
    if (head->direction == LEFT && next_x == 0)
    {
        return true;
    }
    if (head->direction == RIGHT && next_x == COLUMN + 1)
    {
        return true;
    }
    return false;
}

bool eatFood() //��һ���Ƿ�Ϊʳ��
{
    int next_x;
    int next_y;
    SnakeBody *p = head->next;
    switch (head->direction)
    {
    case UP:
        next_x = head->x;
        next_y = ((head->y - 2 + ROW) % ROW) + 1;
        break;
    case RIGHT:
        next_x = (head->x % COLUMN) + 1;
        next_y = head->y;
        break;
    case DOWN:
        next_x = head->x;
        next_y = (head->y % ROW) + 1;
        break;
    case LEFT:
        next_x = ((head->x - 2 + COLUMN) % COLUMN) + 1;
        next_y = head->y;
        break;
    }
    if (next_x == FOOD_X && next_y == FOOD_Y)
    {
        return true;
    }
    return false;
}

void autoMoveSnake1() //��ͨ�ƶ�
{
    position.X = 2 * rear->x - 1 + RAW_X;           //�����β
    position.Y = rear->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //
    putchar(' ');                                   //
    position.X = 2 * head->x - 1 + RAW_X;           //����ԭ��ͷ����
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //
    printf("��");                                    //
    _moveSnake();                                   //�����ƶ�����
    position.X = 2 * head->x - 1 + RAW_X;           //�������ͷ
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //
    printf("��");                                    //
    Sleep(head->speed);                             //�����ٶ�
}

void autoMoveSnake2() //��ʳ���ƶ�
{
    FOOD = false;                                   //ʳ����false
    head->score++;                                  //�÷ּ�һ
    position.X = 2 * head->x - 1 + RAW_X;           //����ԭ��ͷ����
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //
    printf("��");                                    //
    _lengthenSnake();                               //����һ������
    position.X = 2 * head->x - 1 + RAW_X;           //�������ͷ
    position.Y = head->y + RAW_Y;                   //
    SetConsoleCursorPosition(screen_out, position); //
    printf("��");                                    //
    Sleep(head->speed);                             //�����ٶ�
}

void gameMode(int gamemodenumber) //��ʼ��Ϸ
{
    char key;
    bool pause_game = false;
    FOOD = false; //��ʼû��ʳ��
    while (true)
    {
        SetConsoleCursorInfo(screen_out, &cursor_info);
        if (!FOOD)
        {
            createFood();
        }
        if (_kbhit())
        {
            key = getch();
            if (key == 'q') //�˳�
            {
                clearSnake(0);
                fflush(stdin);
                break;
            }
            else if (key == 'p') //��ͣ����
            {
                position.X = 2 * COLUMN + 5 + RAW_X;
                position.Y = (int)ROW / 2 + 11 + RAW_Y;
                SetConsoleCursorPosition(screen_out, position);
                if (pause_game == true)
                {
                    printf("             ");
                    pause_game = false;
                }
                else
                {
                    printf("    ��ͣ��...");
                    pause_game = true;
                }
                fflush(stdin);
            }
            else if (key == DIRECTIONKEY && !pause_game) //�ı��ߵķ���
            {
                key = getch();
                changeDirection(key);
            }
            else
            {
                fflush(stdin);
            }
        }
        if (!pause_game) //����ͣ״̬
        {
            if (gamemodenumber == 2) //Χǽģʽ��һ��ײǽ�ж�
            {
                if (eatWall())
                {
                    Sleep(500);
                    clearSnake(50);
                    updateHighestScore(); //������ʷ��߷�
                    break;
                }
            }

            if (eatSnakeBody()) //�Ƿ�Ե�����
            {
                Sleep(500);
                clearSnake(50);
                updateHighestScore(); //������ʷ��߷�
                break;
            }
            else if (eatFood()) //�Ƿ�Ե�ʳ��
            {
                autoMoveSnake2();
                updateScore();
                if (head->speed > 20) //��һ��ʳ��ͼ���
                {
                    head->speed -= 3; //�ٶ�������
                }
            }
            else //��ͨ�ƶ�
            {
                autoMoveSnake1();
            }
        }
    }
}

void mainLoopSnake() //��ѭ������
{
    if (system("chcp 936")) //��֤������
    {
        printf("�޷�������ʾ��");
        system("pause");
        return;
    }
    system("color 0b"); //��ɫ
    char key;
    while (true)
    {
        int gamemodenumber = selectGameModeNumber(); //ѡ����Ϸģʽ
        initScreen();                                //�������г�ʼ������
        initSnake(200, 4, COLUMN / 2, ROW / 2);      //
        printSnake();                                //
        getch();                                     //�������ʼ��Ϸ
        gameMode(gamemodenumber);                    //��Ϸ��ʼ
        delSnake();                                  //��������
        position.X = (int)COLUMN * 4 / 5 - 2 + RAW_X;
        position.Y = (int)ROW / 2 - 1 + RAW_Y;
        SetConsoleCursorPosition(screen_out, position);
        printf("  ��Ϸ����...");
        position.Y += 2;
        SetConsoleCursorPosition(screen_out, position);
        printf("'r'��ʼ�µ�һ��...");
        position.Y += 2;
        SetConsoleCursorPosition(screen_out, position);
        printf(" 'q'�˳���Ϸ...");
        key = '\0';
        while (key != 'r' && key != 'q')
        {
            key = getch();
        }
        if (key == 'q')
        {
            break;
        }
    }
    system("color 0f"); //�ָ���ʼ
    system("cls");
}
