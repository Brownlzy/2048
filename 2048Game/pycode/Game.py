from copy import deepcopy
import numpy
import random


class Game:

    # 初始化，把真实环境里的游戏场景传给虚拟环境里的矩阵
    def __init__(self):
        self.score = 0
        self.board = numpy.zeros((4, 4), dtype=int)

    def __init__(self,state):
        self.score = 0
        self.board = state

    # 返回空白格子
    def get_empty_cells(self):
        return [(i, j) for i in range(4) for j in range(4) if self.board[i][j] == 0]

    def generate_new_cell(self):
        empty_cells = self.get_empty_cells()
        if empty_cells:
            i, j = random.choice(empty_cells)
            self.board[i][j] = 2 if random.random() < 0.9 else 4

    def is_game_over(self):
        # 检查是否有空格子
        if len(self.get_empty_cells()) > 0:
            return False
        # 检查每个格子的上下左右是否有相等的格子
        for i in range(4):
            for j in range(4):
                if i > 0 and self.board[i][j] == self.board[i - 1][j]:
                    return False
                if j > 0 and self.board[i][j] == self.board[i][j - 1]:
                    return False
                if i < 3 and self.board[i][j] == self.board[i + 1][j]:
                    return False
                if j < 3 and self.board[i][j] == self.board[i][j + 1]:
                    return False
        return True

    def get_state(self):
        return self.board.copy()

    def set_state(self, state):
        self.board = state.copy()

    def get_possible_moves(self):
        # 返回可能的移动方向：'up', 'down', 'left', 'right'
        return [direction for direction in ['up', 'down', 'left', 'right'] if self.can_move(direction)]

    def can_move(self, direction):
        test_board = deepcopy(self.board)
        test_board, _ = self.test_move(test_board, direction)
        return not numpy.array_equal(self.board, test_board)

    def compress(self, board):
        new_board = [[0] * 4 for _ in range(4)]

        for i in range(4):
            pos = 0
            for j in range(4):
                if board[i][j] != 0:
                    if new_board[i][pos] == 0:
                        new_board[i][pos] = board[i][j]
                    elif new_board[i][pos] == board[i][j]:
                        new_board[i][pos] = 2 * board[i][j]
                        self.score += new_board[i][pos]
                        pos += 1
                    else:
                        pos += 1
                        new_board[i][pos] = board[i][j]
        return new_board, self.score

    def transpose(self, board):
        return [list(i) for i in zip(*board)]

    def reverse(self, board):
        return [i[::-1] for i in board]

    def execute_move(self, direction):
        # 返回执行移动后的新棋盘和得分
        moved = False

        # 这里添加根据方向执行移动和合并的逻辑
        if direction == 'up':
            self.board = self.transpose(self.board)
            self.board, self.score = self.compress(self.board)
            self.board = self.transpose(self.board)
        elif direction == 'down':
            self.board = self.reverse(self.transpose(self.board))
            self.board, self.score = self.compress(self.board)
            self.board = self.transpose(self.reverse(self.board))
        elif direction == 'left':
            self.board, score = self.compress(self.board)
        elif direction == 'right':
            self.board = self.reverse(self.board)
            self.board, self.score = self.compress(self.board)
            self.board = self.reverse(self.board)

        return self.board, self.score

    def test_move(self, board, direction):
        # 返回执行移动后的新棋盘和得分
        moved = False
        score = 0
        # 这里添加根据方向执行移动和合并的逻辑
        if direction == 'up':
            board = self.transpose(board)
            board, score = self.compress(board)
            board = self.transpose(board)
        elif direction == 'down':
            board = self.reverse(self.transpose(board))
            board, self.score = self.compress(board)
            board = self.transpose(self.reverse(board))
        elif direction == 'left':
            board, score = self.compress(board)
        elif direction == 'right':
            board = self.reverse(board)
            board, self.score = self.compress(board)
            board = self.reverse(board)

        return board, score





