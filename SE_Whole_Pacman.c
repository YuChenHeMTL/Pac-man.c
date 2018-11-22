#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE_R 21
#define SIZE_C 77
#define ITEM_TOTAL 263

typedef struct {
	int row;
	int column;
} position;

void update_screen(char maze[][SIZE_C+1], int rows, int cols, int items) 
{
  	int i;

	gotoxy(0,0);
    	clrscr();
  
	if (items)
	{
		 printf("\nw = move up, s = move down, a = move left, d = move right, q = quit game, items left: %d \n", items);
	}
      
    	// Draw the maze above.
    	for (i = 0; i < rows; i++)
    	{
    		// gotoxy(1,3 + (i+1));
    		printf("%s\n",maze[i]);
	}
}

void ghost_add_col (position *ghost, int* changef, int* deathf, int* itemf, char arr[SIZE_R][SIZE_C + 1])
{
	if (*changef == 0)
	{
		if ((arr[ghost->row][ghost->column + 1] == '*') || ( (ghost->column + 2 ) > SIZE_C ) || (arr[ghost->row][ghost->column + 2] == '*') || (arr[ghost->row][ghost->column + 2] == '&'))
		{
			// *movable = -1;
		}
		else
		{
			if (arr[ghost->row][ghost->column + 2] == '@')
			{
				*deathf = 1;
			}
			if (*itemf)
			{
				arr[ghost->row][ghost->column] = '^';
			}
			else
			{
				arr[ghost->row][ghost->column] = ' ';
			}
			if(arr[ghost->row][ghost->column + 2] == '^')
			{
				*itemf = 1;
			}
			else
			{
				*itemf = 0;
			}

			arr[ghost->row][ghost->column + 2] = '&';
			ghost->column += 2;
			*changef = 1;
		}
	}
}

void ghost_min_col (position *ghost, int* changef, int* deathf, int* itemf, char arr[SIZE_R][SIZE_C + 1])
{
	if (*changef == 0)
	{
		if ((arr[ghost->row][ghost->column - 1] == '*') || ( (ghost->column - 2 ) > SIZE_C ) || (arr[ghost->row][ghost->column - 2] == '*') || (arr[ghost->row][ghost->column - 2] == '&'))
		{
			// *movable = -1;
		}
		else
		{
			if (arr[ghost->row][ghost->column - 2] == '@')
			{
				*deathf = 1;
			}
			if (*itemf)
			{
				arr[ghost->row][ghost->column] = '^';
			}
			else
			{
				arr[ghost->row][ghost->column] = ' ';
			}
			if(arr[ghost->row][ghost->column - 2] == '^')
			{
				*itemf = 1;
			}
			else
			{
				*itemf = 0;
			}
				
			arr[ghost->row][ghost->column - 2] = '&';
			ghost->column -= 2;
			*changef = 1;
		}
	}
}

void ghost_add_row (position *ghost, int* changef, int* deathf, int* itemf, char arr[SIZE_R][SIZE_C + 1])
{
	if (*changef == 0)
	{
		if ( ( (ghost->row + 1 ) > SIZE_R ) || (arr[ghost->row + 1][ghost->column] == '*') || (arr[ghost->row + 1][ghost->column] == '&'))
		{
			// *movable = -1;				
		}
		else
		{
			if (arr[ghost->row + 1][ghost->column] == '@')
			{
				*deathf = 1;
			}
			if (*itemf)
			{
				arr[ghost->row][ghost->column] = '^';
			}
			else
			{
				arr[ghost->row][ghost->column] = ' ';
			}
			if(arr[ghost->row + 1][ghost->column] == '^')
			{
				*itemf = 1;
			}
			else
			{
				*itemf = 0;
			}
			arr[ghost->row + 1][ghost->column] = '&';
			ghost->row += 1;
			*changef = 1;
		}
	}
}

void ghost_min_row (position *ghost, int* changef, int* deathf, int* itemf, char arr[SIZE_R][SIZE_C + 1])
{
	if (*changef == 0)
	{
		if ( ( (ghost->row - 1 ) > SIZE_R ) || (arr[ghost->row - 1][ghost->column] == '*') || (arr[ghost->row - 1][ghost->column] == '&'))
		{
			// *movable = -1;
		}
		else
		{
			if (arr[ghost->row - 1][ghost->column] == '@')
			{
				*deathf = 1;
			}
			if (*itemf)
			{
				arr[ghost->row][ghost->column] = '^';
			}
			else
			{
				arr[ghost->row][ghost->column] = ' ';
			}
			if(arr[ghost->row - 1][ghost->column] == '^')
			{
				*itemf = 1;
			}
			else
			{
				*itemf = 0;
			}
				
			arr[ghost->row - 1][ghost->column] = '&';
			ghost->row -= 1;
			*changef = 1;
		}
	}
}

int main()
{
	printf("WELCOME TO PACMAN! \n");
	printf("Short Guide: '@' is PACMAN, '^' is your objectives, and '&' are the ghosts! \n");
    
	//    #if 0
	// Game start
	while(1)
	{
		int i = 0;
		int j = 0;

		int user_input = 0;
    		int print_flag = 0;
		int death_flag = 0;

		int change_flag = 0;
		int temp = 0;

		int item_flag1 = 0;
		int item_flag2 = 0;
		int item_flag3 = 0;
		int item_flag4 = 0;

		/*
		int add_row = 0;
		int min_row = 0;
		int add_col = 0;
		int min_col = 0;
		*/

    		int items = 0;
    		position player;
		position ghost_1;
		position ghost_2;
		position ghost_3;
		position ghost_4;

    		// The maze blueprint.
    		// "@" is the player.
    		// "^" is the item that the player has to collect.
    		// Player wins when they collect all the "^".
		char maze[SIZE_R][SIZE_C + 1] = {
		"*****************************************************************************",
    		"* ^ ^ & ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ & ^ ^ *",
    		"* ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ ***********",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
    		"* ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ ***********",
    		"* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ @ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ *",
    		"*********** ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ *",
    		"*         * ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *",
    		"*         * ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *",
    		"*         * ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *",
   	 	"*********** ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ *",
   	 	"* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ *",
    		"* ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ ***********",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
    		"* ^ ^ *        *  ^  *        * ^ ^ *        *  ^  *        * ^ ^ *         *",
   	 	"* ^ ^ **********  ^  ********** ^ ^ **********  ^  ********** ^ ^ ***********",
    		"* ^ ^ & ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ & ^ ^ *",
    		"*****************************************************************************",
    		};

	    	// Total amount of "^" that has to be collected.
	    	items = ITEM_TOTAL;
 
		printf("Press any key to start... \n");
		getch();	// wait for user to press a key.

		for(i=0;i<SIZE_R;i++) 
		{
            			maze[i][SIZE_C] = '\0';
              
            			// printf("%s\n",maze[i]);
          	  	}
                
            		update_screen(maze,SIZE_R,SIZE_C,items);

		#if 0
       		printf("\n");

        		// print instructions
        		printf("w = move up, s = move down, a = move left, d = move right, q = quit game, items left: %d \n", items);

    		// Draw the maze above.
    		for (i = 0; i < SIZE_R; i++)
    		{
	   	 	for (j = 0; j < SIZE_C; j++)
		    	{
    				printf("%c", maze[i][j]);
    			}
    			printf("\n");
    		}
		#endif
		
    		// Get user initial position.
    		player.row = 7;
    		player.column = 36;

		// Get ghost initial position
		ghost_1.row = 1;
		ghost_1.column = 6;

		ghost_2.row = 1;
		ghost_2.column = 70;

		ghost_3.row = 19;
		ghost_3.column = 6;

		ghost_4.row = 19;
		ghost_4.column = 70;

	  	while(1)
	    	{
	    		// Check if the input is clean or not. If is not clean, there is an error.
	    		if (user_input == 0)
	    		{
	    			user_input = getch();	// record the user input.
		    	}
	    		else
    			{	
    				printf("bug detected\n");
    				return -1;	// -1 is error in input.
	    		}
    
    			// Respond to user's input; player moves by wasd.
    			// If the location where the user wants to move is a wall, then do nothing and clean user_input.
    			// If there is a '*' in the location, erase the '*' and replace it with "@". The variable "item" will -1.
    			switch (user_input)
    			{
    				case 'a' :
    			   	// move left if possible..
    					if( maze[player.row][player.column - 1] == '*' || ( (player.column - 2 ) < 0 ) ||  maze[player.row][player.column - 2] == '*')
    					{
	    		        			print_flag = -1;
		    	    		}
	    		    		else
	    		    		{
	    		       			// if the location has an item, erase the item and reduce the number of items that should be collected.
    			        			if(maze[player.row][player.column - 2] == '^')
	    		        			{
    			            			maze[player.row][player.column - 2] == ' ';
	    		            			items--;
    			        			}
						// if the location is a ghost, end the game.
						if(maze[player.row][player.column - 2] == '&')
						{
							maze[player.row][player.column] = ' ';
    			        				maze[player.row][player.column - 2] = '&';
							death_flag = 1;

						}
						else
						{
							// erase the user's original position and place user in the new position.
	    		        				maze[player.row][player.column] = ' ';
    			        				maze[player.row][player.column - 2] = '@';
    			        				// update user's current location.
    			        				player.column -= 2;

						}
    			    		}
    					break;
				
    				case 'd' :
    					// move right if possible..
		    			if( maze[player.row][player.column + 1] == '*' || ( (player.column + 2 ) > SIZE_C ) || maze[player.row][player.column + 2] == '*')
    					{
    			        			print_flag = -1;
    			    		}
    			    		else
    			    		{
    			       			if(maze[player.row][player.column + 2] == '^')
    			        			{
    			            			maze[player.row][player.column + 2] == ' ';
    			            			items--;
    			        			}
						if(maze[player.row][player.column + 2] == '&')
    			        			{
    			            			maze[player.row][player.column] = ' ';
    			        				maze[player.row][player.column + 2] = '&';
    			        				death_flag = 1;
    			        			}
    			        			else
						{
							maze[player.row][player.column] = ' ';
    			        				maze[player.row][player.column + 2] = '@';
    			        				player.column += 2;
						}
    			    		}
    					break;
				
    				case 'w' :
    					// move up if possible..
    					if( ( (player.row - 1 ) < 0 ) || maze[player.row - 1][player.column] == '*')
    					{
    			        			print_flag = -1;
    			    		}
    			    		else
    			    		{
    			        			if(maze[player.row - 1][player.column] == '^')
    			        			{
    			            			maze[player.row - 1][player.column] == ' ';
	    		            			items--;
	    		        			}
						if(maze[player.row - 1][player.column] == '&')
    			        			{
    			            			maze[player.row][player.column] = ' ';
    			        				maze[player.row - 1][player.column] = '&';
							death_flag = 1;
	    		        			}

    			        			else
						{
							maze[player.row][player.column] = ' ';
    			        				maze[player.row - 1][player.column] = '@';
    			        				player.row--;
						}
    			    		}
    					break;
    				
    				case 's' :
        					// move down if possible..
	    				if( ( (player.row + 1 ) > SIZE_R ) || maze[player.row + 1][player.column] == '*')
	    				{
	    		        			print_flag = -1;
	    		    		}
    			    		else
    			    		{
    			        			if(maze[player.row + 1][player.column] == '^')
    			        			{
    			            			maze[player.row + 1][player.column] == ' ';
    			            			items--;
    			       			}
						if(maze[player.row + 1][player.column] == '&')
    			        			{
    			            			maze[player.row][player.column] = ' ';
    			        				maze[player.row + 1][player.column] = '&';
							death_flag = 1;
    			       			}

	    		        			else
						{
							maze[player.row][player.column] = ' ';
    			        				maze[player.row + 1][player.column] = '@';
    			        				player.row++;
						}

    			    		}
    						break;
				
    				case 'q' :
    			    		// quit game?
	    		    		printf("Are you sure you want to quit the game? y/n \n");
    			    		while(1)
		    	    		{
		    	        			user_input = getch();
		    	        			if(user_input == 'y')
	    		       			{
	    		            		printf("See you!\n");
	    		            		return 0;
	    		        			}
	    		        			if(user_input == 'n')
	    		        			{
		    	            			printf("Game Continue! \n");
		    	            			break;
		    	        			}
	    		    		}
	    		    		break;
	       		    
	    		default :
    			    	print_flag = -1; // the map will not print because no valid key is pressed.
    				break;	// nothing else happens because it could be user randomly pressed a key.
    		}
		
/*		if(death_flag)
		{
			printf("You hit a ghost!\n");
			break;
		}
*/

		if ((death_flag == 0) && (print_flag == 0))
		{
			temp = rand() %10;
			if (temp == 0)
			{
				ghost_add_col (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
			}

			if (temp == 1)
			{
				ghost_add_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
			}

			if (temp == 2)
			{
				ghost_min_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
			}

			if (temp == 3)
			{
				ghost_min_col (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
			}

			if (temp > 3)
			{
				if ((ghost_1.column - player.column) < 0)
				{
					ghost_add_col (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				}
				
				if ((ghost_1.column - player.column) > 0)
				{
					ghost_min_col (&ghost_1, &change_flag, &death_flag, &item_flag1,  maze);
				}	

				if ((ghost_1.row - player.row) < 0)
				{
					ghost_add_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				}
				
				if ((ghost_1.row - player.row) > 0)
				{
					ghost_min_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				}	
			}
			if (!change_flag)
			{
				ghost_add_col (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				ghost_min_col (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				ghost_add_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
				ghost_min_row (&ghost_1, &change_flag, &death_flag, &item_flag1, maze);
			}
		}


		// printf("change_flag = %d\n", change_flag);
		// printf("row = %d, column = %d\n", ghost_1.row, ghost_1.column);

		// initialize change_flag
		change_flag = 0;

		if ((death_flag == 0) && (print_flag == 0))
		{
			temp = rand() %10;
			if (temp == 0)
			{
				ghost_add_col (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
			}

			if (temp == 1)
			{
				ghost_add_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
			}

			if (temp == 2)
			{
				ghost_min_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
			}

			if (temp == 3)
			{
				ghost_min_col (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
			}

			if (temp > 3)
			{
				if ((ghost_2.row - player.row) < 0)
				{
					ghost_add_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				}
				
				if ((ghost_2.row - player.row) > 0)
				{
					ghost_min_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				}
				
				if ((ghost_2.column - player.column) < 0)
				{
					ghost_add_col (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				}
				
				if ((ghost_2.column - player.column) > 0)
				{
					ghost_min_col (&ghost_2, &change_flag, &death_flag, &item_flag2,  maze);
				}	
	
			}
			if (!change_flag)
			{
				ghost_add_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				ghost_min_row (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				ghost_add_col (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
				ghost_min_col (&ghost_2, &change_flag, &death_flag, &item_flag2, maze);
			}
		}
		change_flag = 0;

		if ((death_flag == 0) && (print_flag == 0))
		{
			temp = rand() %10;
			if (temp == 0)
			{
				ghost_add_col (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
			}

			if (temp == 1)
			{
				ghost_add_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
			}

			if (temp == 2)
			{
				ghost_min_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
			}

			if (temp == 3)
			{
				ghost_min_col (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
			}

			if (temp > 3)
			{
				
				if ((ghost_3.row - player.row) > 0)
				{
					ghost_min_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				}

				if ((ghost_3.row - player.row) < 0)
				{
					ghost_add_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				}
				
				if ((ghost_3.column - player.column) > 0)
				{
					ghost_min_col (&ghost_3, &change_flag, &death_flag, &item_flag3,  maze);
				}

				if ((ghost_3.column - player.column) < 0)
				{
					ghost_add_col (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				}	
			}
			if (!change_flag)
			{
				ghost_min_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				ghost_add_row (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				ghost_min_col (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
				ghost_add_col (&ghost_3, &change_flag, &death_flag, &item_flag3, maze);
			}
		}
		change_flag = 0;

		if ((death_flag == 0) && (print_flag == 0))
		{
			temp = rand() %10;
			if (temp == 0)
			{
				ghost_add_col (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
			}

			if (temp == 1)
			{
				ghost_add_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
			}

			if (temp == 2)
			{
				ghost_min_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
			}

			if (temp == 3)
			{
				ghost_min_col (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
			}

			if (temp > 3)
			{
				if ((ghost_4.column - player.column) > 0)
				{
					ghost_min_col (&ghost_4, &change_flag, &death_flag, &item_flag4,  maze);
				}

				if ((ghost_4.column - player.column) < 0)
				{
					ghost_add_col (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				}
				
				if ((ghost_4.row - player.row) > 0)
				{
					ghost_min_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				}

				if ((ghost_4.row - player.row) < 0)
				{
					ghost_add_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				}	
			}
			if (!change_flag)
			{
				ghost_min_col (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				ghost_add_col (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				ghost_min_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
				ghost_add_row (&ghost_4, &change_flag, &death_flag, &item_flag4, maze);
			}
		}
		change_flag = 0;

	    	if(!print_flag)
    		{
			#if 0
    			printf("\n");
    			printf("\n");
    			printf("\n");
//			printf("item_flag = %d\n", item_flag1);
    			printf("w = move up, s = move down, a = move left, d = move right, q = quit game, items left: %d\n", items);
    			for (i = 0; i < SIZE_R; i++)
    			{
    				for (j = 0; j < SIZE_C; j++)
    				{
		    			printf("%c", maze[i][j]);
	    			}
	    			printf("\n");
	    		}
			#endif

			update_screen(maze,SIZE_R,SIZE_C,items);
    		}

		// Check if player hit ghost.
		if(death_flag)
		{
			break;
		}

    		// All items is collected, user wins the game, the loop will break.
    		if(!items)
	    	{
	    		break;
	    	}
		
            //  printf("items left?: %d\n", items);
		
	    	user_input = 0;	// clean the input.
	    	print_flag = 0;	// reset flag.
    	}
	

	if(!death_flag)
	{
		printf("Congratulations! You Win!\n");	// winning message.
	}
	else
	{
		printf("Aw... You Lose!\n");	// losing message.
	}
    	
    	printf("Press any key to proceed...\n");
	
    	getch();

    	printf("Do you want to play again? y/n \n");
    	while(1)
    	{
    	    	user_input = getch();
    		if(user_input == 'y')
    		{
    		   	printf("\n");
    			printf("\n");
    			printf("\n");
	            	break;
    		}
    		if(user_input == 'n')
    	    	{
    		   	printf("Press any key to exit...\n");
    	       		getch();
    	       		return 0;
    		}
    	}
}

	
			    
//	#endif
	
	return 0;
}
