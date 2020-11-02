from models.Specification import Specification


class Scanner:
    def __init__(self, specifications: Specification):
        self.__specifications = specifications

    @property
    def specifications(self):
        return self.__specifications

    def __getStringToken(self, line, index):
        token = ''
        quoteCount = 0

        while index < len(line) and quoteCount < 2:
            if line[index] == '"' and not self.__specifications.isEscapedQuote(line, index):
                quoteCount += 1
            token += line[index]
            index += 1

        return token, index

    def __getOperatorToken(self, line, index):
        token = ''
        while index < len(line) and self.__specifications.isOperator(line[index]):
            token += line[index]
            index += 1
        if token == '+' or token == '-':
            while index < len(line) and self.__specifications.isConstant(line[index]):
                token += line[index]
                index += 1

        return token, index

    def getTokens(self, line):
        token = ''
        index = 0

        while index < len(line):
            if line[index] == '"':
                if token:
                    yield token
                token, index = self.__getStringToken(line, index)
                yield token
                token = ''

            elif self.__specifications.isOperator(line[index]):
                if token:
                    yield token
                token, index = self.__getOperatorToken(line, index)
                yield token
                token = ''

            elif line[index] in self.__specifications.separators:
                if token:
                    yield token
                token, index = line[index], index + 1
                yield token
                token = ''

            else:
                token += line[index]
                index += 1
        if token:
            yield token
