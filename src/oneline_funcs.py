import numpy as np

def adjacentElementsProduct(inputArray):
    return np.max(np.array([inputArray[i] * inputArray[i+1] for i in range(len(inputArray)-1)]))

def allLongestStrings(inputArray):
    return [s for s in inputArray if len(s) == max([len(s) for s in inputArray])]

def checkPalindrome(inputString):
    return inputString == inputString[::-1]

def commonCharacterCount(s1, s2):
    return sum([min(s1.count(c), s2.count(c)) for c in set(s1) & set(s2)])

def areSimilar(A, B):
    return (A == B) or (sorted(A) == sorted(B))

def palindromeRearranging(inputString):
    return sum(map(lambda x: inputString.count(x) % 2, set(inputString))) <= 1

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [substitutionElem if e == elemToReplace else e for e in inputArray]

def evenDigitsOnly(n):
    return all([int(c) % 2 == 0 for c in str(n)])

def alphabeticShift(inputString):
    return ''.join([chr((ord(c) - ord('a') + 1) % 26 + ord('a')) for c in inputString])

def firstDigit(inputString):
    return int([c for c in inputString if c.isdigit()][0])
