#import json module 
import json
from unittest import result


number_of_splits = 49

#opening the local file through txt
with open('testData.txt', 'r') as f:
    text_split = f.read().split('}')

#create new file with json
with open('newfile' + '.json', 'w') as f:
    f.write(text_split[0])
    
#current unknown, we have a steady stream of files to read, with x amount of times of splitting. 
#Incrementing through a loop because infinite therefore incremeting a file becomes infinite 

#Option: Hard code the amount of times we want to split to have 

for i in range (number_of_splits+1): 
    #parse i to string 
    i = str(i)
#create new file with json and store objects
    with open('newfile'+i+ '.json', 'w') as f:
    
        f.write('}'.join(text_split[1:]))