def bylength(word1,word2):
    return len(word1)-len(word2)


imena = open('names.txt')
lines=imena.readlines()
lines.sort(bylength)

for ime in lines:
    print(ime)
