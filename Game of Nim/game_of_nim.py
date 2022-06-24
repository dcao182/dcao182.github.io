from games import *
import numpy as np

class GameOfNim(Game):
    def __init__(self, board):
        possible_moves = []
        for row in range(len(board)):
            for move in range(1, board[row] + 1):
                possible_moves.append((row, move))
        self.initial = GameState(to_move='MAX', utility=0, board=board, moves=possible_moves)



    def actions(self, state):
        return state.moves



    def result(self, state, move):
        if move not in state.moves:
            return state  # Illegal move has no effect

        board = state.board.copy()
        board[move[0]] = board[move[0]] - move[1]
        
        updated_moves = []
        for row in range(len(board)):
            for move in range(1, board[row] + 1):
                updated_moves.append((row, move))
        
        return GameState(to_move=('MIN' if state.to_move == 'MAX' else 'MAX'),
                         utility=state.utility, board=board, moves=updated_moves)



    def utility(self, state, player):
        is_all_zero = np.all((state.board == 0))
        if (is_all_zero and state.to_move == 'MAX'):
            return 1
        elif (is_all_zero and state.to_move == 'MIN'):
            return -1
        return 0
        


    def terminal_test(self, state):
        is_all_zero = np.all((state.board == 0))
        if(is_all_zero):
            return True
        else:
            return False

        

if __name__ == "__main__":
    nim = GameOfNim(board=[0, 5, 3, 1])  # Creating the game instance
    # nim = GameOfNim(board=[7, 5, 3, 1]) # a much larger tree to search
    print(nim.initial.board) # must be [0, 5, 3, 1]
    print(nim.initial.moves) # must be [(1, 1), (1, 2), (1, 3), (1, 4), (1, 5), (2, 1), (2, 2), (2, 3), (3, 1)]
    print(nim.result(nim.initial, (1,3) ))
    utility = nim.play_game(alpha_beta_player, query_player) # computer moves first
    if (utility < 0):
        print("MIN won the game")
    else:
        print("MAX won the game")
