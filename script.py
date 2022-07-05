#import json module 
import json


count = 0

#point to local file and using 'with' so we don't have to write .close()  
with open('moistureLevel.json', 'r') as file:

#parsing json file to a dictonary(object)
    data = json.load(file)

#need to split by every new object in the array 
result = []

#incremet count so that we can incremet file name 
#each file will have its own object 

#writing into a new file 
with open('data.json', 'w') as file: 
    
    json.dump(data, file, indent=2)




