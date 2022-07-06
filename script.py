#import json module 
import json
from unittest import result


#opening the local file through txt
with open('testData.txt', 'r') as f:
    text_split = f.read().split('}')

  
#create new file with json
with open('newfile' + '.json', 'w') as f:
    f.write(text_split[0])

#create new file with json and store objects
with open('newfile' + '.json', 'w') as f:
   
    f.write('}'.join(text_split[1:]))