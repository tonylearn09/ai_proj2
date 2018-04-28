import game
import collections
from random import randint

const_agentId = 1
const_oppoId = 2

# a random policy 
class RandomPolicy:
    def getNextAction(self, game):
        agent = game.nextPlayer
        op = 2 if agent == 1 else 1
        index_map = game.index_map
        while True:
            pos = randint(0, 217 - 1)
            x, y = index_map[pos]

            if (game.gomokuboard[x][y] == 0):
                return pos

def evaluate(game, weights = collections.defaultdict(int, {1:1,2:2,3:3,4:4,5:5})):
    agentCount = game.winningCount[const_agentId - 1]
    oppoCount = game.winningCount[const_oppoId - 1]

    return sum([ weights[key] * agentCount[key] - weights[key] * oppoCount[key] for key in range(len(agentCount))])


class MinimaxPolicy:
    def __init__(self, evalFunc = evaluate, depth = 1, pruning = True):
        self.depth = depth
        self.pruning = pruning
        self.evalFunc = evalFunc

    def getNextAction(self, game, weights = None):

        def recurseAlphaBeta(d, lowerBound, upperBound):
            winner = game.isEnd()
            if winner == const_agentId:
                return (float('inf'), None)
            elif winner >= 0:
                return (float('-inf'), None)
            if d == self.depth:
                if weights is None:
                    return (self.evalFunc(game), None)
                else:
                    return (self.evalFunc(game, weights), None)

            gomokuboard = game.gomokuboard
            lastMove = game.lastMove
            player = game.nextPlayer

            nextd = d + 1 if player == 2 else d
            choices = []
            for k in range(0, 217):
                res = game.updateBoard(k)
                if res:
                    # have update
                    if weights is None:
                        choices.append((self.evalFunc(game), k))
                    else:
                        choices.append((self.evalFunc(game, weights), k))
                    game.revert(lastMove)

            choices.sort()
            if player == const_agentId:
                choices = choices[::-1]

            maxPair = (float('-inf'), None)
            minPair = (float('inf'), None)
            for _, a in choices:
                game.updateBoard(a)
                if player == const_agentId:
                    v, _ = recurseAlphaBeta(nextd, maxPair[0], upperBound)
                else:
                    v, _ = recurseAlphaBeta(nextd, lowerBound, minPair[0])
                maxPair = max(maxPair, (v, a))
                minPair = min(minPair, (v, a))

                game.revert(lastMove)
                if self.pruning and player == const_agentId and maxPair[0] > upperBound:
                    return maxPair
                elif self.pruning and player != const_agentId and minPair[0] < lowerBound:
                    return minPair
            return maxPair if player == const_agentId else minPair

        value, action = recurseAlphaBeta(0, float('-inf'), float('inf'))
        return action