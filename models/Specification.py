import re


class Specification:
    def __init__(self):
        self.separators = ['[', ']', '{', '}', '(', ')', '\n', ' ', '\"', "\'", ';', ',']
        self.operators = ['+', '-', '*', '/', '%', '<', '<=', '=', '>=', '>',
                          '==', '&&', '||', '!', '!=', '++', '--', '+=', '-=']
        self.reservedWords = ['main', 'char', 'int', 'double', 'citeste', 'afiseaza',
                              'if', 'else', 'for', 'while', 'break']
        self.words = self.separators + self.operators + self.reservedWords
        self.codification = dict([(self.words[i], i + 2) for i in range(len(self.words))])
        self.codification['identifier'] = 0
        self.codification['constant'] = 1

    @staticmethod
    def isIdentifier(token):
        return re.match(r'^[a-zA-Z]([a-zA-Z]|[0-9])*$', token) is not None

    @staticmethod
    def isConstant(token):
        return re.match('^(0|[\+\-]?[1-9][0-9]*)$|^\'.\'$|^\".\"$', token) is not None

    def isOperator(self, char):
        return char in self.operators

    @staticmethod
    def isEscapedQuote(line, index):
        return False if index == 0 else line[index - 1] == '\\'
