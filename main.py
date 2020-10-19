from HashTable import HashTable

if __name__ == '__main__':
    table = HashTable(hashTableSize=10)
    table.add("int")
    table.add("double")
    table.add("]")
    table.add("char")
    table.add("bool")
    table.add("int")
    table.find("int")
    table.find("no")
    print(table)
