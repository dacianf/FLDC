import copy

# The size of the hashtable is directly proportional to the number of collisions that might occur.
defaultHashTableSize = 32


class HashTable:

    # @param {number} hashTableSize
    def __init__(self, hashTableSize=defaultHashTableSize):

        self.entries = [[] for x in range(0, hashTableSize)]
        self.__nbOfItems = 0
        self.__loadFactor = 0.7

    # @param {string} key
    def add(self, key):
        self.__reHash()
        keyHash = self.__hash(key)
        bucketList = self.entries[keyHash]
        try:
            nodeIndex = bucketList.index(key)
        except ValueError:
            nodeIndex = None

        if nodeIndex is None:
            bucketList.append(key)
            # print("Added: {", key, "} at hash: ", keyHash)
        # else:
            # print("{", key, "} already at", keyHash, ",", nodeIndex)
        self.__nbOfItems += 1
        return keyHash

    def __reHash(self):
        if self.__nbOfItems // len(self.entries) > self.__loadFactor:
            tmp = copy.deepcopy(self.entries)
            self.entries = [[] for x in range(0, 2 * len(self.entries))]
            for key in tmp:
                for v in key:
                    self.add(v)

    # @params {string} key
    # @returns {number}
    def __hash(self, key):
        return hash(key) % len(self.entries)

    # @params {string} key
    # @returns {tuple} _hash and position
    def find(self, key):
        _hash = self.__hash(key)
        if key in self.entries[_hash]:
            return _hash, self.entries[_hash].index(key)
        # print("Key {", key, "} not found.")
        return _hash, -1

    def __str__(self):
        _str = ""
        for index in range(len(self.entries)):
            _str += "hash: " + str(index) + "\n\t"
            _str += str(self.entries[index])
            _str += "\n"
        return _str
