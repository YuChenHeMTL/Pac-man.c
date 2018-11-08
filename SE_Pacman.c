#include <stdio.h>
#include <conio.h>

#define SIZE_R 21
#define SIZE_C 77
#define ITEM_TOTAL 263

typedef struct characters {
	int row;
	int column;
} position;


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

		int item_flag1 = 0;
		int item_flag2 = 0;
		int item_flag3 = 0;
		int item_flag4 = 0;

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
		char maze[SIZE_R][SIZE_C] = {
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

		ghost_2.row = 19;
		ghost_2.column = 70;

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
			if ((ghost_1.column - player.column) < 0)
			{
				if (maze[ghost_1.row][ghost_1.column + 1] == '*' || ( (ghost_1.column + 2 ) > SIZE_C ) || maze[ghost_1.row][ghost_1.column + 2] == '*')
				{

				}
				else
				{
					if (maze[ghost_1.row][ghost_1.column + 2] == '@')
					{
						death_flag = 1;
					}
					if (item_flag1)
					{
						maze[ghost_1.row][ghost_1.column] = '^';
					}
					else
					{
						maze[ghost_1.row][ghost_1.column] = ' ';
					}
					if(maze[ghost_1.row][ghost_1.column + 2] == '^')
					{
						item_flag1 = 1;
					}
					else
					{
						item_flag1 = 0;
					}

					maze[ghost_1.row][ghost_1.column + 2] = '&';
					ghost_1.column += 2;
					change_flag = 1;
				}
			}
			if (((ghost_1.column - player.column) > 0) && (change_flag == 0))
			{
				if (maze[ghost_1.row][ghost_1.column - 1] == '*' || ( (ghost_1.column - 2 ) > SIZE_C ) || maze[ghost_1.row][ghost_1.column - 2] == '*')
				{

				}
				else
				{
					if (maze[ghost_1.row][ghost_1.column - 2] == '@')
					{
						death_flag = 1;
					}
					if (item_flag1)
					{
						maze[ghost_1.row][ghost_1.column] = '^';
					}
					else
					{
						maze[ghost_1.row][ghost_1.column] = ' ';
					}
					if(maze[ghost_1.row][ghost_1.column - 2] == '^')
					{
						item_flag1 = 1;
					}
					else
					{
						item_flag1 = 0;
					}

					maze[ghost_1.row][ghost_1.column - 2] = '&';
					ghost_1.column -= 2;
					change_flag = 1;
				}
			}
			if (change_flag == 0)
			{
				if ((ghost_1.row - player.row) < 0)
				{
					if ( ( (ghost_1.row + 1 ) > SIZE_R ) || maze[ghost_1.row + 1][ghost_1.column] == '*')
					{

					}
					else
					{
						if (maze[ghost_1.row + 1][ghost_1.column] == '@')
						{
							death_flag = 1;
						}
						if (item_flag1)
						{
							maze[ghost_1.row][ghost_1.column] = '^';
						}
						else
						{
							maze[ghost_1.row][ghost_1.column] = ' ';
						}
						if(maze[ghost_1.row + 1][ghost_1.column] == '^')
						{
							item_flag1 = 1;
						}
						else
						{
							item_flag1 = 0;
						}

						maze[ghost_1.row + 1][ghost_1.column] = '&';
						ghost_1.row += 1;
						change_flag = 1;
					}
				}
				if (((ghost_1.row - player.row) > 0) && (change_flag == 0))
				{
					if ( ( (ghost_1.row - 1 ) > SIZE_R ) || maze[ghost_1.row - 1][ghost_1.column] == '*')
					{

					}
					else
					{
						if (maze[ghost_1.row - 1][ghost_1.column] == '@')
						{
							death_flag = 1;
						}
						if (item_flag1)
						{
							maze[ghost_1.row][ghost_1.column] = '^';
						}
						else
						{
							maze[ghost_1.row][ghost_1.column] = ' ';
						}
						if(maze[ghost_1.row - 1][ghost_1.column] == '^')
						{
							item_flag1 = 1;
						}
						else
						{
							item_flag1 = 0;
						}

						maze[ghost_1.row - 1][ghost_1.column] == '&';
						ghost_1.row -= 1;
						change_flag = 1;
					}
				}
			}
		}


		// printf("change_flag = %d\n", change_flag);

		// initialize change_flag
		change_flag = 0;

	    	if(!print_flag)
    		{
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
