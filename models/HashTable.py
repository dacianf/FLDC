import copy

# The size of the hashtable is directly proportional to the number of collisions that might occur.
defaultHashTableSize = 32


class HashTable:

    # @param {number} hashTableSize
    def __init__(self, hashTableSize=defaultHashTableSize):

        self.__entries = [[] for x in range(0, hashTableSize)]
        self.__nbOfItems = 0
        self.__loadFactor = 0.7

    # @params {string} key
    # @returns {tuple} _hash and position
    def findPosition(self, key):
        _hash = self.__hash(key)
        if key in self.__entries[_hash]:
            return _hash, self.__entries[_hash].index(key)
        # print("Key {", key, "} not found.")
        return _hash, -1

    # @param {string} key
    # @returns {tuple} _hash and position
    def add(self, key):
        self.__reHash()
        keyHash = self.__hash(key)
        bucketList = self.__entries[keyHash]
        try:
            nodeIndex = bucketList.index(key)
        except ValueError:
            nodeIndex = None

        if nodeIndex is None:
            bucketList.append(key)
            self.__nbOfItems += 1
            return keyHash, len(bucketList) - 1
            # print("Added: {", key, "} at hash: ", keyHash)
        # print("{", key, "} already at", keyHash, ",", nodeIndex)
        return keyHash, nodeIndex

    # @param {int} keyHash, {int} position
    # @returns {string} key
    def getElement(self, keyHash, position):
        if keyHash >= len(self.__entries) \
                or self.__entries[keyHash] is None \
                or position not in range(0, len(self.__entries[keyHash])):
            return None
        return self.__entries[keyHash][position]

    def __reHash(self):
        if self.__nbOfItems // len(self.__entries) > self.__loadFactor:
            tmp = copy.deepcopy(self.__entries)
            self.__entries = [[] for x in range(0, 2 * len(self.__entries))]
            for key in tmp:
                for v in key:
                    self.add(v)

    # @params {string} key
    # @returns {number}
    def __hash(self, key):
        return hash(key) % len(self.__entries)

    def __str__(self):
        _str = ""
        for index in range(len(self.__entries)):
            _str += "hash: " + str(index) + "\n\t"
            _str += str(self.__entries[index])
            _str += "\n"
        return _str
