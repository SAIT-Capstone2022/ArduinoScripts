#import json module 
import json
from unittest import result


<<<<<<< HEAD
#opening the local file through txt
with open('testData.txt', 'r') as f:
    text_split = f.read().split('}')
=======
count = 0

#point to local file and using 'with' so we don't have to write .close()  
with open('moistureLevel.json', 'r') as file:

#parsing json file to a dictonary(object)
    data = json.load(file)

#need to split by every new object in the array 
result = []

#increment count so that we can incremet file name 
#each file will have its own object 

#writing into a new file 
with open('data.json', 'w') as file: 
    
    json.dump(data, file, indent=2)


>>>>>>> 3c41e3fd4bd7f586cd9a7c3e0f25ca112d436ac7

  
#create new file with json
with open('newfile' + '.json', 'w') as f:
    f.write(text_split[0])

#create new file with json and store objects
with open('newfile' + '.json', 'w') as f:
   
    f.write('}'.join(text_split[1:]))