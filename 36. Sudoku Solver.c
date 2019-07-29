#include<stdio.h>
#include<stdlib.h>

#define N 9
#define UNASSIGNED 0

int is_exist_row(int grid[N][N], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int grid[N][N], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			}
		}
	}
	return 0;
}

int is_safe_num(int grid[N][N], int row, int col, int num) {
	return !is_exist_row(grid, row, num)
			&& !is_exist_col(grid, col, num)
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[N][N]) {

	int row = 0;
	int col = 0;

	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}

	for (int num = 1; num <= N; num++ ) {

		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;

			if (solve(grid)) {
				return 1;
			}

			grid[row][col] = UNASSIGNED;
		}
	}

	return 0;
}

void print_grid(int grid[N][N])
{
    printf("\n\n");
    printf("\t\t\t\t ________________________________________________________\n");
    for(int i=0;i<9;i++)
    {
        printf("\t\t\t\t|");
        for (int j=0;j<9;j++)
        {
                if (grid[i][j]==0)
                    printf("(%d,%d) ",i+1,j+1);
                else
                    printf("  %d   ",grid[i][j]);
                if(j==2 || j==5||j==8)
                    printf("|");
        }
        printf("\n");
        if(i==2||i==5||i==8)
        {
                printf("\t\t\t\t|__________________|__________________|__________________|\n\n");

        }
        else if (i!=8 )
              printf("\t\t\t\t|\t\t   |\t\t      |\t\t         |\n\t\t\t\t|\t\t   |\t\t      |\t\t         |\n");
    }

}



void input(int grid[][9])
{
    int num;
    do{
    printf("How Many No You Want To Enter: ");
    scanf("%d",&num);
    fflush(stdin);
    if(num<=0)
        printf("PLEASE ENTER A POSITIVE INTEGER\n\n");
    }while (num<=0);

    while(num!=0)
    {
        print_grid(grid);
        int row,col;

        do{
        printf("\n\nEnter Row and Col (row,col): ");
        scanf("%d,%d",&row,&col);

        if(!((row>=1 && row<=9) && (col>=1 && col<=9)))
            printf("..WRONG INPUT. Enter a Number Between 1-9\n\n");

        } while((row<1 || row>9) || (col<1 ||col>9));

        fflush(stdin);

        int no;
        do{
            printf("Enter No at %d,%d: ",row,col);
            scanf("%d",&no);

            if(!(no>=1 && no<=9 ))
                printf("PSSSTT..WRONG INPUT. Enter a Number Between 1-9\n\n");

            }while(no<1 || no>9 );

        grid[row-1][col-1]=no;

        num--;
    }

}

int main() {

	int grid[N][N] ;

	printf("\t\t\t\t\tWELCOME TO THE SUDOKU SOLVER PROGRAMME\n\n\n");

	for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
            grid[i][j]=0;
    }

    input(grid);

	if (solve(grid))
		print_grid(grid);
    else
		printf("no solution\n");

	system("pause");

	return 0;
}
