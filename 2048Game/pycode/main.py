import Game
import MCTS
import numpy

def get_next_best_move2(a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4,n_simulations=50):
    state1=[a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4]
    board = numpy.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            board[i][j]=state1[i*4+j]
    game=Game.Game(board)
    mcts = MCTS.MCTS(game,50)
    move = mcts.select_best_move()
    print(move)
    match move:
        case 'up':
            return 1
        case 'down':
            return 2
        case 'left':
            return 3
        case 'right':
            return 4
        case _:
            return 0

def get_next_best_move(state1,n_simulations=50):
    board = numpy.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            board[i][j]=state1[i*4+j]
    game=Game.Game(board)
    mcts = MCTS.MCTS(game,50)
    move = mcts.select_best_move()
    print(move)
    match move:
        case 'up':
            return 1
        case 'down':
            return 2
        case 'left':
            return 3
        case 'right':
            return 4
        case _:
            return 0
        
def main():
    get_next_best_move([0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0],50)

def add(a,b):
    return a+b

if __name__ == '__main__':
    main()