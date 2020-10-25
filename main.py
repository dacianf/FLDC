from HashTable import HashTable

if __name__ == '__main__':
    table = HashTable(hashTableSize=10)
    table.add("int")
    table.add("double")
    table.add("]")
    table.add("char")
    table.add("bool")
    table.add("int")
    print(table.findPosition("int"))
    print(table.findPosition("no"))
    print(table)
    x = int(input())
    y = int(input())
    print(table.getElement(423, 34))
    print(table.getElement(x, 34))
    print(table.getElement(x, -1))
    print(table.getElement(x, y))
