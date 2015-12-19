table = {}
while True:
    try:
        s = raw_input()
    except:
        break
    vec = s.split()
    if vec[1] in table:
        continue
    table[vec[1]]=1
    print vec[1]+'\t'+vec[0]
