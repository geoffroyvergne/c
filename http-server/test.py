import os
#import array

cmd = "curl -s localhost:3000/ | wc -m"

i=0
maxrang = 10000
results = []

for line in range(maxrang):
    #print("Launch", i)
    result = os.popen(cmd).read().strip()
    
    if result not in results :
        results.append(result)
        print(result)

    i+=1

