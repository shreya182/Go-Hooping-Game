/*
 * Author: Shreya Suresh
 * Program description: 2 player Basketball shooting game: simulates players making shots from 5 
 * positions and with 2 special balls. Determines winner and lets user play again.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
* Function: calculateShotScored
* Description: Iterate through the shotResults array and calculate scores for each shot
* Parameters: 
* 	shotResults (bool array): results of all shots
* 	shotScores (int array): scores of all shots
* 	moneyBallRackPos (int): user inputted money ball rack position
*/
void calculateShotScores(bool shotResults[], int shotScores[], int moneyBallRackPos) {
	for (int i = 0; i < 25; i++) {
        	if ((i + 1) % 5 == 0) {
            		if (shotResults[i]) {
                	shotScores[i] = 2; // Last shot of the rack is a money ball
            	} else {
                	shotScores[i] = 0; // Missed money ball
            	}
        	} else {
            		if ((i / 5) + 1 == moneyBallRackPos && shotResults[i]) {
                		shotScores[i] = 2; // Made shot in money ball rack, worth 2 points
            		} else if (shotResults[i]) {
                		shotScores[i] = 1; // Regular ball worth 1 point
            		} else {
                		shotScores[i] = 0; // Missed regular ball
            		}
        	}	
    	}	   
}

/*
* Function: calculateRowScores
* Description: Calculate the scores for each row
* Parameters: 
* 	shotScores (int array): scores of all shots
* 	rowScores (int array): stores totals of each row
* Side effects: add shot score to row score array
*/
void calculateRowScores(int shotScores[], int rowScores[]) {
   	for (int i = 0; i < 25; i += 5) { //calculates scores for each row
        	int rowScore = 0; 
        	for (int j = i; j < i + 5; j++) {
            		rowScore += shotScores[j]; // Add shot score to row score
        	}
        	rowScores[i / 5] = rowScore; //update array
   	} 
}

/*
* Function: displayShootingResults
* Description: Display shooting results for current player
* Parameters: 
* 	shotScores (int array): scores of all shots
* 	rowScores (int array): stores totals of each row
* 	moneyBallRackPos (int): user inputted money ball rack position
* Returns (int): total score for current player 
* Side effects: score display, row labels, and row scores printed to terminal
*/
int displayShootingResults(int shotScores[], int rowScores[], int moneyBallRackPos, 
		int starryShot1, int starryShot2) { //displays player shooting results
	int totalScore = 0;
	for (int i = 0; i < 5; i++) {
		if (i == 2){ //starry row 1
			cout << "Starry: ";
			char starryResult1 = '_';
			if (starryShot1 > 0){
				starryResult1 = 'S';
				totalScore += starryShot1;
			}
			cout << starryResult1 << "         | " << starryShot1 << " pts" << endl;
		}	
		if (i == 3){ //starry row 2
			cout << "Starry: ";
			char starryResult2 = '_';
			if (starryShot2 > 0){
				starryResult2 = 'S';
				totalScore += starryShot2;
			}
			cout << starryResult2 << "         | " << starryShot2 << " pts" << endl;
	}
	
        cout << "Rack " << i + 1 << ": ";
        for (int j = 0; j < 5; j++) {
        	int index = (i * 5) + j; // Calculate the index
        	char resultChar = '_'; // Default to missed shot
		if (shotScores[index] == 1) {
                	resultChar = 'O'; // Made regular shot
            	} else if (shotScores[index] == 2) {
                	resultChar = 'M'; // Made money ball
            	}

            	if ((i + 1) == moneyBallRackPos) {
                	if (resultChar == 'O'){
                        	resultChar = 'M';
                	}
            	}	

        	cout << resultChar << " ";
        }
        cout << "| " << rowScores[i] << " pts" << endl;
	totalScore += rowScores[i];
    	}      
	cout << "Total: " << totalScore << " pts" << endl;
	return totalScore;
}

/*
* Function: decideWinner
* Description: Compare player totals and determine winner
* Parameters: 
* 	player1score (int): the first player's score
* 	player2score (int): the second player's score
* Side effects: "Player (1 or 2) is the winner!" or "It's a tie!" printed to the terminal
*/
void decideWinner(int player1score, int player2score){ // compare totals and decide winner
	if (player1score > player2score) {
        	cout << "Player 1 is the winner!" << endl;
    	} else if (player2score > player1score) {
        	cout << "Player 2 is the winner!" << endl;
    	} else {
        	cout << "It's a tie!" << endl;
    	}
}

int main() {
	srand(time(NULL));
	int again;
	do {
		bool shotResults[25]; // array for shot results
    		int shotScores[25]; // array for shot scores 
    		int rowScores[5]; // array for row scores
    		int player1score; 
    		int player2score;

    		cout << "Welcome to the basketball shooting contest!" << endl;
    		cout << "\n";
    		// Loop for each player's turn
    		for (int playerTurn = 0; playerTurn < 2; playerTurn++) {
        	// Ask the player for their money ball rack position
        		int moneyBallPosition;
        		cout << "Player " << playerTurn + 1 << ", enter the position for the money ball rack (1-5): ";
        		cin >> moneyBallPosition;

        	// Validate the input
        	while (moneyBallPosition < 1 || moneyBallPosition > 5) {
            		cout << "Invalid input. Enter the position for the money ball rack (1-5): ";
            		cin >> moneyBallPosition;
        	}

        	// Simulate shot results (true for made shots, false for missed shots)
        	for (int i = 0; i < 25; i++) {
            		shotResults[i] = rand() % 2 == 0; // 50% chance of true (made shot) or false (missed shot)
        	}

        	// Calculate shot scores and row scores
        	calculateShotScores(shotResults, shotScores, moneyBallPosition);
        	calculateRowScores(shotScores, rowScores);

		int starryRack1Score = 0;
		int starryRack2Score = 0;

		if (shotResults[5 * 2]) {
    			starryRack1Score = 3;
		}
		if (shotResults[5 * 3]) {
    			starryRack2Score = 3;
		}
        	// Display the shooting results for the current player
        	cout << "Player " << playerTurn + 1  << "'s Turn:" << endl;
        	if (playerTurn == 0){
			player1score = displayShootingResults(shotScores, rowScores, moneyBallPosition, 
			starryRack1Score, starryRack2Score);
		} else if (playerTurn == 1){
			player2score = displayShootingResults(shotScores, rowScores, moneyBallPosition,
				starryRack1Score, starryRack2Score);
			}
    		}	
  		decideWinner(player1score, player2score);
		cout << "Do you want to play again? (1-yes, 0-no): ";
		cin >> again;
    	} while (again == 1);
	
	return 0;
}

