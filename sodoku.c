#include <stdio.h>
#include <windows.h>

void gridInit(int grid[9][9]){

  //Giving Each Space in Grid the value 0
  for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;  // Empty cells
        }
  }
}

//Display Grid Function
void displayGrid(int grid[9][9]) {

  //Colours
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  //Top Row
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
  printf("   |1 2 3 |4 5 6 |7 8 9\n");
  printf("___|______|______|_____\n");

  //Nested Loop for 2D Grid
  int i;
  int y;
  //Row Loop
  for (i=0; i<9; i++) {

    
    //Row Numbers
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("%d", (i+1));
    printf("  |");
  
    //Column Loop
    for (y=0; y<9; y++) {

      //Vertical line after 3 columns
      if ((y % 3 == 0) && y != 0){
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("|");
      }

      //Game colour to white
      SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

      //Converting integers to characters, so I can display 0's as "-"
      if (grid[i][y] == 0) {
        char symbol = '-';
        printf("%c ", symbol);
} 
      
      else {
        printf("%d ", grid[i][y]);
      }

      if (y==8){
        printf("\n");
      }


     
    }

     //Line under 3 rows
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    if (((i + 1) % 3 == 0) && i != 0 && i != 8){
      printf("___|______|______|_____\n");
      
    }
  }
}

//Duplicates check function
int checkDuplicates(int nums[9]){

  int nums2[10] = {0}; //Holding any potential duplicates

  //Looping over the column, box or row.
  int c;
  for (c=0; c<9; c++){

    if (nums[c] == 0){
      //Pass over unfilled boxes
    }
    //If a numbers position is empty, fill it
    else if (nums2[nums[c]] == 0){
      nums2[nums[c]] = nums[c];
    }      
    //If the numbers position is taken, there must be a duplicate, so return False 
    else{
      return 0;
    }


  }

  //No dupes found
  return 1;

}


//Function to check whether move is possible
int validateMove(int row, int col, int grid[9][9]) {
  
  //Overview:
  //Going to take the row, and column, and box and make into array of 9
  //If duplicate is found, then we will return false.
  //Else return True to suggest the move may be correct.

  //Column Array
  int column[9];
  int i;
  for (i=0; i<9; i++){
    column[i] = grid[i][col];
  }

  //Row Array
  int fullRow[9];
  int y;
  for (y=0; y<9; y++){
    fullRow[y] = grid[row][y];
  }

  //Box Array
  int boxFull[9];

  //3 Columns Finder 
  int x = 9;
  int decrementNum = 3;
  int colFound;
  int done = 0;
  while (x >= 0 && done == 0) {
    if (col >= x) {
      colFound = x;
      done = 1;
    }
    x -= decrementNum;
  }

  //3 Rows Finder 
  int z = 9;
  int rowFound;
  int done2 = 0;
  while (z >= 0 && done2 == 0) {
    if (row >= z) {
        rowFound = z;
        done2 = 1;
      }
      z -= decrementNum;

    }

  //Manually setting the box array
  boxFull[0] = grid[rowFound][colFound];
  boxFull[1] = grid[rowFound + 1][colFound];
  boxFull[2] = grid[rowFound + 2][colFound];
  boxFull[3] = grid[rowFound][colFound + 1];
  boxFull[4] = grid[rowFound + 1][colFound + 1];
  boxFull[5] = grid[rowFound + 2][colFound + 1];
  boxFull[6] = grid[rowFound][colFound + 2];
  boxFull[7] = grid[rowFound + 1][colFound + 2];
  boxFull[8] = grid[rowFound + 2][colFound + 2];
  

  //Checking for duplicates in the 3 different arrays

  if (checkDuplicates(boxFull) == 0){
    return 0;
  }
  if (checkDuplicates(column) == 0){
    return 0;
  }
  if (checkDuplicates(fullRow) == 0){
    return 0;
  }

  return 1;
  
  
}



//Final full puzzle check
int solved(int grid[9][9]) {

  int i;
  int j;

  //If any part of the grid is empty, then the sodoku is not finished
  for (i=0;i<9;i++){
    for (j=0;j<9;j++){
      if (grid[i][j] == 0){
        return 0;
      }
    }
  }
  //No empty spots
  return 1;

}

//Text File Input function
void loadBoard(int board[9][9]) {
  
  FILE *file = fopen("sodoku.txt", "r");
 
  // Check if the file opened successfully
  if (file == NULL) {
      printf("Error opening file.\n");
      return;

  }

  int num;
  // Read numbers from the file and insert them into board structure
  int x = 0;
  int y = 0;
  while (fscanf(file, "%d", &num) != EOF) {
    board[y][x] = num;
    x += 1;

    if (x == 9) { 
      x = 0;
      y += 1;
    }        
  }

  // Close the file
  fclose(file);

  }


int main() {

  int game = 1;
  int board[9][9];

  printf("Sodoku");
  gridInit(board);
  loadBoard(board);

  while (game == 1){
    printf("\n");
    displayGrid(board);
    
    int row, col, value;
    printf("Enter row, column, and value (1-9) separated by space: ");
    scanf("%d %d %d", &row, &col, &value);
    //Changing Sodoku value
    board[row - 1][col - 1] = value;

    //Checking if the move currently violates the rules
    if (validateMove(row - 1, col - 1, board) == 0){
      displayGrid(board);
      printf("MOVE DISALLOWED\n");
      board[row - 1][col - 1] = 0;
    }

    if (solved(board)) {
      game = 0;
    }

    printf("\n");  
  }
  //Game End
  printf("Puzzle Complete");
}
