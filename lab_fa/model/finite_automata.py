class FiniteAutomata:
    @staticmethod
    def parseLine(line):
        return [value.strip() for value in line.strip().split('=')[1].strip()[1:-1].strip().split(',')]

    @staticmethod
    def fromFile(fileName):
        with open(fileName) as file:
            Q = FiniteAutomata.parseLine(file.readline())
            E = FiniteAutomata.parseLine(file.readline())
            q0 = file.readline().split('=')[1].strip()
            F = FiniteAutomata.parseLine(file.readline())

            S = FiniteAutomata.parseTransitions(FiniteAutomata.parseLine(''.join([line for line in file])))

            return FiniteAutomata(Q, E, S, q0, F)

    @staticmethod
    def parseTransitions(parts):
        result = {}
        transitions = []
        index = 0

        while index < len(parts):
            transitions.append(parts[index] + ',' + parts[index + 1])
            index += 2

        for transition in transitions:
            lhs, rhs = transition.split('->')
            state2 = rhs.strip()
            state1, route = [value.strip() for value in lhs.strip()[1:-1].split(',')]
            if (state1, route) not in result.keys():
                result[(state1, route)] = []
            result[(state1, route)].append(state2)

        return result

    def __init__(self, Q, E, S, q0, F):
        self.states = Q
        self.alphabet = E
        self.transitions = S
        self.initialState = q0
        self.finalStates = F

    def isState(self, value):
        return value in self.states

    def getTransitionsFor(self, state):
        if not self.isState(state):
            raise Exception('Can only get transitions for states')
        return [(trans, self.transitions[trans]) for trans in self.transitions.keys() if trans[0] == state]

    def showTransitionsFor(self, state):
        transitions = self.getTransitionsFor(state)

        print('{ ' + ' '.join([' -> '.join([str(part) for part in trans]) for trans in transitions]) + ' }')

    def isDFA(self):
        for key in self.transitions:
            if len(self.transitions[key]) > 1:
                return False
        return True

    def isAccepted(self, sequence: str):
        if len(sequence) == 0 and self.initialState in self.finalStates:
            return True
        currentState = self.initialState
        for char in sequence:
            currentState = self.nextState(currentState, char)
            if currentState is None:
                return False
        return currentState in self.finalStates

    def nextState(self, currentState: str, currentChar: str):
        if (currentState, currentChar) not in self.transitions.keys():
            return None
        return self.transitions[(currentState, currentChar)][0]

    def showAllTransitions(self):
        for state in self.states:
            self.showTransitionsFor(state)

    def __str__(self):
        return 'Q = { ' + ', '.join(self.states) + ' }\n' \
               + 'E = { ' + ', '.join(self.alphabet) + ' }\n' \
               + 'F = { ' + ', '.join(self.finalStates) + ' }\n' \
               + 'S = { ' + ', '.join(
            [' -> '.join([str(part) for part in trans]) for trans in self.transitions]) + ' }\n' \
               + 'q0 = ' + str(self.initialState) + '\n'
