from random import randint
import collections
import copy
from collections import deque

const_agentId = 1
const_oppoId = 2

class Gomoku:
    def __init__(self, first_player):
        # gomoku board
        self.init_board()
        self.get_index_map()
        self.reverse_index_map = {v: k for k, v in self.index_map.items()}

        # player 
        # 1 is agent, 2 is opponent
        self.nextPlayer = first_player 
        self.lastMove   = (-1, -1)
        self.totalSteps = [0, 0] # (agent, opponent)
        self.winningCount = [[0 for i in range(0, 6)] for j in range(0, 2)] #[[agent count], [opponent count]]
        self.winningCount[0][0] = self.winningCount[1][0] = 217
        self.prevWinningCount = []

        print("Finish setting up board")

    def init_board(self):
        self.gomokuboard = []
        for i in range(9, 18):
            empty_list = [0 for j in range(i)]
            self.gomokuboard.append(empty_list)
        for i in range(16, 8, -1):
            empty_list = [0 for j in range(i)]
            self.gomokuboard.append(empty_list)

    def get_index_map(self):
        self.index_map = { }
        for i in range(0, 0+9):
            self.index_map[i] = (0, i)
        for i in range(9, 9+10):
            self.index_map[i] = (1, i-9)
        for i in range(19, 19+11):
            self.index_map[i] = (2, i-19)
        for i in range(30, 30+12):
            self.index_map[i] = (3, i-30)
        for i in range(42, 42+13):
            self.index_map[i] = (4, i-42)
        for i in range(55, 55+14):
            self.index_map[i] = (5, i-55)
        for i in range(69, 69+15):
            self.index_map[i] = (6, i-69)
        for i in range(84, 84+16):
            self.index_map[i] = (7, i-84)
        for i in range(100, 100+17):
            self.index_map[i] = (8, i-100)
        for i in range(117, 117+16):
            self.index_map[i] = (9, i-117)
        for i in range(133, 133+15):
            self.index_map[i] = (10, i-133)
        for i in range(148, 148+14):
            self.index_map[i] = (11, i-148)
        for i in range(162, 162+13):
            self.index_map[i] = (12, i-162)
        for i in range(175, 175+12):
            self.index_map[i] = (13, i-175)
        for i in range(187, 187+11):
            self.index_map[i] = (14, i-187)
        for i in range(198, 198+10):
            self.index_map[i] = (15, i-198)
        for i in range(208, 208+9):
            self.index_map[i] = (16, i-208)

    def currentGame(self):
        # return the next player, total steps for agent and opponent respectively
        return (self.nextPlayer, self.totalSteps[0], self.totalSteps[1])

    def updateBoard(self, pos):
        # update a board given a pos
        # pos is in the form 0~216
        pos_index = self.index_map[pos]
        self.totalSteps[self.nextPlayer - 1] += 1
        self.lastMove = pos_index

        self.prevWinningCount.append(self.winningCount)
        newWinningCount = updateFeature(self, pos_index)
        if self.nextPlayer == 1:
            self.winningCount = [newWinningCount['agent'], newWinningCount['opponent']]
        else:
            self.winningCount = [newWinningCount['opponent'], newWinningCount['agent']]
        self.gomokuboard[pos_index[0]][pos_index[1]] = self.nextPlayer
        self.nextPlayer = 2 if self.nextPlayer == 1 else 1

    def revert(self, lastPos):
        # revert last move given updated last postion
        self.totalSteps[2 - self.nextPlayer] -= 1
        self.gomokuboard[self.lastMove[0]][self.lastMove[1]] = 0
        self.nextPlayer = 3 - self.nextPlayer
        self.lastMove = lastPos

        assert(len(self.prevWinningCount) > 0)
        self.winningCount = self.prevWinningCount[-1]
        self.prevWinningCount.pop()

    def clear(self, first_player):
        self.init_board()
        self.nextPlayer = first_player 
        self.lastMove   = (-1, -1)
        self.totalSteps = [0, 0] # (agent, opponent)
        self.winningCount = [[0 for i in range(0, 6)] for j in range(0, 2)] #[[agent count], [opponent count]]
        self.winningCount[0][0] = self.winningCount[1][0] = 217
        self.prevWinningCount = []
        print("Finish clearing up board for restart")
    
    def print_board(self):
        for row in self.gomokuboard:
            print(row)


def updateFeature(gomoku, pos_index):

    gomokuboard = gomoku.gomokuboard
    windowSize = 5

    agent = gomoku.nextPlayer
    opponent = 1 if agent == 2 else 2

    agentCount = [gomoku.winningCount[agent - 1][i] for i in range(0, 6)]
    opponentCount = [gomoku.winningCount[opponent - 1][i] for i in range(0, 6)]

    nextMove_i, nextMove_j = pos_index[0], pos_index[1]
    startPos = { }
    startPos['row'] = [(nextMove_i, nextMove_j-delta) for delta in range(0, 5) \
                       if nextMove_j-delta >= 0]

    # valid positions for checking
    valid_pos = copy.deepcopy(startPos['row'])
    startPos['row'] = startPos['row'][-1]

    if nextMove_i <= 8:
        # top half (head)
        startPos['diag'] = [(nextMove_i-delta, nextMove_j-delta) for delta in range(0, 5) \
                                if (nextMove_i-delta >= 0 and nextMove_j-delta >= 0)]
        startPos['rdiag'] = [(nextMove_i-delta, nextMove_j) for delta in range(0, 5) \
                                if nextMove_i-delta>= 0]

        valid_pos += copy.deepcopy(startPos['diag'])
        valid_pos += copy.deepcopy(startPos['rdiag'])
        startPos['diag'] = startPos['diag'][-1]
        startPos['rdiag'] = startPos['rdiag'][-1]

        # top half (tail)
        # diag
        for delta in range(0, 5):
            if nextMove_i + delta > 8:
                y_index = nextMove_j + (8 - nextMove_i)
                if y_index < len(gomoku.gomokuboard[nextMove_i+delta]):
                    valid_pos.append((nextMove_i+delta, y_index))
            else:
                if nextMove_j+delta < len(gomoku.gomokuboard[nextMove_i+delta]):
                    valid_pos.append(nextMove_i+delta, nextMove_j+delta)
        # rdiag
        for delta in range(0, 5):
            if nextMove_i + delta > 8:
                y_index = nextMove_j - (delta - (8 - nextMove_i))
                if y_index >= 0:
                    valid_pos.append((nextMove_i+delta, y_index))
            else:
                if nextMove_j-delta >= 0:
                    valid_pos.append(nextMove_i+delta, nextMove_j-delta)


    elif nextMove_i > 8:
        # bottom half (head)
        start_diag_tuple = pos_index
        valid_pos.append(start_diag_tuple)
        for delta in range(0, 5):
            if nextMove_i - delta > 8:
                start_diag_tuple = (nextMove_i-delta, nextMove_j)
                valid_pos.append(start_diag_tuple)
            else:
                col_index = nextMove_j - (delta - (nextMove_i - 8))
                if col_index >= 0:
                    start_diag_tuple = (nextMove_i-delta, col_index)
                    valid_pos.append(start_diag_tuple)

        startPos['diag'] = start_diag_tuple

        start_rdiag_tuple = pos_index
        valid_pos.append(start_rdiag_tuple)
        for delta in range(0, 5):
            if nextMove_i - delta >= 8:
                if nextMove_j + delta < len(gomoku.gomokuboard[nextMove_i-delta]):
                    start_rdiag_tuple = (nextMove_i-delta, nextMove_j+delta)
                    valid_pos.append(start_rdiag_tuple)
            else:
                col_index = nextMove_j + (nextMove_i - 8)
                if col_index < len(gomoku.gomokuboard[nextMove_i-delta]):
                    start_rdiag_tuple = (nextMove_i-delta, col_index)
                    valid_pos.append(start_rdiag_tuple)

        startPos['rdiag'] = start_rdiag_tuple

        # bottome half (tail)
        valid_pos += [(nextMove_i+delta, nextMove_j) for delta in range(0, 5) \
                          if nextMove_i+delta < 18]
        valid_pos += [(nextMove_i+delta, nextMove_j-delta) for delta in range(0, 5) \
                          if (nextMove_i+delta < 18 and nextMove_j-delta >= 0)]
    
    direction = {'row': (0, 1), 'diag': (1, 1), 'rdiag': (1, 0),
                 'row_b': (0, 1), 'diag_b': (1, 0), 'rdiag_b': (1, -1)}

    for d in ('row', 'diag', 'rdiag'):
        (i, j) = startPos[d]
        initial = 0
        windowCount = {'agent': 0, 'opponent': 0}
        prev_history = deque()
        prev_history.append((-1, -1)) #dummy
        prev_history.append((i, j))
        while (i, j) in valid_pos:
            if initial < windowSize - 1:
                if gomoku.gomokuboard[i][j] == agent:
                    windowCount['agent'] += 1
                elif gomoku.gomokuboard[i][j] == opponent:
                    windowCount['opponent'] += 1
                initial += 1
                if i <= 8:
                    # top half
                    i += direction[d][0]
                    j += direction[d][1]
                else:
                    # bottom
                    i += direction[d+'_b'][0]
                    j += direction[d+'_b'][1]

                prev_history.append((i, j))
                continue
            if (gomoku.gomokuboard[i][j] == agent):
                windowCount['agent'] += 1
            elif (gomoku.gomokuboard[i][j] == opponent):
                windowCount['opponent'] += 1


            (previ, prevj) = prev_history.popleft()
            if (previ, prevj) in valid_pos:
                prevLoc = gomoku.gomokuboard[previ][prevj]
                if (prevLoc == agent):
                    windowCount['agent'] -= 1
                elif (prevLoc == opponent):
                    windowCount['opponent'] -= 1

            if (windowCount['opponent'] <= 0):
                agentCount[windowCount['agent']] -= 1
                agentCount[windowCount['agent'] + 1] += 1
            if (windowCount['agent'] <= 0):
                opponentCount[windowCount['opponent']] -= 1

            if i <= 8:
                # top half
                i += direction[d][0]
                j += direction[d][1]
            else:
                # bottom
                i += direction[d+'_b'][0]
                j += direction[d+'_b'][1]
            prev_history.append((i,j))

    return {'agent': agentCount, 'opponent': opponentCount}




if __name__ == "__main__":
    g = Gomoku(1)
    g.print_board()
