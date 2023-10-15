#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define ROW 6
#define COL 7

typedef struct stack{
    int arr[ROW][COL];
    int top[COL];
}STACK;

void init_board(STACK* ps){
    
    for(int i=0;i<ROW;i++){         
        for(int j=0;j<COL;j++){
            ps->arr[i][j]=0;                
        }
    }
}

void print_board(STACK* ps){
    for(int i=ROW-1;i>=0;i--){
        for(int j=0;j<COL;j++){
            printf(" %d ",ps->arr[i][j]);
        }
        printf("\n");
    }
}

int check_horizontal(STACK* ps,int token){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<=COL-4;j++){
            if(ps->arr[i][j] == ps->arr[i][j+1] && ps->arr[i][j+1] == ps->arr[i][j+2] && ps->arr[i][j+2] == ps->arr[i][j+3] && ps->arr[i][j]==token){
                return token;
            }
        }
    }
    return 0;
}

int check_vertical(STACK* ps, int token){
    for(int i=0;i<ROW-4;i++){
        for(int j=0;j<COL;j++){
            if(ps->arr[i][j] == ps->arr[i+1][j] && ps->arr[i+1][j] == ps->arr[i+2][j] && ps->arr[i+2][j] == ps->arr[i+3][j] && ps->arr[i][j]==token){
                return token;
            }
        }
    }
    return 0;
}

int check_diagonal_right(STACK* ps, int token){
    // i-> 0 to 2; j->0 to 3
    for(int i=0;i<=2;i++){
        for(int j=0;j<=3;j++){
            if(ps->arr[i][j]== ps->arr[i+1][j+1] && ps->arr[i+1][j+1] == ps->arr[i+2][j+2] && ps->arr[i+2][j+2] == ps->arr[i+3][j+3] && ps->arr[i][j] == token)
                return token;
        }
    }
    return 0;
}

int check_diagonal_left(STACK* ps, int token){
    for(int i=0;i<=2;i++){
        for(int j=6;j>=3;j--){
            if(ps->arr[i][j]== ps->arr[i+1][j-1] && ps->arr[i+1][j-1] == ps->arr[i+2][j-2] && ps->arr[i+2][j-2] == ps->arr[i+3][j-3] && ps->arr[i][j]== token)
                return token;
        }
    }
    return 0;
}

void input_1(STACK* ps, int column, int token){
    if(ps->top[column] +1 >5){
        printf("Already Full\n");
        return;
    }
    if(column > 6 || column < 0){
        printf("Invalid\n");
        return;
    }
    ps->top[column]++;
    ps->arr[ps->top[column]][column] = token;
}

void check_win(STACK* ps, int token){
    int win = 0;
    if(check_horizontal(ps,token) || check_vertical(ps,token) || check_diagonal_right(ps,token) || check_diagonal_left(ps,token))
        win = token;

    switch(win){
        case 0:
            return;
        case 1:
            printf("Player 1 wins!");
            exit(0);
            break;
        case 2:
            printf("Player 2 wins!");
            exit(0);
            break;        
    }    
}

int main(){
    int player1=1 , player2=2;
    char p1[100],p2[100];
    int ch;

    STACK *ps=malloc(sizeof(STACK));
    for(int i=0;i<COL;i++){
        ps->top[i] = -1;
    }

    init_board(ps);
    print_board(ps);
    printf("Enter player 1 name:\n");
    scanf("%s",p1);
    printf("Enter player 2 name:\n");
    scanf("%s",p2);

    while(1){
        printf("Enter column 0-6 %s turn\n",p1);
        scanf("%d",&ch);
        input_1(ps,ch,player1);
        print_board(ps);
        check_win(ps,player1);

        printf("Enter column 0-6 %s turn\n",p2);
        scanf("%d",&ch);
        input_1(ps,ch,player2);
        print_board(ps);
        check_win(ps,player2);
    }
    return 0;
}
