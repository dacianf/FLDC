from models.HashTable import HashTable
from models.Scanner import Scanner


class Controller:
    def __init__(self, symbolTable: HashTable, scanner: Scanner, pif):
        self.__symbolTable = symbolTable
        self.__scanner = scanner
        self.__pif = pif

    def run(self, fileName):
        with open(fileName, 'r') as currentFile:
            lineNo = 0
            for line in currentFile:
                line = line.strip()
                lineNo += 1
                tokenPosition = 1
                for token in self.__scanner.getTokens(line.strip()):
                    if token in self.__scanner.specifications.words:
                        self.__pif.append(((token, self.__scanner.specifications.codification[token]), (-1, -1)))
                    elif self.__scanner.specifications.isIdentifier(token):
                        id = self.__symbolTable.add(token)
                        self.__pif.append(((token, self.__scanner.specifications.codification['identifier']), id))
                    elif self.__scanner.specifications.isConstant(token):
                        id = self.__symbolTable.add(token)
                        self.__pif.append(((token, self.__scanner.specifications.codification['constant']), id))
                    else:
                        raise Exception(
                            'Lexical error: Unknown token \'' + token + '\' at line ' + str(
                                lineNo) + ' on position ' + str(
                                tokenPosition))
                    tokenPosition += 1
        print("Lexically correct")

    def __formatPif(self):
        _str = ""
        for x in self.__pif:
            _str += str(x) + "\n"
        return _str

    def saveData(self):
        with open("data/pif.out", 'w+') as currentFile:
            currentFile.write("Program internal form:\n")
            currentFile.write(self.__formatPif())
            currentFile.close()

        with open("data/st.out", 'w+') as currentFile:
            currentFile.write("Symbol table\n(represented as hash table)\n")
            currentFile.write(str(self.__symbolTable))
            currentFile.close()
