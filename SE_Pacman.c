#include <stdio.h>
#include <conio.h>

#define SIZE_R 21
#define SIZE_C 77
#define ITEM_TOTAL 267

int main()
{
	int i = 0;
	int j = 0;

	int user_input = 0;
	int print_flag = 0;

	int items = 0;
	int location_r = 0;
	int location_c = 0;

	// The maze blueprint.
	// "@" is the player.
	// "^" is the item that the player has to collect.
	// Player wins when they collect all the "^".
	char maze[SIZE_R][SIZE_C] = {
	"*****************************************************************************",
	"* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ *",
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
	"* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ *",
	"*****************************************************************************",
	};

	// Total amount of "^" that has to be collected.
	items = ITEM_TOTAL;

    printf("WELCOME TO PACMAN!\n");
    printf("Short Guide: '@' is PACMAN, '^' is your objectives, and '&' are the ghosts!\n");
    printf("Press any key to start... \n");
    
    getch(); // wait for user to press a key.
    
    printf("\n");
    // print instructions
    printf("w = move up, s = move down, a = move left, d = move right, q = quit game, items left: %d\n", items);
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
	location_r = 7;
	location_c = 36;

//    #if 0
	// Game start
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
				if( maze[location_r][location_c - 1] == '*' || ( (location_c - 2 ) < 0 ) ||  maze[location_r][location_c - 2] == '*')
				{
			        print_flag = -1;
			    }
			    else
			    {
			        // if the location has an item, erase the item and reduce the number of items that should be collected.
			        if(maze[location_r][location_c - 2] == '^')
			        {
			            maze[location_r][location_c - 2] == ' ';
			            items--;
			        }
			        // erase the user's original position and place user in the new position.
			        maze[location_r][location_c] = ' ';
			        maze[location_r][location_c - 2] = '@';
			        // update user's current location.
			        location_c -= 2;
			    }
				break;
				
			case 'd' :
				// move right if possible..
				if( maze[location_r][location_c + 1] == '*' || ( (location_c + 2 ) > SIZE_C ) || maze[location_r][location_c + 2] == '*')
				{
			        print_flag = -1;
			    }
			    else
			    {
			        if(maze[location_r][location_c + 2] == '^')
			        {
			            maze[location_r][location_c + 2] == ' ';
			            items--;
			        }
			        maze[location_r][location_c] = ' ';
			        maze[location_r][location_c + 2] = '@';
			        location_c += 2;
			    }
				break;
				
			case 'w' :
				// move up if possible..
				if( ( (location_r - 1 ) < 0 ) || maze[location_r - 1][location_c] == '*')
				{
			        print_flag = -1;
			    }
			    else
			    {
			        if(maze[location_r - 1][location_c] == '^')
			        {
			            maze[location_r - 1][location_c] == ' ';
			            items--;
			        }
			        maze[location_r][location_c] = ' ';
			        maze[location_r - 1][location_c] = '@';
			        location_r--;
			    }
				break;
				
			case 's' :
				// move down if possible..
				if( ( (location_r + 1 ) > SIZE_R ) || maze[location_r + 1][location_c] == '*')
				{
			        print_flag = -1;
			    }
			    else
			    {
			        if(maze[location_r + 1][location_c] == '^')
			        {
			            maze[location_r + 1][location_c] == ' ';
			            items--;
			        }
			        maze[location_r][location_c] = ' ';
			        maze[location_r + 1][location_c] = '@';
			        location_r++;
			    }
				break;
				
			case 'q' :
			    // quit game?
			    printf("Are you sure you want to quit the game? y/n\n");
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
			            printf("Game Continue!\n");
			            break;
			        }
			    }
			    break;
			    
			default :
			    print_flag = -1; // the map will not print because no valid key is pressed.
				break;	// nothing else happens because it could be user randomly pressed a key.
		}
		
		if(!print_flag)
		{
			printf("\n");
			printf("\n");
			printf("\n");
			for (i = 0; i < SIZE_R; i++)
			{
				for (j = 0; j < SIZE_C; j++)
				{
					printf("%c", maze[i][j]);
				}
				printf("\n");
			}
		}

		// All items is collected, user wins the game, the loop will break.
		if(!items)
		{
			break;
		}
		
//		printf("items left?: %d\n", items);
		
		user_input = 0;	// clean the input.
		print_flag = 0; // reset flag.
	}
	
	printf("Congratulations! You win!\n");	// winning message.
	printf("Press any key to terminate...\n");
	
	getch();
/*
	printf("Play again? y/n\n");
	while(1)
	{
	    user_input = getch();
		if(user_input == 'y')
		{
	   
		}
		if(user_input == 'n')
	    {
		   printf("Press any key to exit...\n");
	       getch();
	       return 0;
		}
	}
*/
	
			    
//	#endif
	
	return 0;
}
