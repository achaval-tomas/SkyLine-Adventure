#pragma once

/* GAME STATES CYCLE
								GAME RUNNING
_________________________________________________________________________________

  Show Controls							                     --------<--------
	|	|                     	                            |                 |
Main Menu ----> Select Map ----> Select Difficuly ----> Start Game -----> Game Over
	|	  		     |       			|				    |                 |
	|----<----------<----------------<----------------<--------------<--------
_________________________________________________________________________________
    START               CONFIGURATION                        MAIN GAME LOOP

*/

typedef enum {
	GAME_RUNNING,
	MAIN_MENU,
	CHOOSE_MAP,
	CHOOSE_GAMEMODE,
	SEE_CONTROLS,
	GAME_STARTED,
	GAME_OVER,
	NEED_SET_UP,
	AWAITING_INPUT,
	STATES_SIZE
} STATE;


struct GameState {
/*                         GAME STATE INITIALIZER                   */
	void Init(){
		state[GAME_RUNNING]    = true;
		state[MAIN_MENU]       = true;	
		state[CHOOSE_MAP]      = false;
		state[CHOOSE_GAMEMODE] = false;
		state[SEE_CONTROLS]    = false;
		state[GAME_STARTED]    = false;
		state[GAME_OVER] 	   = false;
		state[NEED_SET_UP] 	   = false;
		state[AWAITING_INPUT]  = false;
		state[STATES_SIZE]     = false;
	}

/*                          GAME STATE SETTERS                      */
	GameState(){
		Init();
	}


	void ChooseMap(){
		state[MAIN_MENU]   = false;
		state[CHOOSE_MAP]  = true;
		StopWait();
	}

	void ChooseGamemode(){
		state[CHOOSE_MAP]      = false;
		state[CHOOSE_GAMEMODE] = true;
		StopWait();
	}

	void ShowControls(){
		state[MAIN_MENU]    = false;
		state[SEE_CONTROLS] = true;
	}

	void StartPlaying(){
		state[CHOOSE_GAMEMODE] = false;
		state[GAME_STARTED]	   = true;
		state[NEED_SET_UP] 	   = true;
		state[GAME_OVER]       = false;
		StopWait();		
	}

	void SetUpDone(){
		state[NEED_SET_UP] = false;
	}

	void EndRound(){
		state[GAME_OVER] = true;
		Wait();
	}

	void Restart(){
		state[NEED_SET_UP] = true;
		state[GAME_OVER]   = false;
		StopWait();
	}

	void Leave(){
		Init();
 		StopWait();
	}

	void Wait(){
		state[AWAITING_INPUT] = true;
	}

	void StopWait(){
		state[AWAITING_INPUT] = false;
	}

	void Quit(){
		state[GAME_RUNNING] = false;
	}

/*                          GAME STATE GETTERS                      */
	bool LoopStarted(){
		return state[GAME_RUNNING];
	}

	bool AtMainMenu(){
		return state[MAIN_MENU];
	}

	bool NeedsSetUp(){
		return state[NEED_SET_UP];
	}

	bool BeingPlayed(){
		return state[GAME_STARTED] && !state[GAME_OVER];
	}

	bool ChoosingMap(){
		return state[CHOOSE_MAP];
	}

	bool ChoosingGamemode(){
		return state[CHOOSE_GAMEMODE];
	}

	bool CheckingControls(){
		return state[SEE_CONTROLS] && !state[AWAITING_INPUT];
	}

	bool IsWaiting(){
		return state[AWAITING_INPUT];
	}

private:
	bool state[STATES_SIZE];
};