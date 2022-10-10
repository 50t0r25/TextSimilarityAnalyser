# TextSimilarityAnalyser
C++ command line app for calculating the similarity percentage between 2 text files.
>Implements [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) and calculates the percentage by dividing from the length of the biggest text file.

###### I only provide support and builds for Linux

# Downloading
```
cd ~/Downloads

wget https://github.com/50t0r25/TextSimilarityAnalyser/releases/download/v1/TSA-v1-linux.tar.gz

tar -xzvf TSA-v1-linux.tar.gz

chmod +x TSA
```

# Running
**ONLY SUPPORTS .txt FILES**
```
./TSA "path to first file" "path to second file"
```
Example: `./TSA text1.txt text2.txt`

# Build instructions
