import random
from copy import deepcopy

class MCTS:
    def __init__(self, game, n_simulations):
        self.game = game
        self.n_simulations = n_simulations
        self.action_rewards = {}

    def select_best_move(self):
        best_move = None
        best_score = -1
        for move in self.game.get_possible_moves():
            total_score = 0
            for _ in range(self.n_simulations):
                test_game = deepcopy(self.game)
                test_game.execute_move(move)
                test_game.generate_new_cell()
                total_score += self.simulate(test_game)
            avg_score = total_score / self.n_simulations
            if avg_score > best_score:
                best_score = avg_score
                best_move = move
        return best_move

    def simulate(self, game):
        while not game.is_game_over():
            move = random.choice(game.get_possible_moves())
            game.execute_move(move)
            game.generate_new_cell()
        return game.score

    def add_action_rewards(self):
        state = self.game.get_state()
        best_move = None
        best_score = -1

        for move in self.game.get_possible_moves():
            total_score = 0
            for _ in range(self.n_simulations):
                game_copy = deepcopy(self.game)
                game_copy.execute_move(move)
                game_copy.generate_new_cell()
                reward = self.simulate(game_copy)
                total_score += reward
                if move not in self.action_rewards:
                    self.action_rewards[move] = []
                self.action_rewards[move].append(reward)
                if total_score > best_score:
                    best_move = move
                    best_score = total_score




    def choose_action(self):
        best_avg_reward = -float('inf')
        best_action = None
        for action in self.game.get_possible_moves():
            if action in self.action_rewards:
                avg_reward = sum(self.action_rewards[action]) / len(self.action_rewards[action])
                if avg_reward > best_avg_reward:
                    best_avg_reward = avg_reward
                    best_action = action
                else:
                    best_action = action
                    break
        return best_action