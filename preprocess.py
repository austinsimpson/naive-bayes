import json
import os, sys
#Script will process a bigass file from the internet and convert it to my file folder scheme

oneStarFile = file("data/amazon_reviews/1_star/data.txt", "w")
twoStarFile = file("data/amazon_reviews/2_star/data.txt", "w")
threeStarFile = file("data/amazon_reviews/3_star/data.txt", "w")
fourStarFile = file("data/amazon_reviews/4_star/data.txt", "w")
fiveStarFile = file("data/amazon_reviews/5_star/data.txt", "w")

def ensureDir():
    if (os.path.exists("data/amazon_reviews") == False):
        os.mkdir("data/amazon_reviews")
        os.mkdir("data/amazon_reviews/1_star")
        os.mkdir("data/amazon_reviews/2_star")
        os.mkdir("data/amazon_reviews/3_star")
        os.mkdir("data/amazon_reviews/4_star")
        os.mkdir("data/amazon_reviews/5_star")


def processLine(line):
    review = json.loads(line)
    rating = review[u'overall']
    if (rating == 1.0):
        oneStarFile.write(review[u"reviewText"] + "\n")
    if (rating == 2.0):
        twoStarFile.write(review[u"reviewText"] + "\n")
    if (rating == 3.0):
        threeStarFile.write(review[u"reviewText"] + "\n")
    if (rating == 4.0):
        fourStarFile.write(review[u"reviewText"] + "\n")
    if (rating == 5.0):
        fiveStarFile.write(review[u"reviewText"] + "\n")

def main():
    ensureDir()

    dataFile = file("data/Movies_and_TV_5.json")
    index = 0
    while True:
        index = index + 1
        print ("Line written: " + str(index))
        line = dataFile.readline()
        if line:
            processLine(line)
        else:
            break


if __name__ == '__main__':
    main()
